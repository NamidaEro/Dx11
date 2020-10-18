#pragma once

#include "Includes.h"

#include <fstream>
#include <corecrt_wstring.h>

char* WCharToChar(const wchar_t* pwstrSrc)
{
#if !defined _DEBUG
    int len = 0;
    len = (wcslen(pwstrSrc) + 1) * 2;
    char* pstr = (char*)malloc(sizeof(char) * len);

    WideCharToMultiByte(949, 0, pwstrSrc, -1, pstr, len, NULL, NULL);
#else

    int nLen = wcslen(pwstrSrc);

    char* pstr = (char*)malloc(sizeof(char) * nLen + 1);
    wcstombs(pstr, pwstrSrc, nLen + 1);
#endif

    return pstr;
}


//  char -> wchar
wchar_t* CharToWChar(const char* pstrSrc)
{
    int nLen = strlen(pstrSrc) + 1;

    wchar_t* pwstr = (wchar_t*)malloc(sizeof(wchar_t) * nLen);
    mbstowcs(pwstr, pstrSrc, nLen);

    return pwstr;
}