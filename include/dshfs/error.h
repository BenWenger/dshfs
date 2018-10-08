#ifndef DSHFS_ERROR_H_INCLUDED
#define DSHFS_ERROR_H_INCLUDED

namespace dshfs
{
    enum ErrorCode
    {
        Ok,
        BadParams,
        NoAccess,
        NotFound,
        AlreadyExists,
        Unknown
    };
}


#endif