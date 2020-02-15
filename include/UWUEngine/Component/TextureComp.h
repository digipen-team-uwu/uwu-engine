#pragma once
#include <UWUEngine/Component/EntityComp.h>
#include <UWUEngine/Component/Component.h>
#include <glm/gtx/transform.hpp>
#include <UWUEngine/constants.h>
#include <array>

using namespace GameObjectConstants;
using AtlasLayer = unsigned;

namespace UWUEngine
{
  class Texture
  {
  public:
    Texture(glm::uvec2& dimension, glm::vec2& uvs, glm::vec4& colors, std::array<std::string, MAX_SPRITES>& filePath,
      AtlasLayer& atlas_layers, glm::vec2& atlas_uv, glm::vec2& atlas_scale)
      : dimensions_(dimension), uvs_(uvs), colors_(colors), filePaths_(filePath), atlas_layers_(atlas_layers),
        atlas_uv_(atlas_uv), atlas_scale_(atlas_scale)
    {}

#pragma region Setter
    void SetAtlasLayer(const AtlasLayer& layer);
    void SetAtlasUV(const glm::vec2& uv);
    void SetAtlasScale(const glm::vec2& scale);
    void SetDimension(const glm::uvec2& dimension);
    void SetUVS(const glm::vec2& uvs);
    void SetColors(const glm::vec4& colors);
    void SetFilePath(const std::string& filePath, unsigned accessID);
#pragma endregion

#pragma region Getter
    const AtlasLayer& GetAtlasLayer() const;
    const glm::vec2& GetAtlasUV() const;
    const glm::vec2& GetAtlasScale() const;
    const glm::uvec2& GetDimension() const;
    const glm::vec2& GetUVS() const;
    const glm::vec4& GetColors() const;
    const std::string& GetFilePaths(unsigned accessID) const;
#pragma endregion

  private:
    glm::uvec2& dimensions_;
    glm::vec2& uvs_;
    glm::vec4& colors_;
    std::array<std::string, MAX_SPRITES>& filePaths_;

    AtlasLayer& atlas_layers_;
    glm::vec2& atlas_uv_;
    glm::vec2& atlas_scale_;
  };

  class TextureComp : public Component<TextureComp, Texture>
  {
  public:
    TextureComp(ISpace* space) : Component<TextureComp, Texture>(space) {}
    ~TextureComp() = default;
    void InitObject(EntityID ID) override;
    void ShutdownObject(EntityID ID) override;

    Texture operator[](EntityID ID);

    Texture getTexture(EntityID ID);

#pragma region Setter
    void SetFilePath(EntityID, const char* filePath, unsigned accessID);
    void SetFilePaths(EntityID, const std::array<std::string, MAX_SPRITES> & filePaths);
#pragma endregion

#pragma region Getter
    const std::string& getFilePath(EntityID ID, unsigned accessID);

    const EntityVector<AtlasLayer>& GetArrayAtlasLayers() const;
    const EntityVector<glm::vec2>& GetArrayAtlasUV() const;
    const EntityVector<glm::vec2>& GetArrayAtlasScale() const;
    
    const EntityVector<glm::uvec2>& GetArrayDimensions() const;
    const EntityVector<glm::vec2>& GetArrayUVS() const;
    const EntityVector<glm::vec4>& GetArrayColors() const;

    const std::unordered_map<EntityID, std::array<std::string, MAX_SPRITES>>& GetArrayFilePaths() const;
#pragma endregion

#pragma Atlas Setter & Getter
    void SetAtlasData(EntityID ID, unsigned accessID = 0);
    void GetAtlasData(const char* filepath, glm::vec2* scale, glm::vec2* uvs, unsigned* layer);
#pragma endregion

    void RemoveColor(EntityID ID);
    bool HasFilepath(EntityID ID);
    void SetCurrentTexture(EntityID ID, unsigned accessID);

  private:
    EntityVector<glm::uvec2> dimensions_{ parent };
    EntityVector<glm::vec2> uvs_{ parent };
    EntityVector<glm::vec4> colors_{ parent };
    std::unordered_map<EntityID, std::array<std::string, MAX_SPRITES>> filePaths_;

    EntityVector<AtlasLayer> atlas_layers{ parent };
    EntityVector<glm::vec2> atlas_uv{ parent };
    EntityVector<glm::vec2> atlas_scale{ parent };
  };
}