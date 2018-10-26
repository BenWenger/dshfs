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
        DSHFS_API FileBuf(const std::string& path, int mode);
        DSHFS_API ~FileBuf();

    protected:
        DSHFS_API virtual int_type          underflow() override;
        DSHFS_API virtual int_type          overflow(int_type ch) override;
        DSHFS_API virtual int_type          sync() override;
        DSHFS_API virtual pos_type          seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode) override;
        DSHFS_API virtual pos_type          seekpos(pos_type pos, std::ios_base::openmode) override;
        DSHFS_API virtual std::streamsize   xsgetn(char* buf, std::streamsize count) override;
        DSHFS_API virtual std::streamsize   xsputn(const char* buf, std::streamsize count) override;

    private:
        FileBuf(const FileBuf&) = delete;
        FileBuf& operator = (const FileBuf&) = delete;
        
        enum class Mode
        {
            Neutral,
            Reading,
            Writing
        };

        static const int        bufferSize = 1024;
        const int               eofVal;
        File::Ptr               file;
        Mode                    curMode;
        char                    buffer[bufferSize+1];

        bool                    flushOutput(int_type extra);
        bool                    flushInput();
        bool                    flushAll(int_type extra);
        bool                    flushAll()                      { return flushAll(eofVal);          }
        void                    clearPtrs();
    };
}

#endif