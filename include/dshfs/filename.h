#ifndef DSHFS_FILENAME_H_INCLUDED
#define DSHFS_FILENAME_H_INCLUDED

#include <string>
#include <vector>

namespace dshfs
{

    class Filename
    {
    public:

        DLL static bool         isAbsolute(const std::string& path);
        DLL static std::string  makeAbsolute(const std::string& path);

        // TODO fill this out later


    private:

    };

}


#endif