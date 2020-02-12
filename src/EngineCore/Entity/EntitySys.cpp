/******************************************************************************/
    /*!
    \par        Project Umbra
    \file       EntitySys.cpp
    \author     Brayan Lopez
    \date       2019/09/13
    \brief      Entity System Implementation

    Copyright � 2019 DigiPen, All rights reserved.
    */
/******************************************************************************/

#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/Entity/EntityIDManager.h>
#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <magic_enum.hpp>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Component/BehaviorComp.h>
#include <UWUEngine/Component/ParentChildComponentManager.h>
#include <UWUEngine/Engine.h>
#include <fstream>
#include <UWUEngine/Serialization.h>
#include "UWUEngine/Instances.h"



//std::vector<EntityID> EntitySys::ids;
//std::vector<EntityID> EntitySys::freeIDs;
//EntityVector<EntitySys::Type> EntitySys::types(goc::INITIAL_OBJECT_COUNT);
//EntityVector<std::uint8_t> EntitySys::destroyeds(goc::INITIAL_OBJECT_COUNT);
//EntityVector<std::uint8_t> EntitySys::clearImmune(goc::INITIAL_OBJECT_COUNT);
//EntityVector<std::uint8_t> EntitySys::dontSerialize(goc::INITIAL_OBJECT_COUNT);
//bool EntitySys::destroyed = false;
//EntityID EntitySys::idCount = 0;
//
//size_t EntitySys::update_ = static_cast<size_t>(ComponentUpdateOrder::LAST);
//size_t EntitySys::behavior_ = static_cast<size_t>(ComponentUpdateOrder::Behavior);

#pragma region GETTERS

using namespace UWUEngine;

size_t EntitySys::EntityCount()
{
  return ids.size();
}

const std::vector<EntityID>& EntitySys::GetIDs()
{
    return ids;
}

void EntitySys::AddTag(EntityID id, Tag tag)
{
  tags[id] |= tag;
}

void EntitySys::SetTags(EntityID id, Tag tag)
{
  tags[id] = tag;
}

void EntitySys::RemoveTag(EntityID id, Tag tag)
{
  tags[id] &= ~tag;
}

bool EntitySys::HasTag(EntityID ID, Tag tag)
{
    return tags[ID] & tag;
}


EntityID EntitySys::New(Type type)
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

      Instances::CreateInstances(Mesh::GetEntityMesh());
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

EntitySys::EntitySys()
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

EntitySys::~EntitySys()
{
    ids.clear();
    freeIDs.clear();
}

void EntitySys::Update( )
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

void EntitySys::InitComponents()
{
  for (auto& comp : GetComponents())
  {
    comp.second->Init();
  }
}

void EntitySys::Destroy(EntityID id, int idsIndex)
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

void EntitySys::DestroyAll()
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

std::map<size_t, EntitySys::IComponentConstructorProxy*>& EntitySys::GetComponents()
{
  static std::map<size_t, IComponentConstructorProxy*> components;
  return components;
}

void EntitySys::Destroy_()
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

void EntitySys::Deactivate(EntityID& id)
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

void EntitySys::SetClearImmunity(EntityID id, bool clearImmunity)
{
  clearImmune[id] = clearImmunity;
}

void EntitySys::SetDontSerialize(EntityID id, bool serialize)
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
void EntitySys::LevelSerialize(std::ofstream &stream)
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
              
                if (types[id] != EntitySys::Cyclone
                    && types[id] != EntitySys::Logo_
                    && types[id] != EntitySys::Player
                    && types[id] != EntitySys::Text_
                    && types[id] != EntitySys::Solid)
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
                if (TransformSys::IsActive(id))
                {
                    stream << Tabs::TWO;
                    TransformSys::Serialize(stream, id);
                }
                
                // Serialize the physics component
                if (PhysicsSys::IsActive(id))
                {
                    stream << ",\n";
                    stream << Tabs::TWO;
                    PhysicsSys::Serialize(stream, id, partial);
                }

                if (BehaviorComp::IsActive(id))
                {
                  if (!BehaviorComp::GetBaseBehavior(id)->GetKey().empty())
                  {
                    stream << ",\n";
                    stream << Tabs::TWO;
                    stream << "\"behavior\" : \"" << BehaviorComp::GetBaseBehavior(id)->GetKey() << "\"\n";
                  }
                  else
                  {
                    BehaviorComp::GetBaseBehavior(id)->Serialize(stream);
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
                    if (AnimationSys::IsActive(id))
                    {
                        stream << Tabs::TWO;
                        AnimationSys::Serialize(stream, id);
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
                      TextureSys::Serialize(stream, id);
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