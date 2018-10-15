#ifndef DSHFS_FILENAME_H_INCLUDED
#define DSHFS_FILENAME_H_INCLUDED

#include <string>
#include <vector>
#include "dshfs/filesystem.h"

namespace dshfs
{
    class Filename
    {
    public:
        DLL                     Filename() = default;
        DLL                     Filename(const std::string& fullpath)       { setFullPath(fullpath);        }

        DLL std::string         getFullPath() const                         { return path + getFullName();  }
        DLL std::string         getPathPart() const                         { return path;                  }
        DLL std::string         getFullName() const;
        DLL std::string         getTitle() const                            { return title;                 }
        DLL std::string         getExt() const                              { return ext;                   }

        DLL void                setFullPath(const std::string& v);
        DLL void                setPathPart(const std::string& v);
        DLL void                setFullName(const std::string& v);
        DLL void                setTitle(const std::string& v)              { title = v;                    }
        DLL void                setExt(const std::string& v)                { ext = v;                      }

        DLL bool                resolveDots()                               { return privateResolveDots(path);                  }
        DLL void                makeAbsolute()                              { makeAbsolute(FileSystem::getInstance());          }
        DLL void                makeAbsolute(FileSystem& fsys)              { path = fsys.makeAbsolute(path);                   }
        DLL bool                fullResolve()                               { return fullResolve(FileSystem::getInstance());    }
        DLL bool                fullResolve(FileSystem& fsys);

        DLL static bool         fullResolve(std::string& path, FileSystem& fsys);
        DLL static bool         fullResolve(std::string& path)              { return fullResolve(path, FileSystem::getInstance());  }

    private:
        static bool                 privateResolveDots(std::string& v);
        std::string                 path;           // Must end in '/' unless its empty!
        std::string                 title;
        std::string                 ext;
    };

}


#endif