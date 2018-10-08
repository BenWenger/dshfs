
#include "winheader.h"
#include "dshfs.h"
#include <algorithm>
#include <limits>

#define winfile         reinterpret_cast<HANDLE>(rawdat)
#define clearwinfile()  rawdat = reinterpret_cast<void*>(INVALID_HANDLE_VALUE)

namespace dshfs
{
    File::File()
    {
        clearwinfile();
    }
    
    File::File(File&& rhs)
    {
        rawdat = rhs.rawdat;
        clearwinfile();
    }
    
    File& File::operator = (File&& rhs)
    {
        close();
        rawdat = rhs.rawdat;
        clearwinfile();
        return *this;
    }

    File::File(const std::string& path, int flags)
    {
        clearwinfile();
        open(path,flags);
    }

    bool File::isOpen() const
    {
        return rawdat != INVALID_HANDLE_VALUE;
    }

    void File::close()
    {
        if(isOpen())
        {
            CloseHandle(winfile);
            clearwinfile();
        }
    }
    
    ErrorCode File::open(const std::string& path, int flags)
    {
        // have to have read access
        if(!(flags & FileMode::Read))           return ErrorCode::BadParams;
        
        DWORD access = GENERIC_READ;
        DWORD share = 0;
        DWORD creat = 0;
        
        if(flags & FileMode::Write)
        {
            // Writable
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
                return ErrorCode::BadParams;
            }
        }
        else
        {
            // Not writable
            if(flags & (FileMode::Create | FileMode::Truncate | FileMode::FailIfExists))
                return ErrorCode::BadParams;
            creat = OPEN_EXISTING;
        }
        if(flags & FileMode::ShareRead)     share |= FILE_SHARE_READ;
        if(flags & FileMode::ShareWrite)    share |= FILE_SHARE_WRITE | FILE_SHARE_DELETE;

        auto handle = CreateFileW(
            makeWindowsFullPathName(path).c_str(),
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
            case ERROR_SHARING_VIOLATION:       return ErrorCode::NoAccess;
            case ERROR_ALREADY_EXISTS:          return ErrorCode::AlreadyExists;
            case ERROR_FILE_EXISTS:             return ErrorCode::AlreadyExists;
            case ERROR_FILE_NOT_FOUND:          return ErrorCode::NotFound;
            default:                            return ErrorCode::Unknown;
            }
        }

        close();
        rawdat = reinterpret_cast<void*>(handle);
        return ErrorCode::Ok;
    }

    File::pos_t File::read(void* buf, pos_t size)
    {
        if(!isOpen())       return 0;

        auto ptr = reinterpret_cast<unsigned char*>(buf);
        pos_t total = 0;
        while(size > 0)
        {
            auto block = static_cast<DWORD>( std::min<pos_t>( size, std::numeric_limits<DWORD>::max() ) );
            DWORD result = block;
            if(!ReadFile(winfile, ptr, block, &result, nullptr))
                break;
            size -= result;
            ptr += result;
            total += result;
            if(result < block)
                break;
        }
        return total;
    }
    
    File::pos_t File::write(const void* buf, pos_t size)
    {
        if(!isOpen())       return 0;

        auto ptr = reinterpret_cast<const unsigned char*>(buf);
        pos_t total = 0;
        while(size > 0)
        {
            auto block = static_cast<DWORD>( std::min<pos_t>( size, std::numeric_limits<DWORD>::max() ) );
            DWORD result = block;
            if(!WriteFile(winfile, ptr, block, &result, nullptr))
                break;
            size -= result;
            ptr += result;
            total += result;
            if(result < block)
                break;
        }
        return total;
    }
    
    File::pos_t File::seek(pos_t pos, Origin origin)
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
        if(!SetFilePointerEx(winfile, in, &out, movemethod))
            return -1;

        return out.QuadPart;
    }

    File::pos_t File::tell()
    {
        if(!isOpen())           return -1;
        
        LARGE_INTEGER in, out;
        in.QuadPart = 0;
        if(!SetFilePointerEx(winfile, in, &out, FILE_CURRENT))
            return -1;

        return out.QuadPart;
    }
}