#include <UWUEngine/Scene/Scene.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>
#include <UWUEngine/Audio/SoundInterface.h>
#include <utility>

Scene::Scene(std::string name):
name_(std::move(name))
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
  EntityManager::DestroyAll();
  TextureAtlaser::ClearData();
}

const std::string& Scene::GetName() const
{
  return name_;
}
