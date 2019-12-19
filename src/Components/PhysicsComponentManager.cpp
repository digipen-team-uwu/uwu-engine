/******************************************************************************/
/*!
\par        Project Umbra
\file       PhysicsComponentManager.cpp
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing physics components

Copyright ☺ 2019 DigiPen, All rights reserved.

*/
/******************************************************************************/
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <UWUEngine/constants.h>
#include <UWUEngine/Serialization.h>
#include <UWUEngine/FrameRateController.h>
#include <magic_enum.hpp>

template<>
size_t RegisterComponentHelper<PhysicsComponentManager>::RegisterComponentHelper_ID = EntityManager::AddComponent<PhysicsComponentManager>(ComponentUpdateOrder::Physics);

namespace goc = GameObjectConstants;

EntityVector<PhysicsComponentManager::BodyType> PhysicsComponentManager::type_(goc::INITIAL_OBJECT_COUNT);

EntityVector<glm::vec4> PhysicsComponentManager::oldTranslation_(goc::INITIAL_OBJECT_COUNT);

EntityVector<glm::vec4> PhysicsComponentManager::acceleration_(goc::INITIAL_OBJECT_COUNT);

EntityVector<glm::vec4> PhysicsComponentManager::velocity_(goc::INITIAL_OBJECT_COUNT);

EntityVector<float> PhysicsComponentManager::rotationalVelocity_(goc::INITIAL_OBJECT_COUNT);

EntityVector<glm::vec4> PhysicsComponentManager::drag_(goc::INITIAL_OBJECT_COUNT);

EntityVector<float> PhysicsComponentManager::inverseMass_(goc::INITIAL_OBJECT_COUNT);

EntityVector<float> PhysicsComponentManager::restitution_(goc::INITIAL_OBJECT_COUNT);

void PhysicsComponentManager::SetAcceleration(const glm::vec4& acceleration, EntityID ID)
{
  acceleration_[ID] = acceleration;
}

void PhysicsComponentManager::SetVelocity(const glm::vec4& velocity, EntityID ID)
{
  velocity_[ID] = velocity;
}

void PhysicsComponentManager::SetRotationalVelocity(const float rotationalVelocity, EntityID ID)
{
  rotationalVelocity_[ID] = rotationalVelocity;
}

void PhysicsComponentManager::SetBodyType(BodyType type, EntityID ID)
{
  type_[ID] = type;
}

void PhysicsComponentManager::SetOldTranslation(const glm::vec4& oldTranslation, EntityID ID)
{
  oldTranslation_[ID] = oldTranslation;
}

void PhysicsComponentManager::SetDrag(const glm::vec4& drag, EntityID ID)
{
  drag_[ID] = drag;
}

void PhysicsComponentManager::SetRestitution(float restitution, EntityID ID)
{
  restitution_[ID] = restitution;
}

void PhysicsComponentManager::SetInverseMass(const float inverseMass, EntityID ID)
{
  inverseMass_[ID] = inverseMass;
}

PhysicsComponentManager::BodyType PhysicsComponentManager::GetBodyType(EntityID ID)
{
  return type_[ID];
}

const glm::vec4& PhysicsComponentManager::GetAcceleration(EntityID ID)
{
  return acceleration_[ID];
}

const glm::vec4& PhysicsComponentManager::GetVelocity(EntityID ID)
{
  return velocity_[ID];
}

const glm::vec4& PhysicsComponentManager::GetOldTranslation(EntityID ID)
{
  return oldTranslation_[ID];
}

float PhysicsComponentManager::GetRotationalVelocity(EntityID ID)
{
  return rotationalVelocity_[ID];
}


const glm::vec4& PhysicsComponentManager::GetDrag(EntityID ID)
{
  return drag_[ID];
}

float PhysicsComponentManager::GetInverseMass(EntityID ID)
{
  return inverseMass_[ID];
}

float PhysicsComponentManager::GetRestitution(EntityID ID)
{
  return restitution_[ID];
}

std::vector<glm::vec4>& PhysicsComponentManager::GetDebugVelocities()
{
  return velocity_;
}

