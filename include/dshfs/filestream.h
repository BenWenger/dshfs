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
        DSHFS_API           FileStream(const std::string& path, int mode = FileMode::rt);
        DSHFS_API virtual   ~FileStream();

    private:
        FileBuf*            buffer;
        FileStream(const FileStream&) = delete;
        FileStream& operator = (const FileStream&) = delete;
    };
}

#endif