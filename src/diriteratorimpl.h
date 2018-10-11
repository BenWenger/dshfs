#ifndef DSHFS_DIRITERATORIMPL_H_INCLUDED
#define DSHFS_DIRITERATORIMPL_H_INCLUDED

#include <string>
#include "dshfs/fileinfo.h"

namespace dshfs
{
    class DirIteratorImpl
    {
    public:
        virtual                 ~DirIteratorImpl() {}
        virtual bool            isOk() = 0;
        virtual std::string     getName() = 0;
        virtual FileInfo        getInfo() = 0;
        virtual bool            next() = 0;

    private:
        // no copying
        DLL DirIterator(const DirIterator&) = delete;
        DLL DirIterator& operator = (const DirIterator&) = delete;
        DirIterator(DirIterator&&) = delete;
        DirIterator& operator = (DirIterator&&) = delete;
    };
}


#endif