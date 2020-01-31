/******************************************************************************/
/*!
\par        Project Umbra
\file       Serialization.h
\author     Michael Rollosson Halbhuber
\date       2019/25/19
\brief      Contains helper functions for serializing JSON components

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <rapidjson/document.h>
#include <vector>
#include <fstream>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/AnimationComponentManager.h>

namespace Tabs //!< tab sizes
{
  inline const char* ONE{ "\t" };        //!< tabbing for object
  inline const char* TWO{ "\t\t" };      //!< tabbing for object member
  inline const char* THREE{ "\t\t\t" };  //!< tabbing for object member variable
  inline const char* FOUR{ "\t\t\t\t" }; //!< tabbing for nested member variable
  inline const char* FIVE{ "\t\t\t\t\t" }; //!< tabbing for nested member variable
  inline const char* SIX{ "\t\t\t\t\t\t" }; //!< tabbing for nested member variable
  inline const char* SEVEN{ "\t\t\t\t\t\t\t" }; //!< tabbing for nested member variable
}

/******************************************************************************/
/*!
  \brief
    Print the data stored in a vec3 to the stream using JSON array format

  \param stream
    The stream to be printed to

  \param name
    The name of the vec3 member object

  \param vector
    The vector to be serialized
*/
/******************************************************************************/
void SerializeVec3(std::ofstream& stream, const char* name, glm::vec3 vector);

/******************************************************************************/
/*!
  \brief
    Print the data stored in a vec4 to the stream using JSON array format

  \param stream
    The stream to be printed to

  \param name
    The name of the vec4 member object

  \param vector
    The vector to be serialized
*/
/******************************************************************************/
void SerializeVec4(std::ofstream& stream, const char* name, glm::vec4 vector);

void SerializeVec2(std::ofstream& stream, const char* name, glm::vec2 vector);

/******************************************************************************/
/*!
  \brief
    Serializes all data in a level to a JSON file named after the level

  \param level
    The name of the json file the level should be serialized to
    (without file extension)
*/
/******************************************************************************/
void SerializeLevel(const char* level);

/******************************************************************************/
/*!
  \brief
    Loads the object data from a JSON formatted level file

  \param level
    The name of the json file the level should be deserialized from
    (without file extension)

  \return
    A vector containing the ids of all serialized game objects
*/
/******************************************************************************/
std::vector<EntityID> DeserializeLevel(const char* level);

/******************************************************************************/
/*!
  \brief
    Checks for a Transform Component in an object and constructs it if it exists

  \param object
    The greater json object containing the nested component object

  \param ID
    The ID of the game object the component belongs to

  \param filePath
    The file path of the json file the object originates from

  \param mandate
    Determines whether or not to mandate a full construction, requiring every
    member be present in the json object
*/
/******************************************************************************/
void CheckTransform(rapidjson::Value& object, EntityID ID, const char* filePath, bool mandate = true);

/******************************************************************************/
/*!
  \brief
    Checks for a Physics Component in an object and constructs it if it exists

  \param object
    The greater json object containing the nested component object

  \param ID
    The ID of the game object the component belongs to

  \param filePath
    The file path of the json file the object originates from

  \param mandate
    Determines whether or not to mandate a full construction, requiring every
    member be present in the json object
*/
/******************************************************************************/
void CheckPhysics(rapidjson::Value& object, EntityID ID, const char* filePath, bool mandate = true);

/******************************************************************************/
/*!
  \brief
    Checks for an Animation Component in an object and constructs it if it exists

  \param object
    The greater json object containing the nested component object

  \param ID
    The ID of the game object the component belongs to

  \param filePath
    The file path of the json file the object originates from
*/
/******************************************************************************/
void CheckAnimation(rapidjson::Value& object, EntityID ID, const char* filePath);

/******************************************************************************/
/*!
  \brief
    Checks for a Texture Component in an object and constructs it if it exists

  \param object
    The greater json object containing the nested component object

  \param ID
    The ID of the game object the component belongs to

  \param filePath
    The file path of the json file the object originates from
*/
/******************************************************************************/
void CheckTexture(rapidjson::Value& object, EntityID ID, const char* filePath);

