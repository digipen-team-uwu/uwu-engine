/******************************************************************************/
/*!
\par        Project Umbra
\file       TransformComponentManager.h
\author     Chau Nguyen
\date       2019/09/13
\brief      Managing transform components

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/BaseComponent.h>
#include <UWUEngine/Component/MeshComponentManager.h>
#include <UWUEngine/Component/PhysicsComponentManager.h>

class TransformComponentManager : public BaseComponent<TransformComponentManager>
{
    public:
      TransformComponentManager() = default;
        ~TransformComponentManager() = default;
        void Update() override {};
        void InitObject(EntityID ID) override;
        void ShutdownObject(EntityID ID) override {};
  
        static void SetTranslation(const glm::vec4& translation, EntityID ID);
        static void SetRotation(float rotation, EntityID ID);
        static void SetScale(const glm::vec3& scale, EntityID ID);

        static const glm::vec3& GetScale(EntityID ID);
        static const glm::vec4& GetTranslation(EntityID ID);
        static float GetRotation(EntityID ID);

        static const std::vector<glm::vec4>& GetArrayTranslation();
        static const std::vector<float>& GetArrayRotation();
        static const std::vector<glm::vec3>& GetArrayScale();

		static glm::mat4 GetModelMatrix(EntityID ID);

    static glm::mat4 GetSpineModelMatrix(EntityID ID);
 
		static const glm::vec4& OffsetTranslation(EntityID ID, glm::vec3 const& offset);

        friend void PhysicsComponentManager::Update();

        // Prints all values of the given object to the given stream
        // in JSON format, if the transform is activated for the object
        static void Serialize(std::ofstream &stream, EntityID id);
    private:    
        static EntityVector<glm::vec4> translation_;
        static EntityVector<float> rotation_;
        static EntityVector<glm::vec3> scale_;

        friend class Editor;
};
