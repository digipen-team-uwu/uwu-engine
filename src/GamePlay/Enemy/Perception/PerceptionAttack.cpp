/******************************************************************************/
/*!
\par        Project Umbra
\file       PerceptionAttack.cpp
\author     Michael Rollosson Halbhuber
\date       2019/11/22
\brief      Implements the Perception Behavior Attack State

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/GamePlay/PerceptionBehavior.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include "glm/vec3.hpp"
#include <UWUEngine\Audio\SoundInterface.h>

#define ANIMATION_FRAMES 40.0f
#define ANIMATION_LENGTH ANIMATION_FRAMES / 30.0f
#define ATTACK_LENGTH 488.0f
#define ATTACK_DAMAGE 1

void FlipScaleX(EntityID id, glm::vec3 scale);

void Behavior<EntityManager::Type::Perception>::Load_Attack()
{
    // DNI, Exists to suppress compiler errors
}

void Behavior<EntityManager::Type::Perception>::Enter_Attack()
{
    SoundInterface::playSound("perception_attack");

    // Get the ID of the entity with the behavior
    EntityID id = GetID();

    // Get the scale and the translation
    glm::vec3 scale = TransformComponentManager::GetScale(id);
    glm::vec4 translation = TransformComponentManager::GetTranslation(id);

    // Check if the enemy is further left than the player
    if (translation.x < TransformComponentManager::GetTranslation(PlayerData::GetPlayerID()).x)
    {
        // Check if the enemy is facing left
        if (scale.x > 0)
        {
            // Flip the enemy's direction
            FlipScaleX(id, scale);
        }
    }
    else
    {
        // Check if the enemy is facing right
        if (scale.x < 0)
        {
            // Flip the enemy's direction
            FlipScaleX(id, scale);
        }
    }

    // Start the attack animation
    SpineAnimationComponentManager::GetAnimation(id).ChangeAnimation("Attack", false);

    // Set the time remaining in the behavior
    attackTimeRemaining = ANIMATION_LENGTH;
}

void Behavior<EntityManager::Type::Perception>::Update_Attack(float dt)
{
    // Uncomment the below for collider stuff
    // EntityID id = GetID();

    attackTimeRemaining -= dt;

    if (attackTimeRemaining <= 0)
    {
        SetNextState(Idle);
    }
    if (attackTimeRemaining <= 0.5)
    {
      ColliderComponentManager::SetCollider(GetID(), attackCollider);
    }
}

void Behavior<EntityManager::Type::Perception>::Exit_Attack()
{
    // Pointless?
    // For now, exists to suppress compiler errors
}

void Behavior<EntityManager::Type::Perception>::Unload_Attack()
{
    // DNI, exists to suppress compiler errors
}


// PRIVATE FUNCTIONS
void FlipScaleX(EntityID id, glm::vec3 scale)
{
    scale.x *= -1;
    TransformComponentManager::SetScale(scale, id);
}