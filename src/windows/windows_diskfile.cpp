
#ifdef _WIN32
#include <algorithm>
#include <limits>
#include "windows_diskfile.h"
#include "dshfs/error.h"


namespace dshfs
{
    Windows_DiskFile::Windows_DiskFile()
    {
        handle = INVALID_HANDLE_VALUE;
        canWrite = false;
    }

    bool Windows_DiskFile::isOpen() const
    {
        return handle != INVALID_HANDLE_VALUE;
    }

    bool Windows_DiskFile::isReadable() const
    {
        return isOpen();
    }

    bool Windows_DiskFile::isWritable() const
    {
        return isOpen() && canWrite;
    }

    void Windows_DiskFile::close()
    {
        if(isOpen())
        {
            CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
            canWrite = false;
        }
    }

    File::pos_t Windows_DiskFile::read(void* buf, pos_t size)
    {
        if(!isReadable())       return 0;

        auto ptr = reinterpret_cast<unsigned char*>(buf);
        pos_t total = 0;
        while(size > 0)
        {
            auto block = static_cast<DWORD>( std::min<pos_t>( size, std::numeric_limits<DWORD>::max() ) );
            DWORD result = block;
            if(!ReadFile(handle, ptr, block, &result, nullptr))
                break;
            size -= result;
            ptr += result;
            total += result;
            if(result < block)
                break;
        }
        return total;
    }
    
    File::pos_t Windows_DiskFile::write(const void* buf, pos_t size)
    {
        if(!isWritable())       return 0;

        auto ptr = reinterpret_cast<const unsigned char*>(buf);
        pos_t total = 0;
        while(size > 0)
        {
            auto block = static_cast<DWORD>( std::min<pos_t>( size, std::numeric_limits<DWORD>::max() ) );
            DWORD result = block;
            if(!WriteFile(handle, ptr, block, &result, nullptr))
                break;
            size -= result;
            ptr += result;
            total += result;
            if(result < block)
                break;
        }
        return total;
    }
    
    File::pos_t Windows_DiskFile::seek(pos_t pos, Origin origin)
    {
        if(!isOpen())           return -1;

        DWORD movemethod;
        switch(origin)
        {
        case Origin::Cur:       movemethod = FILE_CURRENT;      break;
        case Origin::Set:       movemethod = FILE_BEGIN;        break;
        case Origin::End:       movemethod = FILE_END;          break;
        default:                return -1;
        }

        LARGE_INTEGER in, out;
        in.QuadPart = pos;
        if(!SetFilePointerEx(handle, in, &out, movemethod))
            return -1;
        
        return out.QuadPart;
    }

    File::pos_t Windows_DiskFile::tell() const
    {
        if(!isOpen())           return -1;
        
        LARGE_INTEGER in, out;
        in.QuadPart = 0;
        if(!SetFilePointerEx(handle, in, &out, FILE_CURRENT))
            return -1;

        return out.QuadPart;
    }
        
    File::Ptr Windows_DiskFile::open(const std::string& path, int flags)
    {
        std::string errprefix = " In openFile (" + path + ")";

        // have to have read access
        if(!(flags & FileMode::Read))           throw Err::BadParams(errprefix + ": Files must be opened with read access.");
        
        DWORD access = GENERIC_READ;
        DWORD share = 0;
        DWORD creat = 0;
        bool canWrite = false;
        
        if(flags & FileMode::Write)
        {
            // Writable
            canWrite = true;
            access |= GENERIC_WRITE;
            switch(flags & (FileMode::Create | FileMode::Truncate | FileMode::FailIfExists))
            {
            case (FileMode::Create | FileMode::FailIfExists):
            case (FileMode::Create | FileMode::FailIfExists | FileMode::Truncate):
                creat = CREATE_NEW;
                break;
            case (FileMode::Create | FileMode::Truncate):
                creat = CREATE_ALWAYS;
                break;
            case (FileMode::Create):
                creat = OPEN_ALWAYS;
                break;
            case 0:
                creat = OPEN_EXISTING;
                break;
            case (FileMode::Truncate):
                creat = TRUNCATE_EXISTING;
                break;
            default:
                throw Err::BadParams(errprefix + ": Bad combination of Create/Truncate/FailIfExists flags");
            }
        }
        else
        {
            // Not writable
            if(flags & (FileMode::Create | FileMode::Truncate | FileMode::FailIfExists))
                throw Err::BadParams(errprefix + ": Create/Truncate/FailIfExists flags require opening with write access");
            creat = OPEN_EXISTING;
        }
        if(flags & FileMode::ShareRead)     share |= FILE_SHARE_READ;
        if(flags & FileMode::ShareWrite)    share |= FILE_SHARE_WRITE | FILE_SHARE_DELETE;

        auto handle = CreateFileW(
            winsupport::makeWindowsFullPathName(path).c_str(),
            access,
            share,
            nullptr,
            creat,
            0,
            nullptr
        );


        if(handle == INVALID_HANDLE_VALUE)
        {
            switch(GetLastError())
            {
            case ERROR_SHARING_VIOLATION:       throw Err::NoAccess(errprefix + "Create/Truncate/FailIfExists flags require opening with write access");
            case ERROR_ALREADY_EXISTS:          throw Err::AlreadyExists(errprefix);
            case ERROR_FILE_EXISTS:             throw Err::AlreadyExists(errprefix);
            case ERROR_FILE_NOT_FOUND:          throw Err::NotFound(errprefix);
            default:                            throw Err::Unknown(errprefix);
            }
        }

        auto file = std::make_unique<Windows_DiskFile>();
        file->handle = handle;
        file->canWrite = canWrite;
        return std::move(file);
    }
}

#endif