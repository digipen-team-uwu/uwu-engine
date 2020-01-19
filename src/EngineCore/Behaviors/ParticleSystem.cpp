/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       ParticleSystem.cpp
  \author     Hadi Alhussieni
  \date       2019/10/06
  \brief      Implementation for the behavior of a particle system object.
              

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityCacher.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/FrameRateController.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Component/ParentChildComponentManager.h>
#include <UWUEngine/Helper.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/UI/UIManager.h>
#include "UWUEngine/Graphics/Texture/TextureAtlaser.h"

typedef EntityManager::Type type;

void Behavior<type::ParticleEmitter>::PushEvent(ParticleEvent partEvent)
{
  ParentChildComponentManager::Activate(GetID());
  particleEvents.push_back(partEvent);
  if (!emissionTimer.Running())
  {
    emissionTimer.SetDuration(partEvent.emissionRate.Get());
    emissionTimer.Start();
  }
}

void Behavior<type::ParticleEmitter>::PushEvents(const std::vector<ParticleEvent> &partEvent)
{
  ParentChildComponentManager::Activate(GetID());
  particleEvents = partEvent;
  if (!emissionTimer.Running())
  {
    emissionTimer.SetDuration(particleEvents[0].emissionRate.Get());
    emissionTimer.Start();
  }
}

//TODO: warmup particles

void Behavior<type::ParticleEmitter>::Update()
{
  auto &partEvent = particleEvents[currentEvent];
  if (emissionTimer.Finished())
  {
    int emissionCount = partEvent.particlesPerEmission.Get();
    for (int i = 0; i < emissionCount; ++i)
    {
      EntityID id = EntityManager::New(type::Particle);
      BehaviorComponentManager::Activate(id);
      ParentChildComponentManager::AddChild(GetID(), id);
      BehaviorComponentManager::GetBehavior<type::Particle>(id)->InitData(partEvent);
    }
    emissionTimer.SetDuration(partEvent.emissionRate.Get());
  }
}

/* int Behavior<type::ParticleEmitter>::GetCurrentEvent()
{
  return currentEvent;
}

ParticleEvent &Behavior<type::ParticleEmitter>::GetParticleEvent(int eventNumber)
{
  return particleEvents[eventNumber];
}*/

