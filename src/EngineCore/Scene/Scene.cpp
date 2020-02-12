#include <UWUEngine/Scene/Scene.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/Graphics/Texture/AtlasModule.h>
#include <UWUEngine/Audio/SoundInterface.h>
#include <UWUEngine/EngineSettings.h>
#include <UWUEngine/Graphics/Lighting/Lighting.h>

#include <utility>
#include <UWUEngine/Behaviors/DynamicCamera.h>

void SceneSettings::Apply() const
{
  switch (Lighting)
  {
  case State::Inherit:
    if (EngineSettings::Lighting)
    {
      Lighting::Activate();
    }
    else
    {
      Lighting::Deactivate();
    }
    break;
  case State::Activate:
    Lighting::Activate();
    break;
  case State::DeActivate:
    Lighting::Deactivate();
    break;
  default: ;
  }

  switch (DynamicCamera)
  {
  case State::Inherit:
    if (EngineSettings::DynamicCamera)
    {
      DynamicCamera::Activate();
    }
    else
    {
      DynamicCamera::Deactivate();
    }
    break;
  case State::Activate:
    DynamicCamera::Activate();
    break;
  case State::DeActivate:
    DynamicCamera::Deactivate();
    break;
  default:;
  }
}

Scene::Scene(std::string name):
name_(std::move(name))
{
}

Scene::Scene(std::string name, const SceneSettings& settings):
settings_(settings), name_(std::move(name))
{
}

void Scene::Load() const
{
  DeserializeLevel(name_.c_str());
  TextureAtlaser::LoadAtlasPage();
}

void Scene::UnLoad() const
{
  SoundInterface::stopAllSounds();
  EntitySys::DestroyAll();
  TextureAtlaser::ClearData();
}

const std::string& Scene::GetName() const
{
  return name_;
}

const SceneSettings& Scene::GetSettings() const
{
  return settings_;
}
