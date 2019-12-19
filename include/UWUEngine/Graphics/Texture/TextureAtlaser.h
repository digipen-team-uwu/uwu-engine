/******************************************************************************/
/*!
\par        Project Umbra
\file       TextureAtlaser.h
\author     Chau Nguyen
\date       2019/11/1
\brief      Atlasing textures

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Entity/EntityVector.h>
#include <UWUEngine/Component/MeshComponentManager.h>
#include <vector>
// include rectpack2D lib
#include "finders_interface.h"
#include <UWUEngine/Instances.h>
#include <UWUEngine/BaseSystem.h>

using namespace rectpack2D;
namespace TA = TextureAtlasing;
using spaces_type = rectpack2D::empty_spaces<TA::allow_flip, default_empty_spaces>;
using rect_type = output_rect_t<spaces_type>;
using AtlasLayer = unsigned;
using Area = unsigned;

class TextureAtlaser : public BaseSystem<TextureAtlaser>
{
private:
    class RawData; // forward declaration
public:
    TextureAtlaser();
    ~TextureAtlaser() = default;

    static void ClearData();

    static void LoadRawData(int total...);
    static void LoadRawData(const std::vector<std::string>&);

    static void Atlasing(std::vector<RawData>& data_);
    static void report_result(const rect_wh& result_size, const std::vector<rect_type>& rectangles);

    static const std::vector<rect_type>& GetRectangles();
    static const TextureAtlaser::RawData& GetRawData(const std::string&);

    static void LoadAtlasPage(GLboolean isTwice_ = false);

    static const glm::vec2 GetAtlasUV(EntityID);
    static const glm::vec2 GetAtlasScale(EntityID);

    static const std::vector<glm::vec2>& GetArrayAtlasUV();
    static const std::vector<glm::vec2>& GetArrayAtlasScale();

    //static void SetAtlasUVScale(EntityID id, unsigned int accessID = 0);

    static void GetAtlasData(const char* filepath, glm::vec2 *scale, glm::vec2 *uvs, unsigned* layer);

    static void SetAtlasLayers(EntityID, AtlasLayer);
    static const AtlasLayer GetAtlasLayers(EntityID);
    static const std::vector<AtlasLayer>& GetArrayAtlasLayer();

    static const GLuint GetTextureID();

    static glm::vec2 GetBrayanTexture(const std::string&);

    static void SetAtlasData(EntityID id, unsigned int accessID = 0);

private:
    static void CheckLayerCounter(int&, int&);
    static void ResetLayerCounter();
    //static void SetAtlasLayerToEntityID();
    //static void SetAtlasUV(EntityID, unsigned int accessID = 0);
    //static void SetAtlasScale(EntityID, unsigned int accessID = 0);
    //static void SetLayerFromFilePath(EntityID, unsigned int accessID = 0);
    class RawData
    {
    public:
        RawData() = default;
        ~RawData() = default;
        RawData(int x_offset_, int y_offset_, int width_, int height_, Area area_, int channels_,
            unsigned char* image_, const std::string& filePath_, VaoKey vao_key_, AtlasLayer atlas_layer_)
            : x_offset(x_offset_), y_offset(y_offset_), width(width_), height(height_), area(area_),
            channels(channels_), image(image_), filePath(filePath_), vao_key(vao_key_), layer(atlas_layer_)

        {};
        bool operator() (const RawData& r1, const RawData& r2);
        int x_offset;
        int y_offset;
        int width;
        int height;
        Area area;
        int channels;
        unsigned char* image;
        std::string filePath;
        VaoKey vao_key;
        AtlasLayer layer;
    };
    static int max_side;
    static int discard_step;
    static flipping_option runtime_flipping_mode;
    static GLuint texID;

    //static std::unordered_map<AtlasLayer, std::pair<rect_wh, std::vector<RawData>>> data_;

    static std::unordered_map<std::string, RawData> filePath_to_RawData;

    static std::vector<rect_type> rectangles;

    static EntityVector<AtlasLayer> atlas_layers;
    static EntityVector<glm::vec2> atlas_uv;
    static EntityVector<glm::vec2> atlas_scale;

    static unsigned layer_counter;
    static unsigned total_width;
    static unsigned total_height;
};
