#ifndef DSHFS_ERROR_H_INCLUDED
#define DSHFS_ERROR_H_INCLUDED

#include <stdexcept>

namespace dshfs
{
    class Error : public std::runtime_error
    {
    public:
        explicit Error(const std::string& whatarg) : runtime_error(whatarg) {}
        explicit Error(const char* whatarg) : runtime_error(whatarg) {}
        virtual ~Error() = default;
        Error() = delete;
        Error(const Error&) = default;
        Error& operator = (const Error&) = default;
    };

#define DSHFS_MAKE_ERROR_SUBCLASS(ClassName, msg)                                               \
    class ClassName : public Error {                                                            \
        public:                                                                                 \
            explicit ClassName(const std::string& whatarg="") : Error(msg + ("  " + whatarg)) {}\
    }

    namespace Err
    {
        DSHFS_MAKE_ERROR_SUBCLASS(NoAccess,         "Unable to gain access to file.");
        DSHFS_MAKE_ERROR_SUBCLASS(AlreadyExists,    "File already exists.");
        DSHFS_MAKE_ERROR_SUBCLASS(NotFound,         "File not found.");
        DSHFS_MAKE_ERROR_SUBCLASS(Unknown,          "Unknown error.");
        DSHFS_MAKE_ERROR_SUBCLASS(BadParams,        "Bad parameters passed to function call.");
        DSHFS_MAKE_ERROR_SUBCLASS(BadState,         "Object was not ready to be used.");
    }

#undef DSHFS_MAKE_ERROR_SUBCLASS
}


#endif