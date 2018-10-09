#ifndef DSHFS_FILESTREAM_H_INCLUDED
#define DSHFS_FILESTREAM_H_INCLUDED

#include <iostream>
#include "exportdefine.h"
#include "filemode.h"
#include "filebuf.h"

namespace dshfs
{
    class FileStream : public std::iostream
    {
    public:
        DLL FileStream(const std::string& path, int mode = FileMode::r, bool convertLineBreaks = true);
        DLL virtual ~FileStream();

    private:
        FileBuf*            buffer;
        FileStream(const FileStream&) = delete;
        FileStream& operator = (const FileStream&) = delete;
    };
}

#endif