void Behavior<type::Particle>::InitData(ParticleEvent& partEvent)
{
  EntityID emitter = ParentChildComponentManager::GetParent(GetID());
  TransformComponentManager::Activate(GetID());
  PhysicsComponentManager::Activate(GetID());
  //ShaderModule::Activate(GetID());
  MeshComponentManager::Activate(GetID());
  TextureComponentManager::Activate(GetID());
  int sprite = Random::Range(0, static_cast<int>(partEvent.sprite.textures.size()) - 1);
  //TextureComponentManager::SetTextureID(GetID(), partEvent.sprite.textures[sprite]);
  TextureComponentManager::SetFilePath(GetID(), partEvent.sprite.textures[sprite].c_str());
  TextureAtlaser::SetAtlasData(GetID());
  //Engine::textureAtlaser.SetAtlasUV(GetID());
  //Engine::textureAtlaser.SetAtlasScale(GetID());
  //GLuint partTexture = TextureComponentManager::LoadTexture(GetID());
  //TextureComponentManager::SetTextureID(GetID(), partTexture);
  TextureComponentManager::SetDimensions(partEvent.sprite.dimensions[sprite], GetID());
  TextureComponentManager::SetColor(GetID(), partEvent.color.color.Get());
  TransformComponentManager::SetTranslation(TransformComponentManager::GetTranslation(emitter) + partEvent.posOffset.Get(), GetID());
  TransformComponentManager::SetScale(partEvent.scale.scale.Get(), GetID());
  //GLSLShader shader = ShaderModule::CreateShader(GetID(), "./shaders/pass-thru-pos2d-clr.vert", "./shaders/basic-color.frag");
  //ShaderModule::SetShader(GetID(), shader);
  //MeshComponentManager::SetMesh(GetID(), MeshComponentManager::getSquareMesh());
  PhysicsComponentManager::SetAcceleration(partEvent.acceleration.Get(), GetID());
  PhysicsComponentManager::SetInverseMass(partEvent.inverseMass.Get(), GetID());
  PhysicsComponentManager::SetRotationalVelocity(partEvent.rotationalVelocity.Get(), GetID());
  float rotate = partEvent.startRotation.Get();
  baseRotation = rotate;
    TransformComponentManager::SetRotation(rotate, GetID()); //maybe also rotate by emitter's rotation?
    glm::vec4 velocity = { 1, 0, 0, 0 };
    if (partEvent.direction.polarCoordsRotation.Get() != psc::UNUSED_FLOAT)
    {
      velocity = VectorFromAngle(partEvent.direction.polarCoordsRotation.Get());
    }

  if (partEvent.direction.sphereCoordsRotation.Get() != psc::UNUSED_VEC2)
  {
    velocity = VectorFromTwoAngles(partEvent.direction.sphereCoordsRotation.Get());
  }

  velocity *= partEvent.speed.Get();
  PhysicsComponentManager::SetVelocity(velocity, GetID());
  if (partEvent.sprite.animations.size())
  {
    AnimationComponentManager::Activate(GetID());
    AnimationComponentManager::AddNewAnimation(GetID(), 0);
    AnimationComponentManager::AddAnimationData(GetID(), partEvent.sprite.animations[sprite], 0);
  }

  if (partEvent.vectorfieldx)
  {
    int ranfield = Random::Range(0, partEvent.vectorfieldx->size() - 1);
    vectorfieldx = (*(partEvent.vectorfieldx))[ranfield];
    if (partEvent.vectorfieldy)
    {
      vectorfieldy = (*(partEvent.vectorfieldy))[ranfield];
    }
  }

  endColor = partEvent.color.endColor.Get();
  endScale = partEvent.scale.endScale.Get();
  colorRate = partEvent.color.colorRate.Get();
  scaleRate = partEvent.scale.scaleRate.Get();
  maxLife = partEvent.lifetime.Get();
  endWithAnimation = partEvent.endWithAnimation;
  rotateByVelocity = partEvent.rotateByVelocity;
  UIParticle = partEvent.UIParticles;
  lifetime = 0;
}

void Behavior<type::Particle>::Update()
{
  if (endColor != psc::UNUSED_VEC4)
  {
    TextureComponentManager::SetColor(GetID(), glm::mix(TextureComponentManager::GetColor(GetID()), endColor, colorRate * FrameRateController::GetDeltaTime<float>()));
  }
  if (endScale != psc::UNUSED_VEC3)
  {
    TransformComponentManager::SetScale(glm::mix(TransformComponentManager::GetScale(GetID()), endScale, scaleRate * FrameRateController::GetDeltaTime<float>()), GetID());
  }

  if (rotateByVelocity)
  {
    TransformComponentManager::SetRotation(baseRotation + RotationFromVec(PhysicsComponentManager::GetVelocity(GetID())), GetID());
  }
  
  if (endWithAnimation && AnimationComponentManager::AnimationFinished(GetID()))
  {
    EntityManager::Destroy(GetID());
  }
  if (vectorfieldx || vectorfieldy)
  {
    glm::vec4 vel = PhysicsComponentManager::GetVelocity(GetID());
    glm::vec4 pos = TransformComponentManager::GetTranslation(GetID());
    glm::vec4 parpos = TransformComponentManager::GetTranslation(ParentChildComponentManager::GetParent(GetID()));
    if (vectorfieldx)
    {
      vel.x = vectorfieldx->Evaluate(pos - parpos);
    }
    if (vectorfieldy)
    {
      vel.y = vectorfieldy->Evaluate(pos - parpos);
    }
    PhysicsComponentManager::SetVelocity(vel, GetID());
  }

  if (UIParticle)
  {
    UIManager::PushElement(TransformComponentManager::GetRotation(GetID()), TransformComponentManager::GetTranslation(GetID()), TransformComponentManager::GetScale(GetID()),
                      TextureComponentManager::GetColor(GetID()), AnimationComponentManager::indexToUvs(GetID(), AnimationComponentManager::GetCurrentFrame(GetID())),
                            TextureComponentManager::GetDimensions(GetID()), TextureAtlaser::GetAtlasUV(GetID()),
                            TextureAtlaser::GetAtlasScale(GetID()), TextureAtlaser::GetAtlasLayers(GetID()));
    TextureComponentManager::SetUV(GetID(), { -1, -1 });
  }

  lifetime += FrameRateController::GetDeltaTime<float>();

  if (maxLife != psc::UNUSED_FLOAT)
  {
    if (lifetime > maxLife)
    {
      EntityManager::Destroy(GetID());
    }
  }
}

