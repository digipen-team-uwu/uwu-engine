/******************************************************************************/
/*!
\par        Project Umbra
\file       GameObjectfactory.h
\author     Michael Rollosson Halbhuber
\date       2019/09/19
\brief      Constructs game objects from serialized files

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/BaseSystem.h>
#include <document.h>
#include "EntityManager.h"

//!class EntityFactory
class EntityFactory : public BaseSystem<EntityFactory>
{

public:
  /******************************************************************************/
  /*!
    \brief
      Starts up the GameObjectFactory class (currently does nothing)
  */
  /******************************************************************************/
  EntityFactory() = default;

  void Update() override {};

  /******************************************************************************/
  /*!
    \brief
      Shuts down the GameObjectFactory class (currently does nothing)
  */
  /******************************************************************************/
  ~EntityFactory() = default;

  /******************************************************************************/
  /*!
    \brief
      Creates a game object of the given type, currently through serialization only

    \param type
      The type of object to deserialize

    \return
      The ID of the created game object
  */
  /******************************************************************************/
  static EntityID CreateObject(EntityManager::Type type);

  /******************************************************************************/
  /*!
    \brief
      Creates an object from the json file with the given file path
      via serialization

    \param object
      The json object file containing the data for the game object

    \param filePath
      The file path of the source file of the json object
  */
  /******************************************************************************/
  static EntityID CreateObject(rapidjson::Value& object, const char* filePath);

  friend class EntityCacher;
private:

  //! Buffer to read json files into
  static char readBuffer[65536];

  // This'll be useful for caches, probably
};
