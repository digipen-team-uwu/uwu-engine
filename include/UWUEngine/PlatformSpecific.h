/*
 * WARNING: THIS FILE CONTAINS WINDOWS.H. ONLY INCLUDE IT IN A COMPILED FILE, NOT A HEADER
 */

#pragma once
#include <string>

#ifdef _WIN64
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Shlobj_core.h>
namespace WindowsSpecific {}
using namespace WindowsSpecific;
#elif defined(__unix__)
#include <unistd.h>
#endif

#ifdef _WIN64
namespace WindowsSpecific
{
  DWORD RegGetDword(HKEY hKey, const std::string& subKey, const std::string& value);
}
#endif