#include <UWUEngine/GamePlay/FangBehavior.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include "glm/vec3.hpp"
#include <UWUEngine/Audio/SoundInterface.h>

// TO DO: CHANGE THESE TO MATCH LENGTH OF SPINE ANIMATION FOR EACH
#define STUN_TIME 0.5f
#define DEATH_TIME 0.5F

void Behavior<EntitySys::Type::Fang_>::Load_Hurt()
{
    // DNI
}

void Behavior<EntitySys::Type::Fang_>::Enter_Hurt()
{
    health -= 1;
    if (health > 99999)
    {
        health = 0;
    }

    // Instead of separating death and hurt states, just do both in this state for now
    if (health == 0)
    {
        SoundInterface::playSound("fang_dead");
        SpineAnimationComponentManager::GetAnimation(GetID()).ChangeAnimation("Death", false);
        hurtTimeRemaining = DEATH_TIME;
    }
    else
    {
        SoundInterface::playSound("fang_hurt");
        SpineAnimationComponentManager::GetAnimation(GetID()).ChangeAnimation("Hurt_01", false);
        hurtTimeRemaining = STUN_TIME;
    }
}

void Behavior<EntitySys::Type::Fang_>::Update_Hurt(float dt)
{
    hurtTimeRemaining -= dt;
    if (hurtTimeRemaining <= 0)
    {
        if (health == 0)
        {
            EntitySys::Destroy(GetID());
        }
        else
        {
            SetNextState(Grounded);
        }
    }
}

void Behavior<EntitySys::Type::Fang_>::Exit_Hurt()
{
    // Currently exists to suppress compiler warnings
}

void Behavior<EntitySys::Type::Fang_>::Unload_Hurt()
{
	// DNI
}
