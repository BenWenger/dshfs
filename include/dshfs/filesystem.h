#ifndef DSHFS_FILESYSTEM_H_INCLUDED
#define DSHFS_FILESYSTEM_H_INCLUDED

#include <string>
#include "filemode.h"
#include "file.h"
#include <iostream>
#include "diriterator.h"

namespace dshfs
{
    class FileSystem
    {
    public:
        DSHFS_API virtual               ~FileSystem() {}

        DSHFS_API static FileSystem&    getInstance();

        DSHFS_API virtual std::string   getCurrentDirectory() const = 0;

        DSHFS_API virtual File::Ptr     openFile(const std::string& path, int mode = FileMode::rb) = 0;

        DSHFS_API virtual bool          isAbsolute(const std::string& path) const = 0;
        DSHFS_API virtual std::string   makeAbsolute(const std::string& path) const
        {
            if(isAbsolute(path))    return path;
            else                    return getCurrentDirectory() + path;
        }

        DSHFS_API virtual DirIterator   iterateDir(const std::string& dir) = 0;

        DSHFS_API virtual std::string   getExecutablePath() const = 0;

    protected:
        FileSystem() = default;
    private:
        FileSystem(const FileSystem&) = delete;
        FileSystem& operator = (const FileSystem&) = delete;
        FileSystem(FileSystem&&) = delete;
        FileSystem& operator = (FileSystem&&) = delete;
    };

    DSHFS_API extern FileSystem&      fs;
}


#endif