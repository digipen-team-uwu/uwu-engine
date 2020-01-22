/******************************************************************************/
/*!
\par        Project Umbra
\file       TextureAtlaser.cpp
\author     Chau Nguyen
\date       2019/11/1
\brief      Atlasing textures

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>
#include <cstdarg>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include "UWUEngine/Graphics/Texture/TextureLoader.h"


int TextureAtlaser::layer_counter;
int TextureAtlaser::tracker_ = 0;
int TextureAtlaser::start_index_ = 0;
bool TextureAtlaser::is_first_pass_;
int TextureAtlaser::max_side;
int TextureAtlaser::discard_step;
flipping_option TextureAtlaser::runtime_flipping_mode;
GLuint TextureAtlaser::texID;
std::vector<rect_type> TextureAtlaser::rectangles;
EntityVector<AtlasLayer> TextureAtlaser::atlas_layers{ goc::INITIAL_OBJECT_COUNT };
EntityVector<glm::vec2> TextureAtlaser::atlas_uv{ goc::INITIAL_OBJECT_COUNT };
EntityVector<glm::vec2> TextureAtlaser::atlas_scale{ goc::INITIAL_OBJECT_COUNT };
std::unordered_map<std::string, TextureAtlaser::RawData>TextureAtlaser::filePath_to_RawData;
std::vector<TextureAtlaser::RawData>TextureAtlaser::atlas_data_;

TextureAtlaser::TextureAtlaser()
{
    max_side = TA::MAX_SIZE_PAGE;
    discard_step = 1;
    // disable flipping image for best fit
    runtime_flipping_mode = flipping_option::DISABLED;
    stbi_set_unpremultiply_on_load(1);
    is_first_pass_ = true;
    layer_counter = 0;
}

void TextureAtlaser::ClearData()
{
    //free image ptrs
    for (auto it1 = filePath_to_RawData.begin(); it1 != filePath_to_RawData.end(); ++it1)
    {
        stbi_image_free(it1->second.image);
    }
    filePath_to_RawData.clear();
    atlas_data_.clear();
    Reset();
    glDeleteTextures(1, &texID);
    //TextureLoader::FlushCacheFiles();
}

void TextureAtlaser::Reset()
{
    is_first_pass_ = true;
    layer_counter = 0;
    start_index_ = 0;
    tracker_ = 0;
}

void TextureAtlaser::report_result(const rect_wh& result_size, const std::vector<rect_type>& rectangles)
{
    TraceLogger::Log(TraceLogger::DEBUG) << "Resultant atlas bin: " << result_size.w << " " << result_size.h << std::endl;

    for (const auto& r : rectangles) {
      TraceLogger::Log(TraceLogger::TRACE) << r.x << " " << r.y << " " << r.w << " " << r.h << std::endl;
    }
}

const std::vector<rect_type>& TextureAtlaser::GetRectangles()
{
    return rectangles;
}

const TextureAtlaser::RawData& TextureAtlaser::GetRawData(const std::string& filePath)
{
    return filePath_to_RawData.at(filePath);
}


void TextureAtlaser::CheckingLayer()
{
    if (is_first_pass_)
    {
        for (auto it = atlas_data_.begin(); it != atlas_data_.end(); ++it)
        {
            rectangles.emplace_back(rect_xywh(0, 0, it->width + TA::SIZE_OFFSET, it->height + TA::SIZE_OFFSET));
        }
        // update first pass check
        is_first_pass_ = false;
    }

    // create a root page
    auto packing_root = spaces_type({ max_side, max_side });
    packing_root.flipping_mode = runtime_flipping_mode;

    // init iterator
    auto r = rectangles.begin();

    while (!rectangles.empty())
    {
        for (; r != rectangles.end(); ++r)
        {
            if (const auto inserted_rectangle = packing_root.insert(std::as_const(*r).get_wh()))
            {
                *r = *inserted_rectangle;
            }
            else
            {
                // update start index
                start_index_ = tracker_;

                // increase layer counter
                ++layer_counter;

                // update container of rectangles
                rectangles.assign(r, rectangles.end());

                // update layer_counter
                for (int j = 0; j < rectangles.size(); ++j)
                {
                    filePath_to_RawData.find(atlas_data_[j + start_index_].filePath)->second.layer = layer_counter;
                }
                // update iterator
                r = rectangles.begin();
                // create new root page
                packing_root = spaces_type({ max_side, max_side });
                packing_root.flipping_mode = runtime_flipping_mode;
            }
            // update tracker
            ++tracker_;
        }
        // clear after done using
        rectangles.clear();
    }
}

void TextureAtlaser::Atlasing(std::vector<RawData>& data_)
{
    auto report_successful = [](rect_type&) {
        return callback_result::CONTINUE_PACKING;
    };

    auto report_unsuccessful = [](rect_type&) {
        return callback_result::ABORT_PACKING;
    };

    for (auto it = data_.begin(); it != data_.end(); ++it)
    {
        rectangles.emplace_back(rect_xywh(0, 0, it->width + TA::SIZE_OFFSET, it->height + TA::SIZE_OFFSET));
    }
    //Find best packing using all provided custom rectangle orders.
    using rect_ptr = rect_type*;

    auto my_custom_order_1 = [](const rect_ptr a, const rect_ptr b) {
        return a->get_wh().pathological_mult() > b->get_wh().pathological_mult();
    };

    auto my_custom_order_2 = [](const rect_ptr a, const rect_ptr b) {
        return a->get_wh().pathological_mult() < b->get_wh().pathological_mult();
    };

    auto atlas_page = find_best_packing<spaces_type>(
        rectangles,
        make_finder_input(
            max_side,
            discard_step,
            report_successful,
            report_unsuccessful,
            runtime_flipping_mode
        ),
        my_custom_order_1,
        my_custom_order_2
        );
#ifdef _DEBUG
    report_result(atlas_page, rectangles);
#endif
    // update uv offset
    for (int i = 0; i < rectangles.size(); ++i)
    {
        filePath_to_RawData.find(data_[i].filePath)->second.x_offset = rectangles[i].x;
        filePath_to_RawData.find(data_[i].filePath)->second.y_offset = rectangles[i].y;
    }
    rectangles.clear();
}

bool TextureAtlaser::RawData::operator()(const RawData& r1, const RawData& r2)
{
    return r1.area < r2.area;
}

void TextureAtlaser::LoadAtlasPage(GLboolean isTwice_)
{
    if (isTwice_)
    {
        ClearData();
    }
    TextureLoader::LoadCacheFiles();
    LoadRawData(TextureLoader::GetLoadCache());

    for(auto& i : filePath_to_RawData)
    {
        atlas_data_.push_back(i.second);
    }

    std::sort(atlas_data_.begin(), atlas_data_.end(), RawData());

    CheckingLayer();

    std::map<AtlasLayer, std::vector<RawData>> atlasdata;
    for (auto& i : filePath_to_RawData)
    {
        atlasdata[i.second.layer].push_back(i.second);
    }

    for (auto it = atlasdata.begin(); it != atlasdata.end(); ++it)
    {
        auto& raw_data = it->second;
        std::sort(raw_data.begin(), raw_data.end(), RawData());
    }

    for (auto& j : atlasdata)
    {
        Atlasing(j.second);
    }

    glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &texID);

    glTextureParameteri(texID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(texID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(texID, GL_TEXTURE_WRAP_R, GL_REPEAT);
    
    // allocate GPU texture buffer storage for atlas page
    //glTextureStorage2D(textureID, 1, GL_RGBA8, atlas_page.w, atlas_page.h);
    glTextureStorage3D(texID, TA::MIPMAP_LEVEL, GL_RGBA8, 
        TA::MAX_SIZE_PAGE, 
        TA::MAX_SIZE_PAGE,
        TA::MAX_LAYERS);

    // copy data from CPU to texture buffer
    for (auto it1 = filePath_to_RawData.begin(); it1 != filePath_to_RawData.end(); ++it1)
    {
        glTextureSubImage3D(texID, 0, it1->second.x_offset + TA::OFFSET_OFFSET, it1->second.y_offset + TA::OFFSET_OFFSET, it1->second.layer,
            it1->second.width, it1->second.height, 1, GL_RGBA, GL_UNSIGNED_BYTE, it1->second.image);
        glGenerateTextureMipmap(texID);
    }

    // bind to texture unit 0
    glBindTextureUnit(0, texID);

    // create instance vbos and get correspond vao key
    VaoKey vao_key = Instances::CreateInstances(MeshComponentManager::GetEntityMesh());

    // set entity vao key
    Instances::SetEntityVAOKey(vao_key);
    
    // setting atlas uv and atlas scale
    auto& ids = EntityManager::GetIDs();
    for (int i = 0; i < ids.size(); ++i)
    {
        SetAtlasData(i);
    }
}

void TextureAtlaser::LoadRawData(const std::vector<std::string>& files)
{
    for (auto it = files.begin(); it != files.end(); ++it)
    {
        int image_width;
        int image_height;
        int number_channels;
        unsigned char* image;

        image = stbi_load(it->c_str(), &image_width, &image_height, &number_channels, 0);

        if (image)
        {
            Area area = image_width * image_height;
            RawData raw = RawData(0, 0, image_width, image_height, area, number_channels, image,
                *it, TextureAtlasing::INVALID_VAO_KEY, layer_counter);
            filePath_to_RawData.insert({ *it, raw });
        }
        else
        {
            TraceLogger::Log(TraceLogger::FAILURE) << "Failed to load texture" << std::endl;
            std::exit(-1);
        }
    }
}

void TextureAtlaser::LoadRawData(int total...)
{
    va_list args;
    va_start(args, total);

    for (int i = 0; i < total; ++i)
    {
        const char* filePath = va_arg(args, const char*);

        int image_width;
        int image_height;
        int number_channels;
        unsigned char* image;

        image = stbi_load(filePath, &image_width, &image_height, &number_channels, 0);

        if (image)
        {
            Area area = image_width * image_height;
            RawData raw = RawData(0, 0, image_width, image_height, area, number_channels, image,
                filePath, TextureAtlasing::INVALID_VAO_KEY, layer_counter);
            filePath_to_RawData.find(filePath)->second = raw;
        }
        else
        {
          TraceLogger::Log(TraceLogger::FAILURE) << "Failed to load texture" << std::endl;
            exit(-1);
        }
    }
    va_end(args);
}

void TextureAtlaser::SetAtlasData(EntityID ID, unsigned int accessID)
{
    std::string filePath = TextureComponentManager::getFilePath(ID, accessID);

    if (filePath == "")
    {
        return;
    }
        
    auto it = filePath_to_RawData.find(filePath);
    if(it == filePath_to_RawData.end())
    {
        return;
    }
    auto& raw_data = it->second;

    constexpr auto PIXEL_CENTER = (0.5 / 4096);

    auto width = raw_data.width;
    auto height = raw_data.height;
    auto u_scale = (TA::MAX_SIZE_PAGE /*atlas_pages[vao_key].second.w*/ / static_cast<float>(width));
    auto v_scale = (TA::MAX_SIZE_PAGE /*atlas_pages[vao_key].second.h*/ / static_cast<float>(height));
    auto Xoffset = raw_data.x_offset;
    auto Yoffset = raw_data.y_offset;

    auto u_coord = (static_cast<float>(Xoffset) / TA::MAX_SIZE_PAGE); //atlas_pages[vao_key].second.w;
    auto v_coord = (static_cast<float>(Yoffset) / TA::MAX_SIZE_PAGE); //atlas_pages[vao_key].second.h;

    atlas_uv[ID] = glm::vec2(u_coord, v_coord);
    atlas_scale[ID] = glm::vec2{ u_scale, v_scale };
    atlas_layers[ID] = raw_data.layer;
}