void PhysicsComponentManager::InitObject(EntityID ID)
{
  type_[ID] = BodyType::STATIC;
  rotationalVelocity_[ID] = 0.0f;
  drag_[ID] = { 0, 0, 0, 0 };
  velocity_[ID] = glm::vec4(0.0f);
  acceleration_[ID] = glm::vec4(0.0f);
  inverseMass_[ID] = 0.0f;
  restitution_[ID] = 1.0f;
}

void PhysicsComponentManager::Update()
{
  std::vector<EntityID> ids = EntityManager::GetIDs();
  auto it = ids.begin();

  oldTranslation_.operator std::vector<glm::vec4, std::allocator<glm::vec4>>& ().swap(TransformComponentManager::translation_);

  while (it != ids.end())
  {
    if (TransformComponentManager::IsActive(*it) && IsActive(*it))
    {
      float dt = FrameRateController::GetDeltaTime<float>();
      const glm::vec4 pos = GetOldTranslation(*it);
      const glm::vec4 vel = velocity_[*it];
      const glm::vec4 acl = acceleration_[*it];
      float invMass = inverseMass_[*it];

      oldTranslation_[*it] = pos;
      glm::vec4 newVel = (vel + (acl * invMass) * dt) * (glm::vec4{ 1, 1, 1, 0 } -drag_[*it] * dt);
      glm::vec4 newPos = pos + newVel * dt;
      TransformComponentManager::SetTranslation(newPos, *it);
      velocity_[*it] = newVel;
      TransformComponentManager::SetRotation(TransformComponentManager::GetRotation(*it) + rotationalVelocity_[*it] * dt, *it);
    }
    else
    {
      TransformComponentManager::SetTranslation(oldTranslation_[*it], *it);
    }
    ++it;
  }

  /*static int frameoffset;
  ++frameoffset;
  if (frameoffset % 3 == 0)
  {
    auto& rot = const_cast<std::vector<float>&>(TransformComponentManager::GetArrayRotation());
    EntityVectorManager::QuickSortBy(rot);
  }*/
}


// deprecated
/*void PhysicsComponentManager::addPhysics(EntityID ID)
{
    glm::vec4 empty_vec = glm::vec4(0.0f);
    glm::vec4 empty_pos = { 0,0,0,1 };
    glm::mat4 empty_mat = glm::mat4(0.0f);


    if (ID >= isActive_.size())
    {
        oldTranslation_.push_back(empty_pos);
        acceleration_.push_back(empty_vec);
        velocity_.push_back(empty_vec);
        rotationalVelocity_.push_back(0.0f);
        drag_.push_back(0.0f);
        inverseMass_.push_back(0.0f);
        isActive_.push_back(true);
    }
    else
    {
        oldTranslation_[ID] = empty_pos;
        acceleration_[ID] = empty_vec;
        velocity_[ID] = empty_vec;
        rotationalVelocity_[ID] = 0.0f;
        drag_[ID] = 0.0f;
        inverseMass_[ID] = 0.0f;
        isActive_[ID] = true;
    }
}*/

// Below code written by Michael Rollosson Halbhuber
void PhysicsComponentManager::Serialize(std::ofstream& stream, EntityID id, bool partial)
{
  // Check if the given ID has an active physics component
  if (PhysicsComponentManager::IsActive(id))
  {
    // Open a "physics" JSON object
    stream << "\"physics\" :\n";
    stream << Tabs::TWO <<  "{\n";

    // Serialize body type
    stream << Tabs::THREE << R"("type" : ")" << magic_enum::enum_name(type_[id]) << '"';
    stream << ",\n";

    // Print the velocity
    SerializeVec4(stream, "velocity", velocity_[id]);
    stream << ",\n";

    // Print the acceleration
    SerializeVec4(stream, "acceleration", acceleration_[id]);
    stream << ",\n";

    // Print the rotational velocity
    stream << Tabs::THREE << "\"rotational velocity\" : " << rotationalVelocity_[id] << ",\n";

    if (!partial)
    {
      // Print the drag
      SerializeVec4(stream, "drag", drag_[id]);
      stream << ",\n";

      // Print the Inverse Mass
      stream << Tabs::THREE << "\"inverse mass\" : " << inverseMass_[id] << "\n";
    }
    else
    {
      // Print to avoid json errors
      // Doesn't need to be used for anything else, but nobody is stopping you from doing so
      stream << Tabs::THREE << "\"partial\" : true";
    }
    // Close the physics object
    stream << "}";
  }
}