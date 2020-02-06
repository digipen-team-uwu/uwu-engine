#pragma once
#include <UWUEngine/NonCopyable.h>

namespace UWUEngine
{

class ISpace;

class System : NonCopyable
{
public:
  System(ISpace* p) : parent(p) {}
  virtual ~System() = 0;
  virtual void Update() = 0;

  template <class T>
  T& Get();
private:
  ISpace* parent;
};

} // namespace UWUEngine

#include <UWUEngine/System.template.cpp>