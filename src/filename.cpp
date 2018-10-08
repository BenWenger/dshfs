
#include "dshfs.h"

namespace dshfs
{
    std::string Filename::makeAbsolute(const std::string& path)
    {
        if( isAbsolute(path) )
            return path;
        return fs.getCurrentDirectory() + path;
    }

}