#pragma once

#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/Scene/Scene.h>
#include <unordered_map>

class SceneManager final : public BaseSystem<SceneManager>
{
public:
  SceneManager();
  void Update() override;

  static void NewScene(const std::string& name);

  static void SetNextScene(const std::string & name);
  static void SetNextScene(std::unordered_map<std::string, Scene>::const_iterator scene);

  static std::unordered_map<std::string, Scene>::const_iterator Begin();
  static std::unordered_map<std::string, Scene>::const_iterator End();

  ~SceneManager() override;

private:
  static std::unordered_map<std::string, Scene> scenes;
  static std::unordered_map<std::string, Scene>::const_iterator current;
  static std::unordered_map<std::string, Scene>::const_iterator next;
};
