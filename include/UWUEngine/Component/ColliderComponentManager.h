/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderComponentManager.h
\author     Yi Qian
\date       2019/12/05
\brief      Collider manager, I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include <unordered_map>

#include <UWUEngine/Component/Component.h>
#include <UWUEngine/Physics/Colliders/Collider.h>

namespace UWUEngine
{
  class ColliderComp final : public Component
  {
  public:
    ColliderComp();
    ~ColliderComp() override;

    void Update() override;
    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;

    void SetCollider(EntityID ID, Collider const* collider);

    void SetPointCollider(EntityID ID, glm::vec2 position);
    void SetLineCollider(EntityID ID, glm::vec2 p1, glm::vec2 p2);
    void SetCircularCollider(EntityID ID, glm::vec2 center, float radius);
    void SetRectangleCollider(EntityID ID);
    void SetPolygonCollider(EntityID ID);

    Collider const* GetCollider(EntityID ID);

    void Serialize(std::ofstream& stream, EntityID id);

    std::unordered_map<EntityID, Collider*>::const_iterator begin();
    std::unordered_map<EntityID, Collider*>::const_iterator end();

  private:
    //TODO: part of event collision sys
    //void ResolveCollision(const Event<EventType::Collision>& info);
    //EventListener<EventType::Collision> listener_;
    std::unordered_map<EntityID, Collider*> _collider;
  };
}