void TextureAtlaser::GetAtlasData(const char* filepath, glm::vec2 *scale, glm::vec2 *uvs, unsigned *layer)
{
    auto raw_data = filePath_to_RawData.at(filepath);

    auto width = raw_data.width;
    auto height = raw_data.height;
    auto Xoffset = raw_data.x_offset;
    auto Yoffset = raw_data.y_offset;
    auto u_scale = TA::MAX_SIZE_PAGE /*atlas_pages[vao_key].second.w*/ / static_cast<float>(width);
    auto v_scale = TA::MAX_SIZE_PAGE /*atlas_pages[vao_key].second.h*/ / static_cast<float>(height);
    auto u_coord = static_cast<float>(Xoffset) / TA::MAX_SIZE_PAGE; //atlas_pages[vao_key].second.w;
    auto v_coord = static_cast<float>(Yoffset) / TA::MAX_SIZE_PAGE; //atlas_pages[vao_key].second.h;

    *scale = glm::vec2{ u_scale, v_scale };
    *uvs = glm::vec2{ u_coord, v_coord };
    *layer = raw_data.layer;
}

void TextureAtlaser::SetAtlasLayers(EntityID ID, AtlasLayer new_layer)
{
    atlas_layers[ID] = new_layer;
}

const AtlasLayer TextureAtlaser::GetAtlasLayers(EntityID ID)
{
    return atlas_layers[ID];
}

const std::vector<AtlasLayer>& TextureAtlaser::GetArrayAtlasLayer()
{
    return atlas_layers;
}

const GLuint TextureAtlaser::GetTextureID()
{
    return texID;
}

const glm::vec2 TextureAtlaser::GetAtlasUV(EntityID ID)
{
    return atlas_uv[ID];
}

const glm::vec2 TextureAtlaser::GetAtlasScale(EntityID ID)
{
    return atlas_scale[ID];
}

const std::vector<glm::vec2>& TextureAtlaser::GetArrayAtlasUV()
{
    return atlas_uv;
}

const std::vector<glm::vec2>& TextureAtlaser::GetArrayAtlasScale()
{
    return atlas_scale;
}

glm::vec2 TextureAtlaser::GetBrayanTexture(const std::string& filePath)
{
    int image_width;
    int image_height;
    int number_channels;
    unsigned char* image;

    image = stbi_load(filePath.c_str(), &image_width, &image_height, &number_channels, 0);
    if (image)
    {
        stbi_image_free(image);
        return glm::vec2(image_width, image_height);
    }
    else
    {
      TraceLogger::Log(TraceLogger::ERROR) << "Failed to load texture" << std::endl;
      std::exit(-1);
    }
}

