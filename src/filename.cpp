
#include "dshfs.h"

#include <iostream>     // TODO remove this

namespace dshfs
{
    std::string Filename::getFullName() const
    {
        if(ext.empty())         return title;
        else                    return title + ext;
    }

    void Filename::setFullName(const std::string& v)
    {
        auto dot = v.rfind('.');
        if(dot == 0 || dot == v.npos || dot == v.length()-1)
        {
            title = v;
            ext.clear();
        }
        else
        {
            title = v.substr(0,dot);
            ext = v.substr(dot);
        }
    }

    void Filename::setPathPart(const std::string& v)
    {
        path = v;
        if(!v.empty() && v.back() != '/')
            path.push_back('/');
    }

    void Filename::setFullPath(const std::string& v)
    {
        auto pos = v.rfind('/');
        if(pos == v.npos)
        {
            path.clear();
            setFullName(v);
        }
        else
        {
            path = v.substr(0, pos+1);
            setFullName(v.substr(pos+1));
        }
    }
    
    bool Filename::fullResolve(FileSystem& fsys)
    {
        auto tmp = fsys.makeAbsolute(path);
        if(!privateResolveDots(tmp))
            return false;

        path = tmp;
        return true;
    }

    bool Filename::fullResolve(std::string& path, FileSystem& fsys)
    {
        Filename fn(path);
        if(!fn.fullResolve(fsys))
            return false;
        path = fn.getFullPath();
        return true;
    }

    namespace
    {
        class PathTraverse
        {
        public:
            PathTraverse(const std::string& p)
                : path(p), a(0), b(p.find('/'))
            {
                if(b != path.npos)
                    ++b;
            }

            operator bool () const
            {
                return (a < path.length()) && (a != std::string::npos);
            }

            PathTraverse& operator ++ ()
            {
                auto pos = path.find('/', b);
                if(pos == path.npos)
                {
                    a = b = std::string::npos;
                }
                else
                {
                    a = b;
                    b = pos+1;
                }
                return *this;
            }

            std::string operator * () const
            {
                return path.substr(a,b-a);
            }

        private:
            const std::string&  path;
            std::size_t         a;
            std::size_t         b;
        };

        bool dropLastPath(std::string& path)
        {
            if(path.empty())
                return false;

            auto pos = path.rfind('/', path.length() - 2);
            if(pos == path.npos)
                return false;

            path = path.substr(0,pos+1);
            return true;
        }
    }

    bool Filename::privateResolveDots(std::string& v)
    {
        std::string out;

        for(PathTraverse pt(v); pt; ++pt)
        {
            auto seg = *pt;
            if(seg == "../")
            {
                if(!dropLastPath(out))
                    return false;
            }
            else if(seg != "./")
                out += seg;
        }

        v = std::move(out);
        return true;
    }

}