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
        DLL virtual                 ~FileSystem() {}

        DLL static FileSystem&      getInstance();

        DLL virtual std::string     getCurrentDirectory() const = 0;

        DLL virtual File::Ptr       openFile(const std::string& path, int mode = FileMode::rb) = 0;

        DLL virtual bool            isAbsolute(const std::string& path) const = 0;
        DLL virtual std::string     makeAbsolute(const std::string& path) const
        {
            if(isAbsolute(path))    return path;
            else                    return getCurrentDirectory() + path;
        }

        DLL virtual DirIterator     iterateDir(const std::string& dir) = 0;

    protected:
        FileSystem() = default;
    private:
        FileSystem(const FileSystem&) = delete;
        FileSystem& operator = (const FileSystem&) = delete;
        FileSystem(FileSystem&&) = delete;
        FileSystem& operator = (FileSystem&&) = delete;
    };

    DLL extern FileSystem&      fs;
}


#endif