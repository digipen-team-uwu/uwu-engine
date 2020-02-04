/******************************************************************************/
/*!
\par        Project Umbra
\file       TextureComponentManager.h
\author     Chau Nguyen
\date       2019/09/20
\brief      Managing textures

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/BaseComponent.h>
#include <string>

namespace UWUEngine
{
  class Texture
  {
  public:
    Texture (glm::uvec2& dimension, glm::vec2& uvs, glm::vec4& colors, GLuint& textureID, std::array<std::string, goc::MAX_SPRITES>& filePath)
      : dimensions_(dimension), uvs_(uvs), colors_(colors), textureID_(textureID), filePaths_(filePath)
    {}

#pragma region Setter
    void SetDimension(const glm::uvec2& dimension);
    void SetTextureID(GLuint textureID);
    void SetUVS(const glm::vec2& uvs);
    void SetColors(const glm::vec4& colors);
    void SetFilePath(const std::string& filePath, unsigned accessID);
#pragma endregion

#pragma region Getter
    const glm::uvec2& GetDimension() const;
    const GLuint& GetTextureID() const;
    const glm::vec2& GetUVS() const;
    const glm::vec4& GetColors() const;
    const std::string& GetFilePaths(unsigned accessID) const;
#pragma endregion

  private:
    glm::uvec2& dimensions_;
    glm::vec2& uvs_;
    glm::vec4& colors_;
    GLuint& textureID_;
    std::array<std::string, goc::MAX_SPRITES>& filePaths_;
  };

  class TextureComponentManager : public ...future......
  {
  public:
    TextureComponentManager() = default;
    ~TextureComponentManager();
    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;
    void Update() override {}

    Texture operator[](EntityID ID);

    Texture getTexture(EntityID ID);

#pragma region Setter
    void SetFilePath(EntityID, const char* filePath, unsigned accessID);
    void SetFilePaths(EntityID, const std::array<std::string, goc::MAX_SPRITES>& filePaths);
#pragma endregion

#pragma region Getter
    const std::string& getFilePath(EntityID ID, unsigned accessID);
    const EntityVector<glm::uvec2>& GetArrayDimensions() const;
    const EntityVector<glm::vec2>& GetArrayUVS() const;
    const EntityVector<glm::vec4>& GetArrayColors() const;
    const std::unordered_map<EntityID, std::array<std::string, goc::MAX_SPRITES>>& GetArrayFilePaths() const;
#pragma endregion

    void RemoveColor(EntityID ID);
    bool HasFilepath(EntityID ID);
    void SetCurrentTexture(EntityID ID, unsigned accessID);
    void Serialize(std::ofstream& stream, EntityID id);

  private:
    EntityVector<glm::uvec2> dimensions_;
    EntityVector<glm::vec2> uvs_;
    EntityVector<glm::vec4> colors_;
    EntityVector<GLuint> textureID_;
    std::unordered_map<EntityID, std::array<std::string, goc::MAX_SPRITES>> filePaths_;
  };
}
