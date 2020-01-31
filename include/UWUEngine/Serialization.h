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

void SerializeVec3(std::ofstream& stream, const char* name, glm::vec3 vector);

void SerializeVec4(std::ofstream& stream, const char* name, glm::vec4 vector);

void SerializeVec2(std::ofstream& stream, const char* name, glm::vec2 vector);

void SerializeLevel(const char* level);

