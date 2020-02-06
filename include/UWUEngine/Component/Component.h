#pragma once

#include <UWUEngine/NonCopyable.h>

namespace UWUEngine
{

using EntityID = unsigned;

class IComponent : public NonCopyable
{
public:
  virtual void Update() = 0;
  virtual void InitObject(EntityID ID) = 0;
  virtual void ShutdownObject(EntityID ID) = 0;
  virtual ~IComponent() = default;
};

template<class Comp, class Instance>
class Component : public IComponent
{
  Instance GetInstance(EntityID ID)
  {
    return Instance(dynamic_cast<Comp*>(this), ID);
  }
};

} // namespace UWUEngine