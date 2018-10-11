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

        DLL DirIterator() = default;
        DLL ~DirIterator();
        DLL operator bool() const;
        DLL const FileInfo& get() const;
        DLL const FileInfo& operator * () const     { return get();     }
        DLL const FileInfo* operator -> () const    { return &get();    }
        DLL DirIterator& operator ++ ();
        
        DLL DirIterator(DirIterator&&) = default;
        DLL DirIterator& operator = (DirIterator&&) = default;

        DLL DirIterator(impl_t&& impl);

    private:
        impl_t                      iter;
        FileInfo                    info;

        // no copying
        DLL DirIterator(const DirIterator&) = delete;
        DLL DirIterator& operator = (const DirIterator&) = delete;
    };
}


#endif