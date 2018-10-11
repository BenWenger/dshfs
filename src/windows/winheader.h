#ifndef DSHFS_WINDOWS_WINHEADER_H_INCLUDED
#define DSHFS_WINDOWS_WINHEADER_H_INCLUDED

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#define STRICT
#define _UNICODE

#include <Windows.h>
#include <string>
#include "dshfs.h"
#include "dshfs/error.h"

namespace dshfs
{
    namespace winsupport
    {
        inline std::string wideToNarrow(const std::wstring& wide)
        {
            auto len = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), static_cast<int>(wide.size()), nullptr, 0, nullptr, nullptr);
            std::string narrow(len, '\0');
            WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), static_cast<int>(wide.size()), &narrow[0], static_cast<int>(narrow.size()), nullptr, nullptr);
            return narrow;
        }

        inline std::wstring narrowToWide(const std::string& narrow)
        {
            auto len = MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), static_cast<int>(narrow.size()), nullptr, 0);
            std::wstring wide(len, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), static_cast<int>(narrow.size()), &wide[0], static_cast<int>(wide.size()));
            return wide;
        }

        inline std::wstring makeWindowsFullPathName(const std::string& fn)
        {
            auto out = narrowToWide(Filename::makeAbsolute(fn));
            for(auto& i : out)
            {
                if(i == L'/')
                    i = L'\\';
            }
            return L"\\\\?\\" + out;
        }

        inline std::string fromWindowsName(std::wstring fn)
        {
            if(fn.substr(0,4) == L"\\\\?\\")
                fn = fn.substr(4);

            for(auto& i : fn)
            {
                if(i == L'\\')
                    i = L'/';
            }
            return wideToNarrow(fn);
        }

        inline void throwError(DWORD e, const std::string& msg)
        {
            switch(e)
            {
            case ERROR_SHARING_VIOLATION:       throw Err::NoAccess(msg);
            case ERROR_ALREADY_EXISTS:          throw Err::AlreadyExists(msg);
            case ERROR_FILE_EXISTS:             throw Err::AlreadyExists(msg);
            case ERROR_FILE_NOT_FOUND:          throw Err::NotFound(msg);
            default:                            throw Err::Unknown(msg);
            }
        }

        inline void throwLastError(const std::string& msg)
        {
            throwError(GetLastError(), msg);
        }
    }
}

#endif