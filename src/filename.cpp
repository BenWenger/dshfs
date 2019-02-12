
#include "dshfs.h"

namespace dshfs
{
    std::string Filename::normalizeSlash(const std::string& path)
    {
        std::string out = path;
        for(auto& i : out)
        {
            if(i == '\\')
                i = '/';
        }
        return out;
    }

    std::string Filename::getFullName() const
    {
        if(ext.empty())         return title;
        else                    return title + ext;
    }

    void Filename::setFullName(const std::string& name)
    {
        auto str = normalizeSlash(name);
        auto pos = str.rfind('/');
        if(pos != str.npos)
        {
            path = path + str.substr(0, pos+1);
            str = str.substr(pos+1);
        }

        pos = str.rfind('.');
        if(pos == 0 || pos == str.npos || pos == str.length()-1)
        {
            setTitle(str);
            ext.clear();
        }
        else
        {
            setTitle(str.substr(0,pos));
            setExt(str.substr(pos));
        }
    }

    void Filename::setPathPart(const std::string& v)
    {
        path = v;
        cleanPathSlash();
    }
    
    void Filename::cleanPathSlash()
    {
        path = normalizeSlash(path);
        if(!path.empty() && path.back() != '/')
            path.push_back('/');
    }

    void Filename::setFullPath(const std::string& fullpath)
    {
        path.clear();
        setFullName(fullpath);
    }
    
    bool Filename::fullResolve(FileSystem& fsys)
    {
        auto tmp = fsys.makeAbsolute(path);
        if(!privateResolveDots(tmp))
            return false;

        path = tmp;
        cleanPathSlash();
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