/*
 * WARNING: THIS FILE CONTAINS WINDOWS.H. ONLY INCLUDE IT IN A COMPILED FILE, NOT A HEADER
 */

#pragma once
#include <string>

#ifdef _WIN64
#include <windows.h>
#elif defined(__unix__)
#include <unistd.h>
#endif

#ifdef _WIN64
namespace WindowsSpecific
{
  DWORD RegGetDword(HKEY hKey, const std::string& subKey, const std::string& value);
}
#endif