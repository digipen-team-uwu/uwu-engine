#pragma once
#include <string>
#include <UWUEngine/Serialization.h>

struct SceneSettings
{
  enum class State
  {
    Inherit,
    Activate,
    DeActivate
  };
  State Lighting{ State::Inherit };
  State DynamicCamera{ State::Inherit };

  void Apply() const;
};

class Scene
{
public:
  Scene(std::string name);
  Scene(std::string name, const SceneSettings& settings);
  virtual ~Scene() = default;

  virtual void Load() const;
  virtual void UnLoad() const;

  const std::string& GetName() const;
  const SceneSettings& GetSettings() const;

private:
  SceneSettings settings_{};
  std::string name_;
};
