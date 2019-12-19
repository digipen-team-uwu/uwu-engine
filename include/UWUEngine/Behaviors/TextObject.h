#pragma once
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <sstream>

//TODO: make this a text emittor, make a text object that renders one character

template<>
class Behavior<EntityManager::Type::Text_> : public BaseBehavior
{
public:
  Behavior(EntityID id) : BaseBehavior(id), formattedText("") { }
  void Render();
  std::ostringstream& SetText() { formattedText.clear();  formattedText.str(""); return formattedText; }
private:
  std::ostringstream formattedText;
};