template<typename T>
FlatOrRange<T> DeserializeFlatOrRange(rapidjson::Value& object);

template<>
FlatOrRange<glm::vec4> DeserializeFlatOrRange<glm::vec4>(rapidjson::Value& object)
{
  if (object[0].IsArray())
  {
    return FlatOrRange<glm::vec4>(glm::vec4{ object[0][0].GetFloat(), object[0][1].GetFloat(), object[0][2].GetFloat(), object[0][3].GetFloat() },
      glm::vec4{ object[1][0].GetFloat(), object[1][1].GetFloat(), object[1][2].GetFloat(), object[1][3].GetFloat() });
  }
  else
  {
    return FlatOrRange<glm::vec4>(glm::vec4{ object[0].GetFloat(), object[1].GetFloat(), object[2].GetFloat(), object[3].GetFloat() });
  }
}

template<>
FlatOrRange<glm::vec3> DeserializeFlatOrRange<glm::vec3>(rapidjson::Value& object)
{
  if (object[0].IsArray())
  {
    return FlatOrRange<glm::vec3>(glm::vec3{ object[0][0].GetFloat(), object[0][1].GetFloat(), object[0][2].GetFloat() },
      glm::vec3{ object[1][0].GetFloat(), object[1][1].GetFloat(), object[1][2].GetFloat() });
  }
  else
  {
    return FlatOrRange<glm::vec3>(glm::vec3{ object[0].GetFloat(), object[1].GetFloat(), object[2].GetFloat() });
  }
}

template<>
FlatOrRange<glm::vec2> DeserializeFlatOrRange<glm::vec2>(rapidjson::Value& object)
{
  if (object[0].IsArray())
  {
    return FlatOrRange<glm::vec2>(glm::vec2{ object[0][0].GetFloat(), object[0][1].GetFloat() },
      glm::vec2{ object[1][0].GetFloat(), object[1][1].GetFloat() });
  }
  else
  {
    return FlatOrRange<glm::vec2>(glm::vec2{ object[0].GetFloat(), object[1].GetFloat() });
  }
}

template<>
FlatOrRange<float> DeserializeFlatOrRange<float>(rapidjson::Value& object)
{
  if (object.IsArray())
  {
    return FlatOrRange<float>(object[0].GetFloat(), object[1].GetFloat());
  }
  else
  {
    return FlatOrRange<float>(object.GetFloat());
  }
}

template<>
FlatOrRange<int> DeserializeFlatOrRange<int>(rapidjson::Value& object)
{
  if (object.IsArray())
  {
    return FlatOrRange<int>(object[0].GetInt(), object[1].GetInt());
  }
  else
  {
    return FlatOrRange<int>(object.GetInt());
  }
}

