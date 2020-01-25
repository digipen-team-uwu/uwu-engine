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

#include <UWUEngine/Component/BaseComponent.h>
#include <UWUEngine/Physics/Colliders/Collider.h>
#include <UWUEngine/Event/Type/Collision.h>

class ColliderComponentManager : public BaseComponent<ColliderComponentManager>
{
public:
	ColliderComponentManager();
	~ColliderComponentManager() override;
	
	void Update() override;
	void InitObject(EntityID ID) override;
	void ShutdownObject(EntityID ID) override;

  static void SetCollider(EntityID ID, Collider const * collider);

	static void SetPointCollider(EntityID ID, glm::vec2 position);
	static void SetLineCollider(EntityID ID, glm::vec2 p1, glm::vec2 p2);
	static void SetCircularCollider(EntityID ID, glm::vec2 center, float radius);
	static void SetRectangleCollider(EntityID ID);
	static void SetPolygonCollider(EntityID ID);

	static Collider const* GetCollider(EntityID ID);

  static void Serialize(std::ofstream& stream, EntityID id);

  static std::unordered_map<EntityID, Collider*>::const_iterator begin();
  static std::unordered_map<EntityID, Collider*>::const_iterator end();

private:
	static void ResolveCollision(CollisionInfo const& info);
	static std::unordered_map<EntityID, Collider*> _collider;
};
