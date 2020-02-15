/******************************************************************************/
/*!
\par        Project Umbra
\file       ColliderComp.h
\author     Yi Qian
\date       2019/12/05
\brief      Collider manager, I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#pragma once
#include <unordered_map>
#include <UWUEngine/Component/Component.h>
#include <UWUEngine/Systems/EventSys.h>
#include <glm/glm.hpp>


namespace UWUEngine
{

using Axis = glm::vec2;
class ColliderComp;

/**
 * \brief Project the point onto an axis
 * \param point The point to project from
 * \param axis The axis to project onto
 * \return The resultant point
 */
float ProjectPoint(glm::vec2 point, Axis axis);

class Projection
{
public:
	Projection(float min, float max, Axis axis);
	[[nodiscard]] bool isOverlapping(Projection const& rhs) const;
	[[nodiscard]] float getOverlap(Projection const& rhs)const;

private:
	float min{};
	float max{};
	const Axis axis;
};

class Collider
{
public:
	enum class ShapeType
	{
		INACTIVE,
		INVALID,
		POINT,
		LINE,
		CIRCLE,
		POLYGON,
		RECTANGLE,
		COUNT
	};
	Collider(ColliderComp& p, EntityID ID, ShapeType type) : parent(p), ID(ID), type(type) {}
	virtual ~Collider() = default;
	Collider(Collider const&) = default;
	Collider& operator=(Collider const&) = delete;

	[[nodiscard]] virtual Collider* Clone() const { assert("y'aint supposed to instantiate this", 0); return nullptr; }
	virtual void Serialize(std::ofstream& stream) const { assert("y'aint supposed to instantiate this", 0); }
	virtual void Render() { assert("y'aint supposed to instantiate this", 0); }

	Event<EventType::Collision> IsColliding(Collider& rhs);

	[[nodiscard]] virtual Projection Project(Axis const& axis) const { assert("y'aint supposed to instantiate this", 0); return Projection{ 0, 0, {} }; }
	virtual std::vector<Axis> const& GenerateAxis() { assert("y'aint supposed to instantiate this", 0); return {}; }

	[[nodiscard]] ShapeType GetType() const;
	void SetType(ShapeType type);

	template<class T>
	auto Get() const -> std::enable_if_t<std::is_base_of_v<IComponent, T>, T&>
	{
		return parent.Get<T>();
	}

	template <class T>
	auto Get() const -> std::enable_if_t<std::is_base_of_v<System, T>, T&>
	{
		return parent.Get<T>();
	}

	ColliderComp& parent;

	friend ColliderComp;

protected:

	std::vector<Axis> normals;
	EntityID ID;

private:
	ShapeType type;
};

class ColliderComp : public Component<ColliderComp, Collider>
{
public:
  ColliderComp(ISpace*);
  ~ColliderComp() override;

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
  void ResolveCollision(const Event<EventType::Collision>& info);
  EventListener<EventType::Collision> listener_;
  std::unordered_map<EntityID, Collider*> _collider;
};
}