Polynomial* DeserializePolynomial(rapidjson::Value& object)
{
  Polynomial::PolynomialSpecials special = Polynomial::NONE;
  float specialCoeff = 1;
  if (object[0].HasMember("special"))
  {
    special = magic_enum::enum_cast<Polynomial::PolynomialSpecials>(str_toupper(object[0]["special"].GetString())).value();
  }
  if (object[0].HasMember("special coefficient"))
  {
    specialCoeff = object[0]["special coefficient"].GetFloat();
  }
  Polynomial* poly = new Polynomial(object[0]["exponent"].GetInt(), object[0]["coefficient"].GetFloat(), object[0]["variable"].GetString()[0], special, specialCoeff);
  for (int i = 1; i < object.Size(); ++i)
  {
    special = Polynomial::NONE;
    specialCoeff = 1;
    if (object[i].HasMember("special"))
    {
      special = magic_enum::enum_cast<Polynomial::PolynomialSpecials>(str_toupper(object[i]["special"].GetString())).value();
    }
    if (object[i].HasMember("special coefficient"))
    {
      specialCoeff = object[i]["special coefficient"].GetFloat();
    }
    poly->AddPolynomial(object[i]["exponent"].GetInt(), object[i]["coefficient"].GetFloat(), object[i]["variable"].GetString()[0], special, specialCoeff);
  }
  return poly;
}

std::vector<std::shared_ptr<Polynomial>>* DeserializePolynomials(rapidjson::Value& object)
{
  std::vector<std::shared_ptr<Polynomial>>* vec = new std::vector<std::shared_ptr<Polynomial>>;
  if (!object[0].IsArray())
  {
    std::shared_ptr<Polynomial> ptr(DeserializePolynomial(object));
    vec->push_back(ptr);
  }
  else
  {
    for (int i = 0; i < object.Size(); ++i)
    {
      std::shared_ptr<Polynomial> ptr(DeserializePolynomial(object[i]));
      vec->push_back(ptr);
    }
  }
  return vec;
}



