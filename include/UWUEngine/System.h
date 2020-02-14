#pragma once
#include <UWUEngine/NonCopyable.h>

namespace UWUEngine
{

class ISpace;

class System : NonCopyable
{
public:
  System(ISpace* p) : parent(p) {}
  virtual ~System() = default;
  virtual void Update() {}

  template <class T>
  T& Get();
protected:
  ISpace* parent;
};

} // namespace UWUEngine

#include <UWUEngine/System.template.cpp>