#include <UWUEngine/Reflection.h>
#include <UWUEngine/Behaviors/ParticleSystem.h>

//PONDER_TYPE(ParticleEvent)

void Reflection::ReflectObject(EntityID id)
{
  //for (auto&& it : ponder::classIterator())
  {
    //it.second->getUserObjectFromPointer(it.second.)
  }
}

void SerializeObject(EntityID id)
{

}
/*
void test()
{
  ParticleEvent event;
  ponder::Class::declare<ParticleEvent>().constructor<>()
    .property("UI", &ParticleEvent::UIParticles);
  ponder::UserObject thing = ponder::UserObject::makeRef<ParticleEvent>(event);
  ponder::UserObject& thing2 = thing;
  auto& classy = thing2.getClass();
  
  for (auto&& it : classy.propertyIterator())
  {
    auto &pp = thing.get(it.first);
    it.name();
    typeid(pp);
  }
  
}*/