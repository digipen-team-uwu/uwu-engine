#pragma once
#include <UWUEngine/NonCopyable.h>

namespace UWUEngine
{

class System : NonCopyable
{
public:
  System() = default;
  virtual void Update() = 0;
  virtual ~System() = default;
};

}