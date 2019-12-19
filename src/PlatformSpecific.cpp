#include <UWUEngine/PlatformSpecific.h>

#ifdef _WIN64
namespace WindowsSpecific
{
  DWORD RegGetDword(HKEY hKey, const std::string& subKey, const std::string& value)
  {
    DWORD data{};
    DWORD dataSize = sizeof(data);
    LONG const retCode = RegGetValue
    (
      hKey,
      subKey.c_str(),
      value.c_str(),
      RRF_RT_REG_DWORD,
      nullptr,
      &data,
      &dataSize
    );
    if (retCode != ERROR_SUCCESS)
    {
#ifdef _MSVC
      throw std::exception{ "Cannot read DWORD from registry.", retCode };
#endif
    }
    return data;
  }
}
#endif