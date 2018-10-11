
#include "dshfs/diriterator.h"
#include "dshfs/error.h"

namespace dshfs
{
    DirIterator::DirIterator(impl_t&& impl)
        : iter(std::move(impl))
    {
        if(*this)
            iter->fillInfo(info);
    }

    DirIterator::~DirIterator()
    {}

    DirIterator::operator bool() const
    {
        if(iter)
            return iter->isOk();
        return false;
    }

    const FileInfo& DirIterator::get() const
    {
        if(*this)   return info;
        throw Err::BadState("  DirIterator::get");
    }
    
    DirIterator& DirIterator::operator ++ ()
    {
        if(*this)
            iter->next(info);
        return *this;
    }
}
