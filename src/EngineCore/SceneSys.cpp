#include <UWUEngine/Systems/SceneSys.h>
#include <UWUEngine/Systems/LogSys.h>
//#include <UWUEngine/Graphics/CameraSys.h>

#include <filesystem>
#include <UWUEngine/EngineSettings.h>

static const std::string scenePath{ "data/levels" };
static const std::string initialSceneName = "BrayanSBOX";

using namespace UWUEngine;

#pragma region Scene
void SceneSettings::Apply() const
{
  //TODO:Lighting and Dynamic camera
  //switch (Lighting)
  //{
  //case State::Inherit:
  //  if (EngineSettings::Lighting)
  //  {
  //    Lighting::Activate();
  //  }
  //  else
  //  {
  //    Lighting::Deactivate();
  //  }
  //  break;
  //case State::Activate:
  //  Lighting::Activate();
  //  break;
  //case State::DeActivate:
  //  Lighting::Deactivate();
  //  break;
  //default:;
  //}

  //switch (DynamicCamera)
  //{
  //case State::Inherit:
  //  if (EngineSettings::DynamicCamera)
  //  {
  //    DynamicCamera::Activate();
  //  }
  //  else
  //  {
  //    DynamicCamera::Deactivate();
  //  }
  //  break;
  //case State::Activate:
  //  DynamicCamera::Activate();
  //  break;
  //case State::DeActivate:
  //  DynamicCamera::Deactivate();
  //  break;
  //default:;
  //}
}

Scene::Scene(std::string name) :
  name_(std::move(name))
{
}

Scene::Scene(std::string name, const SceneSettings& settings) :
  settings_(settings), name_(std::move(name))
{
}

void Scene::Load() const
{
  //TODO:Level load
  //DeserializeLevel(name_.c_str());
  //TextureAtlaser::LoadAtlasPage();
}

void Scene::UnLoad() const
{
  //TODO:Level unload
  //SoundInterface::stopAllSounds();
  //EntitySys::DestroyAll();
  //TextureAtlaser::ClearData();
}

const std::string& Scene::GetName() const
{
  return name_;
}

const SceneSettings& Scene::GetSettings() const
{
  return settings_;
}
#pragma endregion 

#pragma region SceneSystem
SceneSys::SceneSys(ISpace* p):
System(p), listener_(MemberFunc(&SceneSys::OnSetNextScene))
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
  Get<EventSys>().Register(listener_);

  //Load initial scene
  const auto initial = scenes.find(initialSceneName);
  if (initial != scenes.end())
  {
    current = initial;
    next = initial;
    initial->second.Load();
    return;
  }
  Get<LogSys>().Log(Get<LogSys>().WARNING) << "Scene with name \"" << initialSceneName << "\" doesn't exist. Failed to load initial scene." << std::endl;
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

    //TODO:Camera system
    //Get<CameraSys>().ResetPosition();
    //Get<CameraSys>().ResetZoom();

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
  Get<LogSys>().Log(Get<LogSys>().WARNING) << "Scene with name \"" << name << "\" doesn't exist. Failed to set next scene." << std::endl;
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

#pragma endregion 
