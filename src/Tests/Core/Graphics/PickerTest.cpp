#include <catch2/catch.hpp>
#include <UWUEngine/Graphics/Debugs/Picker.h>
#include <UWUTest/Helper/TestFloat.hpp>
#include <UWUEngine/Graphics/Texture/TextureAtlaser.h>
#include "stb_image.h"

#include <glm/gtx/intersect.hpp>

using UWUTest::t_float;

TEST_CASE("Picking transparent pixel")
{
  SECTION("GLM ray triangle intersection")
  {
    glm::vec3 origin(0, 0, 0);
    glm::vec3 dir(0, 0, -1);

    glm::vec3
      vert1(-1, -1, -1),
      vert2(1, 1, -1),
      vert3(1, -1, -1);

    glm::vec2 baryPos;
    float dist;

    glm::intersectRayTriangle(origin, dir, vert3, vert1, vert2, baryPos, dist);

    REQUIRE(t_float(baryPos.x) == 0.5f);
    REQUIRE(t_float(baryPos.y) == 0.5f);
    REQUIRE(t_float(dist) == 1.0f);
  }
  SECTION("2x2 image")
  {
    //int width, height, channels;
    //unsigned char* image = stbi_load("./assets/props/Props_RockSlope_02.png", &width, &height, &channels, 0);
    //int offset = static_cast<int>(((1 - Data_[chosen_ID].uv.y) * static_cast<float>(raw_data.width) + Data_[chosen_ID].uv.x));
    //offset *= raw_data.channels;
    //auto alpha = static_cast<unsigned char>(image[offset] + 3);
    //
    
  }
}