
#include "dshfs/filebuf.h"
#include "dshfs/filesystem.h"

namespace dshfs
{
    FileBuf::FileBuf(const std::string& path, int mode)
        : std::filebuf( )
        , eofVal( traits_type::eof() )
        , file( FileSystem::getInstance().openFile(path,mode) )
    {
        setp(outBuf, outBuf + bufferSize);
        setg(nullptr, nullptr, nullptr);
    }

    FileBuf::~FileBuf()
    {
    }
    
    auto FileBuf::underflow() -> int_type
    {
        auto siz = file->read(inBuf, bufferSize);
        if(siz >= 0)
        {
            setg(inBuf, inBuf, inBuf + siz);
            if(siz > 0)
                return inBuf[0];
        }
        setg(nullptr, nullptr, nullptr);
        return eofVal;
    }
    
    auto FileBuf::overflow(int_type ch) -> int_type
    {
        if(flushOutput(ch))
            return 0;
        else
        {
            setp(outBuf, outBuf);
            return eofVal;
        }
    }
    
    auto FileBuf::sync() -> int_type
    {
        setg(nullptr,nullptr,nullptr);
        return flushOutput(eofVal) ? 0 : -1;
    }
    
    auto FileBuf::seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode md) -> pos_type
    {
        File::Origin mode;
        switch(dir)
        {
        case std::ios_base::beg:    mode = File::Origin::Set;       break;
        case std::ios_base::cur:    mode = File::Origin::Cur;       break;
        case std::ios_base::end:    mode = File::Origin::End;       break;
        default:                    return -1;
        }
        sync();
        return static_cast<pos_type>( file->seek( static_cast<File::pos_t>(off), mode ) );
    }

    auto FileBuf::seekpos(pos_type pos, std::ios_base::openmode md) -> pos_type
    {
        return seekoff( static_cast<off_type>(pos), std::ios_base::beg, md );
    }

    bool FileBuf::flushOutput(int_type extra)
    {
        bool success = false;
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
            success = (written == size);
        }catch(...) {}

        if(success)
            setp(outBuf, outBuf + bufferSize);
        return success;
    }
}