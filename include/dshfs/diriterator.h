#ifndef DSHFS_DIRITERATOR_H_INCLUDED
#define DSHFS_DIRITERATOR_H_INCLUDED

#include <string>
#include <memory>
#include "exportdefine.h"
#include "fileinfo.h"
#include "diriteratorimpl.h"

namespace dshfs
{
    class DirIterator
    {
    public:
        typedef std::unique_ptr<DirIteratorImpl>        impl_t;

        DSHFS_API DirIterator() = default;
        DSHFS_API ~DirIterator();
        DSHFS_API operator bool() const;
        DSHFS_API const FileInfo& get() const;
        DSHFS_API const FileInfo& operator * () const     { return get();     }
        DSHFS_API const FileInfo* operator -> () const    { return &get();    }
        DSHFS_API DirIterator& operator ++ ();
        
        DSHFS_API DirIterator(DirIterator&&) = default;
        DSHFS_API DirIterator& operator = (DirIterator&&) = default;

        DSHFS_API DirIterator(impl_t&& impl);

    private:
        impl_t                      iter;
        FileInfo                    info;

        // no copying
        DSHFS_API DirIterator(const DirIterator&) = delete;
        DSHFS_API DirIterator& operator = (const DirIterator&) = delete;
    };
}


#endif