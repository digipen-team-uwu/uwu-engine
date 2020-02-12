/******************************************************************************/
	/*!
	\par        Project Umbra
	\file       EntitySys.h
	\author     Brayan Lopez
	\date       2019/09/13
	\brief      Entity System

	Copyright � 2019 DigiPen, All rights reserved.
	*/
	/******************************************************************************/

#pragma once
#include <UWUEngine/constants.h>
#include <UWUEngine/System.h>
#include "EntityVector.h"
#include <vector>

class Editor;
class IBaseComponent;

//TODO: factory construction of different GameObjects (Maybe?)
namespace goc = GameObjectConstants;
namespace uwu = UWUEngine;

namespace UWUEngine
{

class EntitySys : public System
{
public:

	enum Type
	{
		Empty,
		Player,
		Cyclone,
		Crystal,
		Logo_,
		Solid,
		Torch,
		Background,
		Light,
		ParticleEmitter,
		Particle,
		DebugVector,
		DebugRect,
		ZoesDog,
		Fang_,
		Perception,
		Text_,
		Rock_,
		CameraBounds,
		Wall_,
		Lantern,
		TypeCount,
		Prop_,
		Black,
		BrokenPillars,
		RockBG,
		CliffFace,
		Dropped,
		HUDHealth,
		HUDEnergy,
		HUDProp,
		ColliderTest,
		Hazard,
		LevelEnd,
		End,
	};

	//! \brief
	//    Gets the number of active entities
	//  \return
	//     the number of active entities
	size_t EntityCount();

	//! \brief
	//    returns a const ref to a container of all the 
	//    currently active entity IDs
	//  \return
	//    a const ref to container of ids
	const std::vector<EntityID>& GetIDs();
	//! \brief
	//    gets an entity's type
	//  \param ID
	//    the entity's type 
	//  \return
	//    a const ref to container of ids
	Type GetType(EntityID ID);
	//! \brief
	//    starts up the EntitySys
	//    call only once at the beginning of the game
	//  \return
	//    nothing  
	EntitySys();
	//! \brief
	//    frees up all memory used by the entity manager
	//  \return
	//    nothing  
	~EntitySys();
	//! \brief
	//    updates all active entities and destroys those marked
	//    for destroy
	//  \return
	//    nothing  
	void Update() override;
	//! \brief
	//    Get a "new" entity and make it active
	//    assumes there are no holes in internal vectors
	//    other than active entity ids, Particles are set to not serialize by default  
	//  \param type
	//    the new type of entity to create
	//  \return
	//    the ID of the new entity
	EntityID New(Type type);
	// Serializes all game components in JSON format, but only the pertinent data
	// Input:
	//    stream - The file stream that components will be written to
	//             (this should be opened and checked for validity ahead of time)
	void LevelSerialize(std::ofstream& stream);
	//! \brief
	//    set whether an entity is to pertain after a scene is cleared
	//    of entities. Entities get cleared by default.
	//  \param id
	//    the id of the entity to pertain
	//  \param clearImmunity
	//    whether the entity is to pertain after a scene is cleared
	//  \return
	//    nothing  
	void SetClearImmunity(EntityID id, bool clearImmunity);
	//! \brief
	//    set whether an entity is to be serialized or not. Entities
	//    are serialized by default.
	//  \param id
	//    the id of the entity to serialize/not serialize
	//  \param serialize
	//    whether the entity is to be serialized or not
	//  \return
	//    nothing  
	void SetDontSerialize(EntityID id, bool serialize);
	class IComponentConstructorProxy
	{
	public:
		virtual void Init() = 0;
		virtual ~IComponentConstructorProxy() = default;
		IBaseComponent* Get() const
		{
			return component_;
		}
		IBaseComponent* component_ = nullptr;
	};

	template <typename T>
	class ComponentConstructorProxy final : public IComponentConstructorProxy
	{
	public:
		explicit ComponentConstructorProxy(size_t order) : order_(order) {};
		void Init() override
		{
			component_ = new T();
			dynamic_cast<T*>(component_)->updateOrder_ = order_;
		};
		~ComponentConstructorProxy() = default;
	private:
		size_t order_ = -1;
	};

	template <typename T>
	size_t AddComponent(ComponentUpdateOrder order)
	{
		assert(order != ComponentUpdateOrder::INVALID);
		size_t pass_order = static_cast<size_t>(order);
		if (order == ComponentUpdateOrder::LAST)
		{
			pass_order = update_++;
		}
		else if (order == ComponentUpdateOrder::Behavior)
		{
			pass_order = behavior_++;
		}
		auto* new_component = new ComponentConstructorProxy<T>(pass_order);
		GetComponents().insert(std::make_pair(pass_order, static_cast<IComponentConstructorProxy*>(new_component)));
		return pass_order;
	}
	void InitComponents();
	//! \brief
	//    removes an entity from the scene
	//  \param id
	//    the id of the entity to destroy
	//  \param idsIndex
	//    the index of the entity in the ids vector,
	//    this will be found if not given
	//  \return
	//    nothing  
	void Destroy(EntityID id, int idsIndex = -1);
	//! \brief
	//    clears the scene by destroying all destroyable entities
	//  \return
	//    nothing  
	void DestroyAll();

	std::map<size_t, IComponentConstructorProxy*>& GetComponents();
private:
	std::vector<EntityID> ids;
	std::vector<EntityID> freeIDs;
	EntityVector<Type> types;
	EntityVector<std::uint8_t> destroyeds;
	EntityVector<std::uint8_t> clearImmune;
	EntityVector<std::uint8_t> dontSerialize;
	bool destroyed; //was any destroyed flag set to true this frame
	void Destroy_();//destroys entities when safe to do so
	void Deactivate(EntityID& id);//deactivates components attached to entity
	//std::vector<GameObject*> gameObjects{ goc::INITIAL_OBJECT_COUNT };
	//std::vector<GameObject*> freeGameObjects;
	EntityID idCount;

	size_t update_;
	size_t behavior_;

	friend class Editor;
};

} // namespace UWUEngine
