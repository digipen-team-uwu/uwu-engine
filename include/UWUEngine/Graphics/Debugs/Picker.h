#pragma once
#include <queue>
#include <UWUEngine/Entity/EntityManager.h>

class Picker
{
public:
    Picker();
    ~Picker() = default;

    EntityID Pick();

private:
  EntityID saved_ID;
  float saved_t;
  std::priority_queue<float> time_;
};