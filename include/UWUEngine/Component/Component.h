#pragma once

#include <UWUEngine/NonCopyable.h>

namespace UWUEngine
{

using EntityID = unsigned;

class Component : NonCopyable
{
public:
  virtual void Update() = 0;
  virtual void InitObject(EntityID ID) = 0;
  virtual void ShutdownObject(EntityID ID) = 0;
  virtual ~Component() = default;
};

}