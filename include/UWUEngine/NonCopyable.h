#pragma once

namespace UWUEngine
{

class NonCopyable
{
public:
  NonCopyable(const NonCopyable&) = delete; // No copies
  NonCopyable& operator = (const NonCopyable&) = delete; // No self-assignment

protected:
  NonCopyable() = default;
  ~NonCopyable() = default; // Protected non-virtual destructor
};

}
