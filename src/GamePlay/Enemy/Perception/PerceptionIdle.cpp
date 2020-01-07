/******************************************************************************/
/*!
\par        Project Umbra
\file       PerceptionIdle.cpp
\author     Michael Rollosson Halbhuber
\date       2019/11/22
\brief      Implements the idle behavior for the Perception Enemy Type

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/GamePlay/PerceptionBehavior.h>
#include <UWUEngine/GamePlay/PlayerController.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include "glm/vec3.hpp"
#include <UWUEngine/Audio/SoundInterface.h>

// The range at which the enemy will begin atttacking (slightly past the actual attack range)
#define AGGRO_X_RANGE 500.0f

// Modifies the acceptable range of Y positions the player can be in for the enemy to begin attacking
// Positive increases the range, negative decreases it
// Don't make this more negative than the player's Y scale (check player.json), as I have no idea what that might do
// Not used right now, so 0.0f
#define AGGRO_Y_OFFSET 0.0f

void Behavior<EntityManager::Type::Perception>::Enter_Idle()
{
    // Set the idle animation
    SpineAnimationComponentManager::GetAnimation(GetID()).ChangeAnimation("Idle", true);
    ColliderComponentManager::SetCollider(GetID(), idleCollider);
}

void Behavior<EntityManager::Type::Perception>::Load_Idle()
{
    // Exists to suppress compiler errors
}

void Behavior<EntityManager::Type::Perception>::Update_Idle(float dt)
{
  //SoundInterface::playSound("perception_idle");
    // Get the player's ID
    EntityID playerID = PlayerData::GetPlayerID();

    // Get this object's translation
    glm::vec4 translation = TransformComponentManager::GetTranslation(GetID());

    // Get the player's translation and scale
    glm::vec3 playerScale = TransformComponentManager::GetScale(playerID);
    glm::vec4 playerTranslation = TransformComponentManager::GetTranslation(playerID);

    // Check if the player is within aggro range of the enemy
    
    // First, check if the player is within one player's height (Y Scale) of the enemy
    
    float yDifference = playerTranslation.y - translation.y;
    if (yDifference < 0)
    {
        // If it's negative, invert it
        yDifference *= -1.0f;
    }

    if (yDifference <= playerScale.y + AGGRO_Y_OFFSET)
    {
        // Now, check if the player is within the X aggro range of the enemy
        float xDifference = playerTranslation.x - translation.x;
        if (xDifference < 0)
        {
            // If it's negative, invert it
            xDifference *= -1.0f;
        }

        if (xDifference < AGGRO_X_RANGE)
        {
            // Attack the player
            SetNextState(Attack);
        }
    }
}

void Behavior<EntityManager::Type::Perception>::Unload_Idle()
{
    // Exists to suppress compiler errors
}

void Behavior<EntityManager::Type::Perception>::Exit_Idle()
{
    // For now, exists to suppress compiler errors
}