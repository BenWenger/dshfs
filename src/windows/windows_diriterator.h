#ifndef DSHFS_WINDOWS_DIRITERATOR_H_INCLUDED
#define DSHFS_WINDOWS_DIRITERATOR_H_INCLUDED
#ifdef _WIN32

#include "dshfs/diriteratorimpl.h"
#include "winheader.h"

namespace dshfs
{
    class Windows_DirIterator : public DirIteratorImpl
    {
    public:
                Windows_DirIterator() = delete;
                Windows_DirIterator(std::string path);
        virtual ~Windows_DirIterator();
        
        virtual bool            isOk() override;
        virtual void            next(FileInfo& info) override;
        virtual void            fillInfo(FileInfo& info) override;

    private:
        bool                active;
        HANDLE              handle;
        WIN32_FIND_DATAW    data;
    };
}


#endif
#endif