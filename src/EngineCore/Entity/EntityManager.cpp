/******************************************************************************/
    /*!
    \par        Project Umbra
    \file       EntityManager.cpp
    \author     Brayan Lopez
    \date       2019/09/13
    \brief      Game Object Manager implementation

    Copyright � 2019 DigiPen, All rights reserved.
    */
/******************************************************************************/

#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityIDManager.h>
#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <magic_enum.hpp>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Component/BehaviorComponentManager.h>
#include <UWUEngine/Component/ParentChildComponentManager.h>
#include <UWUEngine/Engine.h>
#include <fstream>
#include <UWUEngine/Serialization.h>

template<>
int RegisterSystemHelper<EntityManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<EntityManager>(SystemInitOrder::Entity, SystemUpdateOrder::Entity);

std::vector<EntityID> EntityManager::ids;
std::vector<EntityID> EntityManager::freeIDs;
EntityVector<EntityManager::Type> EntityManager::types(goc::INITIAL_OBJECT_COUNT);
EntityVector<std::uint8_t> EntityManager::destroyeds(goc::INITIAL_OBJECT_COUNT);
EntityVector<std::uint8_t> EntityManager::clearImmune(goc::INITIAL_OBJECT_COUNT);
EntityVector<std::uint8_t> EntityManager::dontSerialize(goc::INITIAL_OBJECT_COUNT);
bool EntityManager::destroyed = false;
EntityID EntityManager::idCount = 0;

size_t EntityManager::update_ = static_cast<size_t>(ComponentUpdateOrder::LAST);
size_t EntityManager::behavior_ = static_cast<size_t>(ComponentUpdateOrder::Behavior);

#pragma region GETTERS

namespace goc = GameObjectConstants;

size_t EntityManager::EntityCount()
{
  return ids.size();
}

const std::vector<EntityID>& EntityManager::GetIDs()
{
    return ids;
}

Type EntityManager::GetType(EntityID ID)
{
    return types[ID];
}


EntityID EntityManager::New(Type type)
{
    if (!type) //if its Type.Empty
        return -1;//then dont waste time calling this function

    EntityID id = 0;

    if (freeIDs.size())
    {
        //take the last one
        id = freeIDs.back();/*[freeIDs.size() - 1];*/
        //remove last one from vector
        freeIDs.pop_back();
    }
    else
    {
      id = (++idCount - 1);
      EntityIDManager::AddID(id);
    }

    ids.push_back(id);
    if (id >= EntityVectorManager::GetVectorSize())
    {
      EntityVectorManager::ResizeVectors();
      Instances::CreateInstances(MeshComponentManager::GetEntityMesh());
    }

    types[id] = type;
    destroyeds[id] = false;
    clearImmune[id] = false;
    if (type == Particle)
      dontSerialize[id] = true;
    else
      dontSerialize[id] = false;
	
    return id;
}

#pragma endregion

#pragma region DOERS

EntityManager::EntityManager()
{
    ids.reserve(goc::INITIAL_OBJECT_COUNT);
    freeIDs.resize(goc::INITIAL_OBJECT_COUNT);
    for (idCount = 0; idCount < goc::INITIAL_OBJECT_COUNT; ++idCount)
    {
        //freeGameObjects.push_back(new GameObject);
        freeIDs[idCount] = idCount;
    }
    InitComponents();
}

EntityManager::~EntityManager()
{
    ids.clear();
    freeIDs.clear();
}

void EntityManager::Update( )
{
  if (destroyed)
  {
    Destroy_();
  }

  for (auto& comp : GetComponents())
  {
    comp.second->Get()->Update();
  }
}

void EntityManager::InitComponents()
{
  for (auto& comp : GetComponents())
  {
    comp.second->Init();
  }
}

void EntityManager::Destroy(EntityID id, int idsIndex)
{
  //Mark all the children as destroyed
  //for (auto child : ParentChildComponentManager::GetChildren(id))
  //{
    //Destroy(child, idsIndex);
  //}
  //Remove Name
  Editors::EntityViewer::RemoveName(id);
  if (idsIndex == -1)
  {
    for (int i = 0; i < ids.size(); ++i)
    {
      if (ids[i] == id)
      {
        destroyeds[id] = true;
        destroyed = true;
        break;
      }
    }
  }
  else
  {
    destroyeds[id] = true;
    destroyed = true;
  }

}

void EntityManager::DestroyAll()
{
  Editors::EntityViewer::RemoveAllNames();
  for (int i = static_cast<int>(ids.size()) - 1; i > -1; --i)
  {
    EntityID id = ids[i];
    if (!clearImmune[id])
    {
      //remove it
      ids.pop_back();
      //add it to freed
      freeIDs.push_back(id);

      Deactivate(id);
    }
  }
  destroyed = false;
}

std::map<size_t, EntityManager::IComponentConstructorProxy*>& EntityManager::GetComponents()
{
  static std::map<size_t, IComponentConstructorProxy*> components;
  return components;
}

