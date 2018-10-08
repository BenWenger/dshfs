
#include "winheader.h"

namespace dshfs
{
    bool Filename::isAbsolute(const std::string& path)
    {
        if(path.length() < 2)   return false;
        return path[1] == ':';
    }

}