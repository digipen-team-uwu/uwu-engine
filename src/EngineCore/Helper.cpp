#include <UWUEngine/Helper.h>
#include <algorithm>

std::string str_toupper(std::string const& str)
{
  std::string new_str = str;
  std::transform(new_str.begin(), new_str.end(), new_str.begin(), ::toupper);
  return new_str;
}

std::string str_tolower(std::string const& str)
{
  std::string new_str = str;
  std::transform(new_str.begin(), new_str.end(), new_str.begin(), ::tolower);
  return new_str;
}

float intpow(float number, int exponent)
{
  float sum = 1;
  for (int i = 0; i < exponent; ++i)
  {
    sum *= number;
  }
  return sum;
}
