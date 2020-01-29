#pragma once
#include <string>
#include <UWUEngine/Serialization.h>

class IScene
{
public:
  IScene(const std::string& name);
  virtual ~IScene();

  virtual void Load() = 0;
  virtual void Init() = 0;
  virtual void Update() = 0;
  virtual void ShutDown() = 0;
  virtual void UnLoad() = 0;

  const std::string& GetName();

private:
  std::string name_;
};

template <const std::string& name>
class Scene : public IScene
{
public:
  Scene();
  ~Scene() override = default;
  void Load() override;
  void Init() override;
  void Update() override;
  void ShutDown() override;
  void UnLoad() override;
};

template <const std::string& name>
Scene<name>::Scene():
IScene(name)
{
}

template <const std::string& name>
void Scene<name>::Load()
{
  objects = DeserializeLevel(name);
  TextureAtlaser::LoadAtlasPage();
}

template <const std::string& name>
void Scene<name>::Init()
{
}

template <const std::string& name>
void Scene<name>::Update()
{
}

template <const std::string& name>
void Scene<name>::ShutDown()
{
}

template <const std::string& name>
void Scene<name>::UnLoad()
{
  SoundInterface::stopAllSounds();
  EntityManager::DestroyAll();
  TextureAtlaser::ClearData();
}

#include <UWUEngine/Scene/CustomScenes/BrayanSBOX.h>
