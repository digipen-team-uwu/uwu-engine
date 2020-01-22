/******************************************************************************/
  /*!
  \par        Project Umbra
  \file       DebugManager.cpp
  \author     Hadi Alhussieni
  \date       2019/10/06
  \brief      Implementation for a debug manager that displays debug information
              when prompted by the user.

  Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityCacher.h>
#include <UWUEngine/Debugs/DebugManager.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Component/TransformComponentManager.h>
#include <UWUEngine/Graphics/Shader/ShaderModule.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <vector>
#include <UWUEngine/Engine.h>
#include "UWUEngine/Graphics/Texture/TextureAtlaser.h"



VaoKey DebugManager::vectorVAO = -1;
VaoKey DebugManager::hitboxVAO = -1;
bool DebugManager::drawVectors;
bool DebugManager::drawHitboxes;
std::vector<float> DebugManager::rotation;
std::vector<glm::vec4> DebugManager::translation;
std::vector<glm::vec3> DebugManager::scale;
std::vector<glm::vec4> DebugManager::color;
std::vector<glm::vec2> DebugManager::uvs;
std::vector<glm::uvec2> DebugManager::dims;
std::vector<glm::vec2> DebugManager::atlasUVs;
std::vector<glm::vec2> DebugManager::atlasScale;
std::vector<unsigned> DebugManager::atlasLayer;
std::tuple<GLenum, GLuint, GLuint> DebugManager::lineMesh;
std::tuple<GLenum, GLuint, GLuint> DebugManager::squareMesh;

DebugManager::DebugManager()
{
  if (DebugConstants::SHOW_VELOCITY)
  {
    EnableVelocityVectors();
  }

  if (DebugConstants::SHOW_VELOCITY)
  {
	  EnableHitboxes();
  }

  EntityCacher::CacheFile("./assets/pixel.png");
}

void DebugManager::EnableVelocityVectors()
{
  if (vectorVAO == -1)
  {
    lineMesh = MeshComponentManager::getSquareMesh();
    vectorVAO = Instances::CreateInstances(lineMesh);
  }
  drawVectors = true;
}

void DebugManager::DisableVelocityVectors()
{
  drawVectors = false;
}

void DebugManager::EnableHitboxes()
{
  if (hitboxVAO == -1)
  {
    squareMesh = MeshComponentManager::getSquareMesh();
    hitboxVAO = Instances::CreateInstances(squareMesh);
  }
  drawHitboxes = true;
}

void DebugManager::DisableHitboxes()
{
  drawHitboxes = false;
}


void DebugManager::Render()
{
  #ifdef _DEBUG
  if (drawVectors || drawHitboxes)
  {
    glDisable(GL_DEPTH_TEST);

    if (drawVectors)
    {
      for (auto it : EntityManager::GetIDs())
      {
        if (PhysicsComponentManager::IsActive(it))
        {
          DebugManager::rotation[it] = RotationFromVec(PhysicsComponentManager::GetVelocity(it));
          DebugManager::scale[it] = { glm::length(PhysicsComponentManager::GetVelocity(it)) / 5, 5.f, 0.f };
          DebugManager::translation[it] = TransformComponentManager::GetTranslation(it) + PhysicsComponentManager::GetVelocity(it) / 10.f - glm::vec4(glm::abs(scale[it] / 2.f), 0) + glm::vec4(glm::abs(TransformComponentManager::GetScale(it)) / 2.f, 0);
          DebugManager::uvs[it] = { 0, 0 };
        }
      }
      Instances::UpdateInstances(vectorVAO, &DebugManager::rotation, &DebugManager::translation, &DebugManager::scale, &DebugManager::color, &DebugManager::uvs, &DebugManager::dims, &DebugManager::atlasUVs, &DebugManager::atlasScale);
    }

    if (drawHitboxes)
    {
      for (auto i = ColliderComponentManager::begin(); i != ColliderComponentManager::end(); ++i)
      {
        i->second->Render();
      }
    }

    GLSLShader shader = ShaderModule::GetEntityShader();
    shader.Use();

    // bind to proper texture unit 0
    if (drawVectors)
    {
      glBindVertexArray(Instances::GetVAOid(vectorVAO));
      glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL, static_cast<GLsizei>(EntityVectorManager::GetVectorSize()));
      glBindVertexArray(0);
    }

    shader.UnUse();
    
    glEnable(GL_DEPTH_TEST);
    glm::vec2 atlasscale;
    glm::vec2 atlasuv;
    unsigned atlaslayer;
    // TODO:: stop assuming debug draw has atlas layer 0
    TextureAtlaser::GetAtlasData("./assets/pixel.png", &atlasscale, &atlasuv, &atlaslayer);
    std::fill(DebugManager::atlasUVs.begin(), DebugManager::atlasUVs.end(), atlasuv);
    std::fill(DebugManager::atlasLayer.begin(), DebugManager::atlasLayer.end(), atlaslayer);
    std::fill(DebugManager::atlasScale.begin(), DebugManager::atlasScale.end(), atlasscale);
    std::fill(DebugManager::uvs.begin(), DebugManager::uvs.end(), glm::vec2{ -1, -1 });
  }
  #endif
}

void DebugManager::Update()
{
  if (InputManager::KeyPressed(DebugConstants::VELOCITY_KEY))
  {
    if (!drawVectors)
    {
      EnableVelocityVectors();
    }
    else
    {
      DisableVelocityVectors();
    }

    if (!drawHitboxes)
    {
      EnableHitboxes();
    }
    else
    {
      DisableHitboxes();
    }
  }

  if (drawHitboxes || drawVectors)
  {
    if (rotation.size() < EntityVectorManager::GetVectorSize())
    {
      glm::vec2 atlasscale;
      glm::vec2 atlasuv;
      unsigned atlaslayer;
      // TODO:: stop assuming debug draw has atlas layer 0
      TextureAtlaser::GetAtlasData("./assets/pixel.png", &atlasscale, &atlasuv, &atlaslayer);
      atlasUVs.resize(EntityVectorManager::GetVectorSize(), atlasuv);
      atlasScale.resize(EntityVectorManager::GetVectorSize(), atlasscale);
      atlasLayer.resize(EntityVectorManager::GetVectorSize(), atlaslayer);
      rotation.resize(EntityVectorManager::GetVectorSize());
      translation.resize(EntityVectorManager::GetVectorSize());
      scale.resize(EntityVectorManager::GetVectorSize());
      color.resize(EntityVectorManager::GetVectorSize(), { 1, 1, 1, 1 });
      uvs.resize(EntityVectorManager::GetVectorSize(), { -1, -1 });
      dims.resize(EntityVectorManager::GetVectorSize(), { 1, 1 });
      

      if (drawVectors)
          Instances::CreateInstances(lineMesh);
      if (drawHitboxes)
          Instances::CreateInstances(squareMesh);
    }
  }
}