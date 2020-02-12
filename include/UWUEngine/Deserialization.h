#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <rapidjson/document.h>
#include <vector>
#include <fstream>
#include <UWUEngine/Entity/EntitySys.h>
#include <UWUEngine/Component/AnimationComponentManager.h>

std::vector<EntityID> DeserializeLevel(const char* level);

void CheckTransform(rapidjson::Value& object, EntityID ID, const char* filePath, bool mandate = true);

void CheckPhysics(rapidjson::Value& object, EntityID ID, const char* filePath, bool mandate = true);

void CheckAnimation(rapidjson::Value& object, EntityID ID, const char* filePath);

void CheckTexture(rapidjson::Value& object, EntityID ID, const char* filePath);

void CheckShader(rapidjson::Value& object, EntityID ID, const char* filePath);

void CheckSpineSkeleton(rapidjson::Value& object, EntityID ID, const char* filePath);

glm::vec4 CreateMemberVec4(rapidjson::Value& object,
  const char* filePath, const char* component, const char* member);

glm::vec3 CreateMemberVec3(rapidjson::Value& object,
  const char* filePath, const char* component, const char* member);

glm::vec2 CreateMemberVec2(rapidjson::Value& object,
  const char* filePath, const char* component, const char* member);

void CheckCollider(rapidjson::Value& object, EntityID ID, const char* filePath);

float CheckFloat(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member);

int CheckInt(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member);

bool CheckBool(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member);

const char* CheckString(rapidjson::Value& object, const char* filePath,
  const char* component, const char* member);

void CheckPartialTransform(rapidjson::Value& object, EntityID ID, const char* filePath);

void CheckPartialPhysics(rapidjson::Value& object, EntityID ID, const char* filePath);

glm::vec4 DeserializeVec4(rapidjson::Value& object);

glm::vec3 DeserializeVec3(rapidjson::Value& object);

glm::vec2 DeserializeVec2(rapidjson::Value& object);

AnimationComponentManager::AnimationData DeserializeAnimation(rapidjson::Value& sprite);