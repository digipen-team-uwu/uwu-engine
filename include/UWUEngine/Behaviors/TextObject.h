#pragma once
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Entity/EntitySys.h>
#include <sstream>

//TODO: make this a text emittor, make a text object that renders one character

namespace UWUEngine
{

template<>
class Behavior<EntitySys::Type::Text_> : public BaseBehavior
{
public:
  Behavior(EntityID id) : BaseBehavior(id), formattedText("") {}
  void Render();
  void Update();
  ::std::ostringstream& SetText() { formattedText.clear();  formattedText.str(""); return formattedText; }
private:
  ::std::ostringstream formattedText;
};

}