
#include "dshfs/filebuf.h"
#include "dshfs/filesystem.h"

namespace dshfs
{
    FileBuf::FileBuf(const std::string& path, int mode, bool convertLineBreaks)
        : std::filebuf( )
        , eofVal( traits_type::eof() )
        , file( FileSystem::getInstance().openFile(path,mode) )
        , inTextMode(convertLineBreaks)
    {
        clearPtrs();
    }

    FileBuf::~FileBuf()
    {
        try
        {
            flushBuffer();
        }catch(...) {}
    }
    
    auto FileBuf::underflow() -> int_type
    {
        if(!flushBuffer())
        {
            clearPtrs();
            return eofVal;
        }
        clearP();
        auto siz = file->read(buffer, bufferSize);
        if(siz > 0)
        {
            if(inTextMode)
            {
                File::pos_t src = 1, dst = 0;
                for(; src < siz; ++src)
                {
                    if(buffer[src-1] != '\r' || buffer[src] != '\n')
                        ++dst;
                    buffer[dst] = buffer[src];
                }
                // nasty case -- if the last character was '\r', we need to "unget" it
                if(buffer[src-1] == '\r')
                {
                    --dst;
                    file->seek(-1, File::Origin::Cur);  // TODO - dunno if this is a good idea
                }
            }
            setg(buffer, buffer, buffer + siz);
            return buffer[0];
        }
        clearG();
        return eofVal;
    }
    
    auto FileBuf::overflow(int_type ch) -> int_type
    {
        if(!flushBuffer(ch))
        {
            clearPtrs();
            return eofVal;
        }
        clearG();
        setp(buffer, buffer + bufferSize);
        return 0;
    }
    
    auto FileBuf::sync() -> int_type
    {
        int_type out = flushBuffer() ? 0 : -1;
        clearPtrs();
        return out;
    }
    
    auto FileBuf::seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode md) -> pos_type
    {
        if(!flushBuffer())
            return -1;

        clearPtrs();
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

    bool FileBuf::flushBuffer(int_type extra)
    {
        // 
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