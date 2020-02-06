#include <UWUEngine/Reflection.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/Helper.h>
#include <rttr/registration.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <UWUEngine/rttrsamples/to_json.h>

namespace UWUEngine
{
using anim = AnimationComp::AnimationData;
ReflectionModule::ReflectionModule()
{
  rttr::registration::class_<anim::Frame>("Frame")
    .property("index", &anim::Frame::index)
    .property("frameDuration", &anim::Frame::frameDuration);
  rttr::registration::class_<anim>("AnimationData")
    .property("looping_", &anim::looping_)
    .property("currentFrame_", &anim::currentFrame_)
    .property("frameCount_", &anim::frameCount_)
    .property("frameDelay_", &anim::frameDelay_)
    .property("isRunning_", &anim::isRunning_)
    .property("frames_", &anim::frames_);
  rttr::registration::class_<glm::uvec2>("uvec2").property("x", &glm::uvec2::x).property("y", &glm::uvec2::y);
  rttr::registration::class_<glm::vec2>("vec2").property("x", &glm::vec2::x).property("y", &glm::vec2::y);
  rttr::registration::class_<glm::vec3>("vec3").property("x", &glm::vec3::x).property("y", &glm::vec3::y).property("z", &glm::vec3::z);
  rttr::registration::class_<glm::vec4>("vec4").property("x", &glm::vec4::x).property("y", &glm::vec4::y).property("z", &glm::vec4::z).property("w", &glm::vec4::w);
  RegisterFlatOrRange<int>();
  RegisterFlatOrRange<float>();
  RegisterFlatOrRange<double>();
  RegisterFlatOrRange<glm::vec2>();
  RegisterFlatOrRange<glm::vec3>();
  RegisterFlatOrRange<glm::vec4>();
  rttr::registration::class_<ParticleEvent::Color>("Color").property("color", &ParticleEvent::Color::color)
    .property("endColor", &ParticleEvent::Color::endColor)
    .property("colorRate", &ParticleEvent::Color::colorRate);
  rttr::registration::class_<ParticleEvent::Size>("Size").property("scale", &ParticleEvent::Size::scale)
    .property("endScale", &ParticleEvent::Size::endScale)
    .property("scaleRate", &ParticleEvent::Size::scaleRate);
  rttr::registration::class_<ParticleEvent::Sprite>("Sprite").property("animations", &ParticleEvent::Sprite::animations)
    .property("textures", &ParticleEvent::Sprite::textures)
    .property("dimensions", &ParticleEvent::Sprite::dimensions);
  rttr::registration::class_<ParticleEvent::Direction>("Direction").property("polarCoordsRotation", &ParticleEvent::Direction::polarCoordsRotation)
    .property("sphereCoordsRotation", &ParticleEvent::Direction::sphereCoordsRotation);
  rttr::registration::class_<ParticleEvent>("ParticleEvent")
    .property("color", &ParticleEvent::color)
    .property("scale", &ParticleEvent::scale)
    .property("rotationalVelocity", &ParticleEvent::rotationalVelocity)
    .property("startRotation", &ParticleEvent::startRotation)
    .property("emissionRate", &ParticleEvent::emissionRate)
    .property("sprite", &ParticleEvent::sprite)
    .property("particlesPerEmission", &ParticleEvent::particlesPerEmission)
    .property("speed", &ParticleEvent::speed)
    .property("direction", &ParticleEvent::direction)
    .property("acceleration", &ParticleEvent::acceleration)
    .property("lifetime", &ParticleEvent::lifetime)
    .property("posOffset", &ParticleEvent::posOffset)
    .property("inverseMass", &ParticleEvent::inverseMass)
    .property("endWithAnimation", &ParticleEvent::endWithAnimation)
    .property("rotateByVelocity", &ParticleEvent::rotateByVelocity)
    .property("UIParticles", &ParticleEvent::UIParticles);
  std::ofstream file;
  file.open("particles.json");
  ParticleEvent event;
  rttr::instance eve(event);
  std::string str = Serialization::to_json(eve);
  file << str;
  file.close();
}


std::vector<rttr::instance>& ReflectionModule::getInstances(EntityID id)
{
  return data[id];
}
}