/******************************************************************************/
/*!
\par        Project Umbra
\file       SpineSkeletonComponentManager.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Spine skeleton component manager,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Component/SpineSkeletonComp.h>
#include <UWUEngine/Graphics/SingleTexture.h>
#include <UWUEngine/Modules/UBOMod.h>
#include <UWUEngine/Systems/LogSys.h>

#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <spine/extension.h>


namespace UWUEngine
{
  struct Vertex
  {
    glm::vec3 position; //!<position of the vertex
    glm::vec4 color = { 0.0f, 1.0f, 0.0f, 1.0f }; //!<color of the vertex
    glm::vec2 texCoords = { 0.0f, 0.0f }; //!<texture coordinate of the vertex

    Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v) :
      position(x, y, z), color(r, g, b, a), texCoords(u, v) {}

    Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texCoords) :
      position(position), color(color), texCoords(texCoords) {}
  };

  SpineSkeleton::SpineSkeleton(SpineData& spineData, EntityID ID) :
    skeleton(spSkeleton_create(&spineData.GetSkeletonData())), ID(ID), scaleOffset(spineData.GetScaleOffset())
  {
  }

  void SpineSkeleton::ChangeSkin(const char* skinName)
  {
    spSkeleton_setSkinByName(skeleton, skinName);
  }

  spSkeleton* SpineSkeleton::GetSkeleton() const
  {
    return skeleton;
  }

  spSkeletonData* SpineSkeleton::GetSkeletonData() const
  {
    return skeleton->data;
  }

  const glm::mat4 SpineSkeletonComp::GetScaleOffSet(EntityID ID)
  {
    float scaleOffset = GetSkeleton(ID).scaleOffset;
    return scale(glm::vec3(scaleOffset, scaleOffset, scaleOffset));
  }

  void SpineSkeletonComp::InitObject(EntityID ID)
  {
  }

  void SpineSkeletonComp::ShutdownObject(EntityID ID)
  {
    skeletons.erase(ID);
  }

  void SpineSkeletonComp::SetSkeleton(EntityID ID, SpineData& spineData)
  {
    if (skeletons.find(ID) != skeletons.end())
    {
      Get<LogSys>().Log(LogSys::DEBUG) << "Skeleton component already exists for object: " << ID << std::endl;
    }
    skeletons.insert_or_assign(ID, SpineSkeleton(spineData, ID));
  }

  void SpineSkeletonComp::SetSkeleton(EntityID ID, const char* name)
  {
    if (skeletons.find(ID) != skeletons.end())
    {
      Get<LogSys>().Log(LogSys::DEBUG) << "Skeleton component already exists for object: " << ID << std::endl;
    }
    skeletons.insert_or_assign(ID, SpineSkeleton(Get<SpineDataMod>().GetData(name), ID));
  }

  SpineSkeleton& SpineSkeletonComp::GetSkeleton(EntityID ID)
  {
    return skeletons.find(ID)->second;
  }

  void SpineSkeleton::DrawMesh(
    std::vector<Vertex> vertices,
    std::vector<unsigned> indices,
    GLuint textureID
  )
  {
    //VAO Setup
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_DYNAMIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

    //color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

    //texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoords)));

    //Draw the mesh
    //Enable texture and VAO
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBindVertexArray(VAO);

    //Draw Mesh
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);

    //Disable shader, texture and VAO
    glBindVertexArray(0);

    //Destroy the mesh
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
  }
}