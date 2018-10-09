#ifndef DSHFS_FILEBUF_H_INCLUDED
#define DSHFS_FILEBUF_H_INCLUDED

#include <iostream>
#include <fstream>
#include "exportdefine.h"
#include "file.h"

namespace dshfs
{
    class FileBuf : public std::filebuf
    {
    public:
        DLL FileBuf(const std::string& path, int mode, bool convertLineBreaks);
        DLL ~FileBuf();

    protected:
        DLL virtual int_type    underflow() override;
        DLL virtual int_type    overflow(int_type ch) override;
        DLL virtual int_type    sync() override;
        DLL virtual pos_type    seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode);
        DLL virtual pos_type    seekpos(pos_type pos, std::ios_base::openmode);

    private:
        FileBuf(const FileBuf&) = delete;
        FileBuf& operator = (const FileBuf&) = delete;

        static const int        bufferSize = 10;
        const int               eofVal;
        File::Ptr               file;
        char                    buffer[bufferSize+1];
        bool                    inTextMode;

        bool    flushBuffer(int_type extra);
        bool    flushBuffer()           { return flushBuffer(eofVal);       }
        void    clearG()                { setg(nullptr,nullptr,nullptr);    }
        void    clearP()                { setp(nullptr,nullptr);            }
        void    clearPtrs()             { clearG(); clearP();               }
    };
}

#endif