#include <UWUEngine/GamePlay/FangBehavior.h>
#include <UWUEngine/Component/SpineAnimationComponentManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>
#include "glm/vec3.hpp"

void Behavior<EntityManager::Type::Fang_>::Load_Running()
{
    // DNI
}

void Behavior<EntityManager::Type::Fang_>::Enter_Running()
{
    SpineAnimationComponentManager::GetAnimation(GetID()).ChangeAnimation("Run 2.0", true);
}

void Behavior<EntityManager::Type::Fang_>::Update_Running(float dt)
{
    // Have Fang walk back and forth
    glm::vec4 velocity = {};

    // A very minor gravity component to induce collisions with ground for detection purposes
    glm::vec4 gravity = { 0, -100.f, 0, 0 };

    // Float to flip the direction of the walking speed
    float flip = 1.0f;

    // Check if Fang is facing left
    if (TransformComponentManager::GetScale(GetID()).x > 0)
    {
        flip = -1.0f;
    }

    velocity.x = walkSpeed * flip;

    // Begin moving Fang
    PhysicsComponentManager::SetVelocity(velocity + gravity, GetID());

}

void Behavior<EntityManager::Type::Fang_>::Exit_Running()
{
    // Currently exists to suppress compiler warnings
}

void Behavior<EntityManager::Type::Fang_>::Unload_Running()
{
	// DNI
}
