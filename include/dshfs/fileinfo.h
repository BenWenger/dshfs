#ifndef DSHFS_FILEINFO_H_INCLUDED
#define DSHFS_FILEINFO_H_INCLUDED

#include <string>

namespace dshfs
{
    struct FileInfo
    {
        std::string         fileName;
        bool                directory;      // TODO do something better with this
        // TODO also add things like last modified date, etc

        inline bool         isDir() const { return directory;   }
    };
}


#endif