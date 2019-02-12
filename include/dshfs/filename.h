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
        DSHFS_API               Filename() = default;
        DSHFS_API               Filename(const std::string& fullpath)       { setFullPath(fullpath);        }

        DSHFS_API std::string   getFullPath() const                         { return path + getFullName();  }
        DSHFS_API std::string   getPathPart() const                         { return path;                  }
        DSHFS_API std::string   getFullName() const;
        DSHFS_API std::string   getTitle() const                            { return title;                 }
        DSHFS_API std::string   getExt() const                              { return ext;                   }

        DSHFS_API void          setFullPath(const std::string& v);
        DSHFS_API void          setPathPart(const std::string& v);
        DSHFS_API void          setFullName(const std::string& v);
        DSHFS_API void          setTitle(const std::string& v)              { title = v;                    }
        DSHFS_API void          setExt(const std::string& v)                { ext = v;                      }

        DSHFS_API bool          resolveDots()                               { return privateResolveDots(path);                  }
        DSHFS_API void          makeAbsolute()                              { makeAbsolute(FileSystem::getInstance());          }
        DSHFS_API void          makeAbsolute(FileSystem& fsys)              { path = fsys.makeAbsolute(path);                   }
        DSHFS_API bool          fullResolve()                               { return fullResolve(FileSystem::getInstance());    }
        DSHFS_API bool          fullResolve(FileSystem& fsys);

        DSHFS_API static bool   fullResolve(std::string& path, FileSystem& fsys);
        DSHFS_API static bool   fullResolve(std::string& path)              { return fullResolve(path, FileSystem::getInstance());  }

        DSHFS_API static std::string normalizeSlash(const std::string& path);

    private:
        static bool                 privateResolveDots(std::string& v);
        void                        cleanPathSlash();
        std::string                 path;           // Must end in '/' unless its empty!
        std::string                 title;
        std::string                 ext;
    };

}


#endif