/******************************************************************************/
/*!
\par        Project Umbra
\file       Serialization.cpp
\author     Michael Rollosson Halbhuber
\date       2019/25/19
\brief      Contains helper functions for serializing JSON components

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityFactory.h>
#include <UWUEngine/Serialization.h>
#include "stdio.h"
#include <iomanip>
#include <fstream>
#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <UWUEngine/Helper.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <sstream>
#include <filesystem>
#include <locale>
#include <UWUEngine/Behaviors/ParticleSystem.h>
#include <rttr/type.h>

#ifdef _MSVC
#include <Shlobj_core.h>
#endif

// Allows the RapidJSON Parser to function when members at the end of objects and arrays have trailing commas
#undef RAPIDJSON_PARSE_DEFAULT_FLAGS
#define RAPIDJSON_PARSE_DEFAULT_FLAGS kParseTrailingCommasFlag

// Print the data stored in a vec3 to the stream using JSON array format
using namespace Tabs;
static char readBuffer[65536];
using namespace rapidjson;


void SerializeObject(rttr::instance &obj, std::string file)
{
  StringBuffer string;
  PrettyWriter<StringBuffer> writer(string);
  
  for (auto& it : obj.get_type().get_properties())
  {
    writer.Key(it.get_name().to_string().c_str());
    
  }
  
}

void SerializeVec3(std::ofstream& stream, const char* name, glm::vec3 vector)
{
  stream << THREE << "\"" << name << "\" : [" << vector.x << ", " << vector.y << ", " << vector.z << "]";
}

void SerializeVec4(std::ofstream& stream, const char* name, glm::vec4 vector)
{
  stream << THREE << "\"" << name << "\" : [" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "]";
}

void SerializeVec2(std::ofstream& stream, const char* name, glm::vec2 vector)
{
  stream << THREE << "\"" << name << "\" : [" << vector.x << ", " << vector.y  << "]";
}

void SerializeLevel(const char* level)
{
  // Create a c-style string that represents the file path
#ifdef _WIN64
  std::wstringstream filepath;
  wchar_t* path = 0;
#ifdef _MSVC
  SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);
  filepath << path << L"\\DigiPen";
  _wmkdir(filepath.str().c_str());
  filepath << L"\\Umbra";
  _wmkdir(filepath.str().c_str());
  filepath << L"\\levels";
  _wmkdir(filepath.str().c_str());
  filepath << L"\\" << level << ".json";
  CoTaskMemFree(static_cast<void*>(path));
#endif
#else
  std::stringstream filepath;
  filepath << "./data/levels/" << level << ".json";
#endif
  // Attempt to open the file for writing
  //printf("Attempting to open file %s for writing", filePath); // Debug print
  TraceLogger::Log(TraceLogger::SERIALIZATION, "Attempting to open file %S for writing\n", filepath.str().c_str());
  std::ofstream stream(filepath.str().c_str());

  // Guarantee that the file is open
  TraceLogger::Assert(stream.is_open(), "the level file %s is open.", level);

  // Guarantee that every printed number is interpreted as a float by RapidJSON parsing
  stream.setf(std::ios::fixed);

  // EntityManager::Serialize(stream);
  EntitySys::LevelSerialize(stream);
}

glm::vec3 CreateMemberVec3(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member)
{
  // Check that the object has the member
  //printf("Checking that %s %s component has %s\n", filePath, component, member); // Debug print
  assert(object[component].HasMember(member));
  //printf("Checking that %s %s is array\n", filePath, member); // Debug print
  assert(object[component][member].IsArray());

  // Check that the member is properly formatted
  // Format of JSON array should be [X, Y, Z] where X, Y, and Z are floats
  //printf("Checking that %s %s array is formatted properly\n", filePath, member); // Debug print
  assert(object[component][member][0].IsFloat());
  assert(object[component][member][1].IsFloat());
  assert(object[component][member][2].IsFloat());

  // Get the relevant elements of the member. Done separate from constructor for clarity.
  float memberX = object[component][member][0].GetFloat();
  float memberY = object[component][member][1].GetFloat();
  float memberZ = object[component][member][2].GetFloat();

  // Create the vec3 for the member
  glm::vec3 memberVec(memberX, memberY, memberZ);

  return memberVec;
}

glm::vec2 CreateMemberVec2(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member)
{
  // Check that the object has the member
  //printf("Checking that %s %s component has %s\n", filePath, component, member); // Debug print
  assert(object[component].HasMember(member));
  //printf("Checking that %s %s is array\n", filePath, member); // Debug print
  assert(object[component][member].IsArray());

  // Check that the member is properly formatted
  // Format of JSON array should be [X, Y, Z] where X, Y, and Z are floats
  //printf("Checking that %s %s array is formatted properly\n", filePath, member); // Debug print
  assert(object[component][member][0].IsFloat());
  assert(object[component][member][1].IsFloat());

  // Get the relevant elements of the member. Done separate from constructor for clarity.
  float memberX = object[component][member][0].GetFloat();
  float memberY = object[component][member][1].GetFloat();

  // Create the vec3 for the member
  glm::vec2 memberVec(memberX, memberY);

  return memberVec;
}

/******************************************************************************/
/*!
  \brief
    Creates a vec4 from the data stored in the given object, with the
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
glm::vec4 CreateMemberVec4(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member)
{
  // Check that the object has the member
  //printf("Checking that %s %s component has %s\n", filePath, component, member); // Debug print
  assert(object[component].HasMember(member));
  //printf("Checking that %s %s is array\n", filePath, member); // Debug print
  assert(object[component][member].IsArray());

  // Check that the member is properly formatted
  // Format of JSON array should be [X, Y, Z, W] where X, Y, Z, and W are floats
  // Also, W should be either 0.0 or 1.0
  //printf("Checking that %s %s array is formatted properly\n", filePath, member); // Debug print
  assert(object[component][member][0].IsFloat());
  assert(object[component][member][1].IsFloat());
  assert(object[component][member][2].IsFloat());
  assert(object[component][member][3].IsFloat());

  // Get the relevant elements of the member. Done separate from constructor for clarity.
  float memberX = object[component][member][0].GetFloat();
  float memberY = object[component][member][1].GetFloat();
  float memberZ = object[component][member][2].GetFloat();
  float memberW = object[component][member][3].GetFloat();

  // Create the vec4 for the member
  glm::vec4 memberVec(memberX, memberY, memberZ, memberW);

  return memberVec;
}



// PARTIAL CHECKS
// Similar to the previous, but don't mandate that all the members exist
// (Mandate is necessary for template json files, but not level files,
// as objects constructed in levels are cloned from base template first,
// then edited according to data in level files)
// Used to Serialize/Deserialize levels