void EntityManager::Destroy_()
{
  EntityID id = 0;
  for (int i = 0; i < ids.size(); ++i)
  {
    id = ids[i];
    if (destroyeds[id])
    {
      //swap with the back one
      EntityID temp = ids.back();
      ids[i] = temp;
      ids.back() = id;
      //remove it
      ids.pop_back();
      //add it to freed
      freeIDs.push_back(id);
      
      Deactivate(id);
    }
  }
  destroyed = false;
}

void EntityManager::Deactivate(EntityID& id)
{
  //deactivate transform
  for (auto& it : GetComponents())
  {
    it.second->Get()->Make_Inactive(id);
  }

  types[id] = Empty; //reset type
}

#pragma endregion

#pragma region SETTERS

void EntityManager::SetClearImmunity(EntityID id, bool clearImmunity)
{
  clearImmune[id] = clearImmunity;
}

void EntityManager::SetDontSerialize(EntityID id, bool serialize)
{
  dontSerialize[id] = serialize;
}

#pragma  endregion 

// The below code written by Michael Rollosson Halbhuber
#pragma region SERIALIZATION

// Serializes all game components in JSON format
// Input:
//    stream - The file stream that components will be written to
//             (this should be opened and checked for validity ahead of time,
//              but this function will double check just in case)
void EntityManager::LevelSerialize(std::ofstream &stream)
{
    if (stream.is_open())
    {
        bool firstObject = true;

        // Begin a JSON object with an array member
        stream << "{\n";
        stream << R"("objects" : )";
        stream << "[\n";
        
        // Iterate through all objects and serialize them
        for (EntityID id : ids)
        {
            if (!dontSerialize[id])
            {
                //if (id != ids.front())
                if (!firstObject)
                {
                    stream << ",";
                    stream << "\n";
                }
                else
                {
                    firstObject = false;
                }
                bool partial = true;
              
                if (types[id] != EntityManager::Cyclone
                    && types[id] != EntityManager::Logo_
                    && types[id] != EntityManager::Player
                    && types[id] != EntityManager::Text_
                    && types[id] != EntityManager::Solid)
                {
                    partial = false;
                }
            
                // Open up a JSON object within the array
                stream << "{\n";
            
                // Print the current object's type
                stream << Tabs::ONE << R"("type" : ")" << magic_enum::enum_name(types[id]) << "\",\n";

                if(Editors::EntityViewer::HasName(id))
                  stream << Tabs::TWO << R"("name" : ")" << Editors::EntityViewer::GetName(id) << "\",\n";
            
                // Serialize the transform component
                if (TransformComponentManager::IsActive(id))
                {
                    stream << Tabs::TWO;
                    TransformComponentManager::Serialize(stream, id);
                }
                
                // Serialize the physics component
                if (PhysicsComponentManager::IsActive(id))
                {
                    stream << ",\n";
                    stream << Tabs::TWO;
                    PhysicsComponentManager::Serialize(stream, id, partial);
                }

                if (BehaviorComponentManager::IsActive(id))
                {
                  if (!BehaviorComponentManager::GetBaseBehavior(id)->GetKey().empty())
                  {
                    stream << ",\n";
                    stream << Tabs::TWO;
                    stream << "\"behavior\" : \"" << BehaviorComponentManager::GetBaseBehavior(id)->GetKey() << "\"\n";
                  }
                  else
                  {
                    BehaviorComponentManager::GetBaseBehavior(id)->Serialize(stream);
                  }
                }

                //if (ColliderComponentManager::IsActive(id))
                //{
                //  stream << ",\n";
                //  stream << Tabs::TWO;
                //  ColliderComponentManager::Serialize(stream, id);
                //}

                if (!partial)
                {
                    stream << ",\n";
                    // Serialize the animation component
                    if (AnimationComponentManager::IsActive(id))
                    {
                        stream << Tabs::TWO;
                        AnimationComponentManager::Serialize(stream, id);
                        stream << ",\n";
                    }

                    // Serialize the shader component
                    /*if (ShaderModule::IsActive(id))
                    {
                        stream << Tabs::TWO;
                        ShaderModule::Serialize(stream, id);
                        stream << ",\n";
                    }*/

                    // Print the texture filePath
                    stream << Tabs::TWO;
                      TextureComponentManager::Serialize(stream, id);
                }
                else
                {
                    // Print a small statement to avoid json errors (only while implementation of serialization is in flux,
                    // all errors should be avoidable as things get closer to finalization)
                  stream << ",\n";
                  stream << Tabs::TWO << R"("partial" : true)";
                    // This statement doesn't need to be used for anything else, but it can
                  stream << "\n";
                }
                
                
                // Close off the current object
                stream << "}";
                
                // If this is not the last object to be serialized, add a comma
                //if (id != ids.back())
                //{
                //    stream << ",";
                //}
                
                // Print a newline before moving on to the next object
                //stream << "\n";
            }
        }

        // Close the JSON array
        stream << "]\n";
        stream << "}";
    }
}

#pragma endregion