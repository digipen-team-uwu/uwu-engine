#include <UWUEngine/Scene/SceneSys.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/Graphics/CameraSys.h>

#include <filesystem>

static const std::string scenePath{ "data/levels" };
static const std::string initialSceneName = "BrayanSBOX";

using namespace UWUEngine;

SceneSys::SceneSys(ISpace* p):
System(p)
{
  //Fetch all scenes
  for (auto entry : std::filesystem::directory_iterator(scenePath))
  {
    const std::string sceneName = entry.path().stem().string();

    //TODO::Serialize this
    if (sceneName == "GameEnd")
    {
      SceneSettings settings;
      settings.DynamicCamera = SceneSettings::State::DeActivate;
      settings.Lighting = SceneSettings::State::DeActivate;

      scenes.insert({sceneName, {sceneName, settings}});
      continue;
    }

    scenes.insert({ sceneName, sceneName });
  }

  //Register scene event listener
  EventSystem::Register(listener_);

  //Load initial scene
  const auto initial = scenes.find(initialSceneName);
  if (initial != scenes.end())
  {
    current = initial;
    next = initial;
    initial->second.Load();
    return;
  }
  TraceLogger::Log(TraceLogger::WARNING) << "Scene with name \"" << initialSceneName << "\" doesn't exist. Failed to load initial scene." << std::endl;
}

void SceneSys::NewScene(const std::string& name)
{
  scenes.insert({ name, name });
}

void SceneSys::Update()
{
  if (next != current)
  {
    current->second.UnLoad();
    next->second.Load();

    Get<CameraSys>().ResetPosition();
    Get<CameraSys>().ResetZoom();

    current = next;
  }
  current->second.GetSettings().Apply();
}

void SceneSys::SetNextScene(const std::string& name)
{
  const auto nextScene = scenes.find(name);

  if (nextScene != scenes.end())
  {
    next = nextScene;
    return;
  }
  TraceLogger::Log(TraceLogger::WARNING) << "Scene with name \"" << name << "\" doesn't exist. Failed to set next scene." << std::endl;
}

void SceneSys::SetNextScene(std::unordered_map<std::string, Scene>::const_iterator scene)
{
  next = scene;
}

void SceneSys::Reload() const
{
  current->second.UnLoad();
  current->second.Load();
}

const std::string& SceneSys::GetCurrentName()
{
  return current->first;
}

const SceneSettings& SceneSys::GetCurrentSettings()
{
  return current->second.GetSettings();
}

std::unordered_map<std::string, Scene>::const_iterator SceneSys::Begin()
{
  return scenes.cbegin();
}

std::unordered_map<std::string, Scene>::const_iterator SceneSys::End()
{
  return scenes.cend();
}

SceneSys::~SceneSys()
= default;

void SceneSys::OnSetNextScene(const Event<EventType::SetNextScene> & event)
{
  SetNextScene(event.name);
}