/******************************************************************************/
/*!
  \brief
    Checks for a Shader Component in an object and constructs it if it exists

  \param object
    The greater json object containing the nested component object

  \param ID
    The ID of the game object the component belongs to

  \param filePath
    The file path of the json file the object originates from
*/
/******************************************************************************/
void CheckShader(rapidjson::Value& object, EntityID ID, const char* filePath);

void CheckSpineSkeleton(rapidjson::Value& object, EntityID ID, const char* filePath);

/******************************************************************************/
/*!
  \brief
    Creates a vec4 from the data stored in the given document, with the
    given component and member names

  \param object
    The greater json object containing the member vec4

  \param filePath
    The file path of the json file the object originates from

  \param component
    The name of the component that contains the member vec3

  \param member
    The name of the vec4 member

  \return
    A vec4 containing the data from the json object member
*/
/******************************************************************************/
glm::vec4 CreateMemberVec4(rapidjson::Value& object,
    const char* filePath, const char* component, const char* member);

/******************************************************************************/
/*!
  \brief
    Creates a vec3 from the data stored in the given document, with the
    given component and member names

  \param object
    The greater json object containing the member vec3

  \param filePath
    The file path of the json file the object originates from

  \param component
    The name of the component that contains the member vec3

  \param member
    The name of the vec3 member

  \return
    A vec3 containing the data from the json object member
*/
/******************************************************************************/
glm::vec3 CreateMemberVec3(rapidjson::Value& object,
    const char* filePath, const char* component, const char* member);

glm::vec2 CreateMemberVec2(rapidjson::Value& object,
  const char* filePath, const char* component, const char* member);

void CheckCollider(rapidjson::Value& object, EntityID ID, const char* filePath);

/******************************************************************************/
/*!
  \brief
    Obtains a float stored in the given object, in the given nested component
    object, with the given name

  \param object
    The greater json object containing the float

  \param filePath
    The file path of the json file the object originates from

  \param component
    The name of the component that contains the float

  \param member
    The name of the float member

  \return
    The float assigned to the member name
*/
/******************************************************************************/
float CheckFloat(rapidjson::Value& object, const char* filePath,
    const char* component, const char* member);

/******************************************************************************/
/*!
  \brief
    Obtains an int stored in the given object, in the given nested component
    object, with the given name

  \param object
    The greater json object containing the int

  \param filePath
    The file path of the json file the object originates from

  \param component
    The name of the component that contains the int

  \param member
    The name of the int member

  \return
    The int assigned to the member name
*/
/******************************************************************************/
int CheckInt(rapidjson::Value& object, const char* filePath,
    const char* component, const char* member);

/******************************************************************************/
/*!
  \brief
    Obtains a bool stored in the given object, in the given nested component
    object, with the given name

  \param object
    The greater json object containing the bool

  \param filePath
    The file path of the json file the object originates from

  \param component
    The name of the component that contains the bool

  \param member
    The name of the bool member

  \return
    The bool assigned to the member name
*/
/******************************************************************************/
bool CheckBool(rapidjson::Value& object, const char* filePath,
    const char* component, const char* member);

/******************************************************************************/
/*!
  \brief
    Obtains a c-style string stored in the given object, in the given nested
    component object, with the given name

  \param object
    The greater json object containing the string

  \param filePath
    The file path of the json file the object originates from

  \param component
    The name of the component that contains the string

  \param member
    The name of the string member

  \return
    The c-style string assigned to the member name
*/
/******************************************************************************/
const char* CheckString(rapidjson::Value& object, const char* filePath,
    const char* component, const char* member);

void CheckPartialTransform(rapidjson::Value& object, EntityID ID, const char* filePath);

void CheckPartialPhysics(rapidjson::Value& object, EntityID ID, const char* filePath);



//I made these for convenience -hadi

glm::vec4 DeserializeVec4(rapidjson::Value& object);

glm::vec3 DeserializeVec3(rapidjson::Value& object);

glm::vec2 DeserializeVec2(rapidjson::Value& object);

AnimationComponentManager::AnimationData DeserializeAnimation(rapidjson::Value& sprite);