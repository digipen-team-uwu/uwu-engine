#pragma once

#include <UWUEngine/Scene/Scene.h>

static std::string name = "BrayanSBOX";

template<>
class Scene<name> : public IScene
{
public:
  ~Scene() override = default;
  void Load() override;
  void Init() override;
  void Update() override;
  void ShutDown() override;
  void UnLoad() override;
};
