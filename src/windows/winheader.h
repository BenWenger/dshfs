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

namespace dshfs
{
    namespace winsupport
    {
        inline std::string wideToNarrow(const std::wstring& wide)
        {
            auto len = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), wide.size(), nullptr, 0, nullptr, nullptr);
            std::string narrow(len, '\0');
            WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), wide.size(), &narrow[0], narrow.size(), nullptr, nullptr);
            return narrow;
        }

        inline std::wstring narrowToWide(const std::string& narrow)
        {
            auto len = MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), narrow.size(), nullptr, 0);
            std::wstring wide(len, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), narrow.size(), &wide[0], wide.size());
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
    }
}

#endif