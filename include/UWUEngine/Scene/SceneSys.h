#pragma once

#include <UWUEngine/System.h>
#include <UWUEngine/Scene/Scene.h>
#include <UWUEngine/Event/Event.h>
#include <unordered_map>

namespace UWUEngine
{
  class SceneSys final : public System
  {
  public:
    SceneSys(ISpace* p);
    void Update() override;

    void NewScene(const std::string& name);

    void SetNextScene(const std::string& name);
    void SetNextScene(std::unordered_map<std::string, Scene>::const_iterator scene);

    void Reload() const;

    const std::string& GetCurrentName();
    const SceneSettings& GetCurrentSettings();

    std::unordered_map<std::string, Scene>::const_iterator Begin();
    std::unordered_map<std::string, Scene>::const_iterator End();

    ~SceneSys() override;

  private:
    std::unordered_map<std::string, Scene> scenes{};
    std::unordered_map<std::string, Scene>::const_iterator current{};
    std::unordered_map<std::string, Scene>::const_iterator next{};

    void OnSetNextScene(const Event<EventType::SetNextScene>& event);
    static EventListener<EventType::SetNextScene> listener_;
  };
}