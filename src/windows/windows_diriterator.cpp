#ifdef _WIN32
#include "windows_diriterator.h"
#include "dshfs/filename.h"

namespace dshfs
{
    
    Windows_DirIterator::Windows_DirIterator(std::string path)
    {
        path = Filename::makeAbsolute(path);
        if(path.back() != '/')
            path.push_back('/');
        path.push_back('*');

        auto winpath = winsupport::makeWindowsFullPathName(path);
        handle = FindFirstFileW( winpath.c_str(), &data );

        if(handle == INVALID_HANDLE_VALUE)
            winsupport::throwLastError("When searching directory '" + path + "'");

        active = true;
    }

    Windows_DirIterator::~Windows_DirIterator()
    {
        if(handle != INVALID_HANDLE_VALUE)
            FindClose(handle);
    }
        
    bool Windows_DirIterator::isOk()
    {
        return active;
    }
    
    void Windows_DirIterator::fillInfo(FileInfo& info)
    {
        info.fileName = winsupport::fromWindowsName( data.cFileName );
        info.directory = (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    }
    
    void Windows_DirIterator::next(FileInfo& info)
    {
        auto success = FindNextFileW(handle, &data);
        if(success)
            fillInfo(info);
        else
        {
            active = false;
            auto e = GetLastError();
            if(e != ERROR_NO_MORE_FILES)
                winsupport::throwError(e, "When iterating directory.");
        }
    }
}

#endif