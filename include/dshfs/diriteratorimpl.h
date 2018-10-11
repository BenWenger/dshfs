#ifndef DSHFS_DIRITERATORIMPL_H_INCLUDED
#define DSHFS_DIRITERATORIMPL_H_INCLUDED

#include <string>
#include "dshfs/fileinfo.h"

namespace dshfs
{
    class DirIteratorImpl
    {
    public:
                                DirIteratorImpl() = default;
        virtual                 ~DirIteratorImpl() {}
        virtual bool            isOk() = 0;
        virtual void            next(FileInfo& info) = 0;
        virtual void            fillInfo(FileInfo& info) = 0;

    private:
        // no copying
        DirIteratorImpl(const DirIteratorImpl&) = delete;
        DirIteratorImpl& operator = (const DirIteratorImpl&) = delete;
        DirIteratorImpl(DirIteratorImpl&&) = delete;
        DirIteratorImpl& operator = (DirIteratorImpl&&) = delete;
    };
}


#endif