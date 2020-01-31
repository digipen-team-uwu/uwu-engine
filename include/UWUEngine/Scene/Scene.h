#pragma once
#include <string>
#include <UWUEngine/Serialization.h>

class Scene
{
public:
  Scene(std::string name);
  virtual ~Scene() = default;

  virtual void Load() const;
  virtual void UnLoad() const;

  const std::string& GetName() const;

private:
  std::string name_;
};
