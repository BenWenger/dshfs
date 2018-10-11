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

        DLL Filename() = default;
        DLL Filename(const std::string& fullpath)                                                   { set(fullpath);            }
        DLL Filename(const std::string& path, const std::string& name)                              { set(path, name);          }
        DLL Filename(const std::string& path, const std::string& name, const std::string& ext)      { set(path, name, ext);     }
        
        DLL void clear();
        DLL void set(const std::string& fullpath);
        DLL void set(const std::string& path, const std::string& name);
        DLL void set(const std::string& path, const std::string& name, const std::string& ext);

        DLL void setFileName(const std::string& fn);

    private:
        std::vector<std::string>    paths;
        std::string                 title;
        std::string                 ext;
    };

}


#endif