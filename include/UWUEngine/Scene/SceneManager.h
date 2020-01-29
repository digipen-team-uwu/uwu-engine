#pragma once

#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/Scene/Scene.h>
#include <unordered_map>

class SceneManager : public BaseSystem<SceneManager>
{
public:
  void Fetch();
  void AddScene(IScene* scene);
  void Update() override;
  ~SceneManager() override;

private:
  std::unordered_map<std::string, IScene*> scenes;
};
