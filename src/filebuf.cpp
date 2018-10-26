
#include "dshfs/filebuf.h"
#include "dshfs/filesystem.h"

namespace dshfs
{
    FileBuf::FileBuf(const std::string& path, int mode)
        : std::filebuf( )
        , eofVal( traits_type::eof() )
        , file( FileSystem::getInstance().openFile(path,mode) )
    {
        clearPtrs();
    }

    FileBuf::~FileBuf()
    {
        try
        {
            flushAll();
        }catch(...) {}
    }
    
    auto FileBuf::underflow() -> int_type
    {
        if(!flushAll())
        {
            return eofVal;
        }

        auto siz = file->read(buffer, bufferSize);
        if(siz > 0)
        {
            setg(buffer, buffer, buffer + siz);
            curMode = Mode::Reading;
            return buffer[0];
        }
        return eofVal;
    }
    
    auto FileBuf::overflow(int_type ch) -> int_type
    {
        if(!flushAll(ch))
            return eofVal;
        setp(buffer, buffer + bufferSize);
        curMode = Mode::Writing;
        return 0;
    }
    
    auto FileBuf::sync() -> int_type
    {
        return flushAll() ? 0 : -1;
    }
    
    auto FileBuf::seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode md) -> pos_type
    {
        if(!flushAll())
            return -1;

        File::Origin mode;
        switch(dir)
        {
        case std::ios_base::beg:    mode = File::Origin::Set;       break;
        case std::ios_base::cur:    mode = File::Origin::Cur;       break;
        case std::ios_base::end:    mode = File::Origin::End;       break;
        default:                    return -1;
        }
        return static_cast<pos_type>( file->seek( static_cast<File::pos_t>(off), mode ) );
    }

    auto FileBuf::seekpos(pos_type pos, std::ios_base::openmode md) -> pos_type
    {
        return seekoff( static_cast<off_type>(pos), std::ios_base::beg, md );
    }

    bool FileBuf::flushOutput(int_type extra)
    {
        if(curMode != Mode::Writing)
        {
            if(extra != eofVal) {
                char v = static_cast<char>(extra);
                return file->write(&v,1) == 1;
            }
            return true;
        }
        
        try
        {
            auto pb = pbase();
            auto pp = pptr();
            if(extra != eofVal)
            {
                *pp = static_cast<char>(extra);
                ++pp;
            }
            File::pos_t size = pp - pb;

            auto written = file->write( pb, size );
            return (written == size);
        }catch(...) {}

        return false;
    }
    
    bool FileBuf::flushInput()
    {
        if(curMode != Mode::Reading)
            return true;

        auto torewind = gptr() - egptr();
        return file->seek(static_cast<File::pos_t>(torewind), File::Origin::Cur) >= 0;
    }
    
    bool FileBuf::flushAll(int_type extra)
    {
        bool res = flushInput();
        res = flushOutput(extra) && res;
        clearPtrs();
        return res;
    }

    void FileBuf::clearPtrs()
    {
        setp(nullptr,nullptr);
        setg(nullptr,nullptr,nullptr);
        curMode = Mode::Neutral;
    }

    
    //////////////////////////////////////
    std::streamsize FileBuf::xsgetn(char* buf, std::streamsize count)
    {
        if(!flushAll())     return 0;
        return static_cast<std::streamsize>( file->read(buf, static_cast<File::pos_t>(count)) );
    }
    
    std::streamsize FileBuf::xsputn(const char* buf, std::streamsize count)
    {
        if(!flushAll())     return 0;
        return static_cast<std::streamsize>( file->write(buf, static_cast<File::pos_t>(count)) );
    }
}