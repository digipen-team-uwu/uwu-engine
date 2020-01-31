#include <UWUEngine/Scene/SceneManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>

#include <filesystem>

static const std::string scenePath{"data/levels"};
static const std::string initialSceneName = "BrayanSBOX";

std::unordered_map<std::string, Scene> SceneManager::scenes;
std::unordered_map<std::string, Scene>::const_iterator SceneManager::current;
std::unordered_map<std::string, Scene>::const_iterator SceneManager::next;

SceneManager::SceneManager()
{
  //Fetch all scenes
  for (auto entry : std::filesystem::directory_iterator(scenePath))
  {
    const std::string sceneName = entry.path().stem().string();
    scenes.insert({sceneName, sceneName});
  }

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

void SceneManager::NewScene(const std::string& name)
{
  scenes.insert({name, name});
}

void SceneManager::Update()
{
  if (next != current)
  {
    current->second.UnLoad();
    next->second.Load();
    current = next;
  }
}

void SceneManager::SetNextScene(const std::string& name)
{
  const auto nextScene = scenes.find(name);

  if (nextScene != scenes.end())
  {
    next = nextScene;
    return;
  }
  TraceLogger::Log(TraceLogger::WARNING) << "Scene with name \"" << name <<"\" doesn't exist. Failed to set next scene." << std::endl;
}

void SceneManager::SetNextScene(std::unordered_map<std::string, Scene>::const_iterator scene)
{
  next = scene;
}

std::unordered_map<std::string, Scene>::const_iterator SceneManager::Begin()
{
  return scenes.cbegin();
}

std::unordered_map<std::string, Scene>::const_iterator SceneManager::End()
{
  return scenes.cend();
}

SceneManager::~SceneManager()
= default;
