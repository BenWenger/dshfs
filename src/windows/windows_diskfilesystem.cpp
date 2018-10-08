#ifdef _WIN32
#include "windows_diskfilesystem.h"
#include "windows_diskfile.h"
#include "dshfs/error.h"

namespace dshfs
{
    FileSystem& fs = FileSystem::getInstance();


    FileSystem& FileSystem::getInstance()
    {
        static Windows_DiskFileSystem theFs;
        return theFs;
    }

    Windows_DiskFileSystem::Windows_DiskFileSystem()
    {
        auto len = GetCurrentDirectoryW(0,nullptr);
        std::wstring path(len, L'\0');
        len = GetCurrentDirectoryW( len, &path[0] );        // cheesing std::string a bit
        path.resize(len);

        path.push_back('/');

        curDirectory = winsupport::fromWindowsName(path);
    }

    std::string Windows_DiskFileSystem::getCurrentDirectory() const 
    {
        return curDirectory;
    }

    File::Ptr Windows_DiskFileSystem::openFile(const std::string& path, int mode)
    {
        return Windows_DiskFile::open(path,mode);
    }
    
    bool Windows_DiskFileSystem::isFilenameAbsolute(const std::string& filename) const
    {
        if(filename.length() < 2)   return false;
        return filename[1] == ':';
    }
}

#endif