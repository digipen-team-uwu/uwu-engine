/******************************************************************************/
/*!
\par        Project Umbra
\file       PerceptionBehavior.cpp
\author     Michael Rollosson Halbhuber
\date       2019/11/22
\brief      Implements the behaviors for the Perception Enemy Type (immobile snake)

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/GamePlay/PerceptionBehavior.h>
#include <UWUEngine/Audio/SoundInterface.h>

// The amount of time the enemy is stunned for after getting hurt
#define STUN_TIME 0.25f

void Behavior<EntitySys::Type::Perception>::Enter_Hurt()
{

    // Decrement health by one
    health -= 1;

    // Just in case, check for an overflow
    if (health > 99999)
    {
        // Set health back to zero
        health = 0;
    }

    // Check for death
    if (health == 0)
    {
        SoundInterface::playSound("perception_dead");
        // Destroy the object, as death has occurred
        EntitySys::Destroy(GetID());
    }
    else
    {
        SoundInterface::playSound("perception_hurt");
        // Activate the stun time
        stunTimeRemaining = STUN_TIME;
    }
}

void Behavior<EntitySys::Type::Perception>::Load_Hurt()
{
    // Exists to suppress compiler errors
}

void Behavior<EntitySys::Type::Perception>::Update_Hurt(float dt)
{
    // Wait for stun time to run out
    stunTimeRemaining -= dt;

    if (stunTimeRemaining <= 0.0f)
    {
        SetNextState(Idle);
    }
}

void Behavior<EntitySys::Type::Perception>::Unload_Hurt()
{
    // Exists to suppress compiler errors
}

void Behavior<EntitySys::Type::Perception>::Exit_Hurt()
{
    // Currently exists to suppress compiler errors
}