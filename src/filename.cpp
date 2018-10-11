
#include "dshfs.h"

namespace dshfs
{
    void Filename::clear()
    {
        paths.clear();
        title.clear();
        ext.clear();
    }

    void Filename::set(const std::string& fullpath)
    {
        clear();
        if(fullpath.empty())
            return;

        std::string full = fullpath;
        while(!full.empty())
        {
            auto pos = full.find('/');
            auto seg = full.substr(0,pos);
            if(pos == full.npos)
            {
                full.clear();
                setFileName(seg);
            }
            else
            {
                full = full.substr(pos+1);
                paths.push_back(seg);
            }
        }
    }

    void Filename::setFileName(const std::string& fn)
    {
        auto pos = fn.rfind('.');
        if(pos == fn.npos)
        {
            ext.clear();
            title = fn;
        }
        else
        {
            title = fn.substr(0,pos);
            ext = fn.substr(pos+1);
        }
    }

    void Filename::set(const std::string& path, const std::string& name)
    {
        // TODO
    }

    void Filename::set(const std::string& path, const std::string& title_, const std::string& ext_)
    {
        // TODO
    }




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