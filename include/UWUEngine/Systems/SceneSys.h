#pragma once

#include <UWUEngine/System.h>
#include <UWUEngine/Systems/EventSys.h>

#include <unordered_map>
#include <string>

namespace UWUEngine
{
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
    EventListener<EventType::SetNextScene> listener_;
  };
}
