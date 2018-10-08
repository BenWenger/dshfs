#ifndef DSHFS_FILESYSTEM_H_INCLUDED
#define DSHFS_FILESYSTEM_H_INCLUDED

namespace dshfs
{

    class FileSystem
    {
    public:
        static inline FileSystem&       instance()      { static FileSystem theFs;      return theFs;   }

        DLL std::string                 getCurrentDirectory() const;


    private:
        DLL FileSystem();
        DLL FileSystem(const FileSystem&)   = delete;
        DLL FileSystem(FileSystem&&)        = delete;
        DLL ~FileSystem();

        void*       rawdat;
    };

    DLL extern FileSystem&      fs;
}


#endif