static void SerializeEvent(rapidjson::Value& evnt, ParticleEvent &partEvent)
{
  if (evnt.HasMember("sprite"))
  {
    for (unsigned j = 0; j < evnt["sprite"].Size(); ++j)
    {
      rapidjson::Value& sprite = evnt["sprite"][j];
      if (sprite.HasMember("animation"))
      {
        AnimationComponentManager::AnimationData animdata = DeserializeAnimation(sprite["animation"]);
        partEvent.sprite.animations.push_back(animdata);
      }
      if (sprite.HasMember("texture"))
      {
        partEvent.sprite.textures.push_back(sprite["texture"].GetString());
        EntityCacher::CacheFile(sprite["texture"].GetString());
      }
      if (sprite.HasMember("dimensions"))
      {
        partEvent.sprite.dimensions.push_back(glm::uvec2{ sprite["dimensions"][0].GetUint(),sprite["dimensions"][1].GetUint() });
      }
      else
      {
        partEvent.sprite.dimensions.push_back({ 1, 1 });
      }
    }
  }

  if (evnt.HasMember("color"))
  {
    partEvent.color.color = DeserializeFlatOrRange<glm::vec4>(evnt["color"]);
  }
  if (evnt.HasMember("end color"))
  {
    partEvent.color.endColor = DeserializeFlatOrRange<glm::vec4>(evnt["end color"]);
  }
  if (evnt.HasMember("color rate"))
  {
    partEvent.color.colorRate = DeserializeFlatOrRange<float>(evnt["color rate"]);
  }
  if (evnt.HasMember("scale"))
  {
    partEvent.scale.scale = DeserializeFlatOrRange<glm::vec3>(evnt["scale"]);
  }

  if (evnt.HasMember("end scale"))
  {
    partEvent.scale.endScale = DeserializeFlatOrRange<glm::vec3>(evnt["end scale"]);
  }

  if (evnt.HasMember("scale rate"))
  {
    partEvent.scale.scaleRate = DeserializeFlatOrRange<float>(evnt["scale rate"]);
  }

  if (evnt.HasMember("particles per emission"))
  {
    partEvent.particlesPerEmission = DeserializeFlatOrRange<int>(evnt["particles per emission"]);
  }

  if (evnt.HasMember("emission rate"))
  {
    partEvent.emissionRate = DeserializeFlatOrRange<float>(evnt["emission rate"]);
  }

  if (evnt.HasMember("direction"))
  {
    partEvent.direction.polarCoordsRotation = DeserializeFlatOrRange<float>(evnt["direction"]);
    partEvent.direction.polarCoordsRotation.SetToRads();
  }

  if (evnt.HasMember("3d direction"))
  {
    partEvent.direction.sphereCoordsRotation = DeserializeFlatOrRange<glm::vec2>(evnt["3d direction"]);
    partEvent.direction.sphereCoordsRotation.SetToRads();
  }

  if (evnt.HasMember("acceleration"))
  {
    partEvent.acceleration = DeserializeFlatOrRange<glm::vec4>(evnt["acceleration"]);
  }

  if (evnt.HasMember("position offset"))
  {
    partEvent.posOffset = DeserializeFlatOrRange<glm::vec4>(evnt["position offset"]);
  }

  if (evnt.HasMember("inverse mass"))
  {
    partEvent.inverseMass = DeserializeFlatOrRange<float>(evnt["inverse mass"]);
  }

  if (evnt.HasMember("speed"))
  {
    partEvent.speed = DeserializeFlatOrRange<float>(evnt["speed"]);
  }

  if (evnt.HasMember("lifetime"))
  {
    partEvent.lifetime = DeserializeFlatOrRange<float>(evnt["lifetime"]);
  }

  if (evnt.HasMember("start rotation"))
  {
    partEvent.startRotation = DeserializeFlatOrRange<float>(evnt["start rotation"]);
    partEvent.startRotation.SetToRads();
  }

  if (evnt.HasMember("end with animation"))
  {
    partEvent.endWithAnimation = evnt["end with animation"].GetBool();
  }

  if (evnt.HasMember("rotate by velocity"))
  {
    partEvent.rotateByVelocity = evnt["rotate by velocity"].GetBool();
  }

  if (evnt.HasMember("ui particles"))
  {
    partEvent.UIParticles = evnt["ui particles"].GetBool();
  }

  if (evnt.HasMember("rotational velocity"))
  {
    partEvent.rotationalVelocity = DeserializeFlatOrRange<float>(evnt["rotational velocity"]);
    partEvent.rotationalVelocity.SetToRads();
  }

  if (evnt.HasMember("vector field x"))
  {
    partEvent.vectorfieldx = std::shared_ptr<std::vector<std::shared_ptr<Polynomial>>>(DeserializePolynomials(evnt["vector field x"]));
  }

  if (evnt.HasMember("vector field y"))
  {
    partEvent.vectorfieldy = std::shared_ptr<std::vector<std::shared_ptr<Polynomial>>>(DeserializePolynomials(evnt["vector field y"]));
  }

  if (evnt.HasMember("event length"))
  {
    partEvent.eventLength = evnt["event length"].GetFloat();
  }
}

void Behavior<type::ParticleEmitter>::Deserialize(rapidjson::Value& obj, EntityID ID, const char* filePath)
{
    //TODO: add curly braces to double code count
  rapidjson::Value &object = obj["behavior"];
  for (unsigned i = 0; i < object["particleevents"].Size(); ++i)
  {
    rapidjson::Value& evnt = object["particleevents"][i];
    ParticleEvent partEvent;
    SerializeEvent(evnt, partEvent);
    PushEvent(partEvent);
  }
}

void CachedBehavior<type::ParticleEmitter>::Deserialize(rapidjson::Value& object)
{
  particleEvents.clear();
  for (unsigned i = 0; i < object["behavior"]["particleevents"].Size(); ++i)
  {
    rapidjson::Value& evnt = object["behavior"]["particleevents"][i];
    ParticleEvent partEvent;
    SerializeEvent(evnt, partEvent);
    particleEvents.push_back(partEvent);
  }
}

void CachedBehavior<type::ParticleEmitter>::InstantiateBehavior(EntityID ID)
{
  BehaviorComponentManager::GetBehavior<type::ParticleEmitter>(ID)->PushEvents(particleEvents);
}