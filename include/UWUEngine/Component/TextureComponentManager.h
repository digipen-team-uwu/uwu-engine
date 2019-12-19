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

class TextureComponentManager : public BaseComponent<TextureComponentManager>
{
    public:
        TextureComponentManager();
        ~TextureComponentManager();
        void InitObject(EntityID) override;
        void ShutdownObject(EntityID ID) override;
        void Update() override {};

        static void SetTextureID(EntityID, GLuint);

        static void SetUV(EntityID, const glm::vec2 &);
        static glm::vec2 &GetUV(EntityID);

        static void SetColor(EntityID, const glm::vec4&);
        static glm::vec4& GetColor(EntityID);
        static void RemoveColor(EntityID);

        static GLuint GetTextureID(EntityID);

        static void SetCurrentTexture(EntityID ID, unsigned accessID);

        static void SetDimensions(const glm::uvec2& dimensions, EntityID ID);
        static glm::uvec2& GetDimensions(EntityID ID);
        static void ShutDown();

        static const std::string& getFilePath(EntityID id, unsigned int accessID = 0);
        static bool HasFilepath(EntityID ID);
        static void SetFilePath(EntityID id, const char * filepath, unsigned int access_id = 0);
        static void SetFilePaths(EntityID id, const std::array<std::string, goc::MAX_SPRITES> &filePaths);

        static void Serialize(std::ofstream& stream, EntityID id);

        static const std::vector<glm::uvec2>& GetArrayDimensions();
        static const std::vector<glm::vec2>& GetArrayUVS();
        static const std::vector<glm::vec4>& GetArrayColors();
        static const std::unordered_map<EntityID, std::array<std::string, goc::MAX_SPRITES>>& GetArrayFilePath();
    private:
        //TODO: add structure holding alternate texture data and add support for switching to alt textures
        static EntityVector<glm::uvec2> dimensions_;
        static EntityVector<glm::vec2> uvs_;
        static EntityVector<glm::vec4> colors_;
        static EntityVector<GLuint> textureID_;

        static std::unordered_map<EntityID, std::array<std::string, goc::MAX_SPRITES>> filePaths_;
};
