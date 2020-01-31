#include <ponder/classbuilder.hpp> //DO THIS ORDER.... or else... ill f*********** kill you
#include<ponder/uses/runtime.hpp>
#include <UWUEngine/Behaviors/ParticleSystem.h>

PONDER_TYPE(ParticleEvent)

void test()
{
  ParticleEvent event;
  ponder::Class::declare<ParticleEvent>().constructor<>()
    .property("UI", &ParticleEvent::UIParticles);
  const ponder::UserObject thing = ponder::UserObject::makeRef<ParticleEvent>(event);
  auto& classy = thing.getClass();
  
  for (auto&& it : classy.propertyIterator())
  {
    auto &pp = thing.get(it.first);
    it.name();
    typeid(pp);
  }
  
}