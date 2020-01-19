#include <UWUEngine/Helper.h>

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

//from Physics Assignment 1, check if a float is close enough to another float to basically be equal
bool near(float x, float y) 
{
    return std::abs(x - y) < 1e-4f;
}