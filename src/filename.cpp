
#include "dshfs.h"

namespace dshfs
{
    bool Filename::isAbsolute(const std::string& path)
    {
        return fs.isFilenameAbsolute(path);         // TODO use instance call?
    }

    std::string Filename::makeAbsolute(const std::string& path)
    {
        if( isAbsolute(path) )
            return path;
        return fs.getCurrentDirectory() + path;     // TODO use instance call?
    }

}