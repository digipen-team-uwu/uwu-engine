/******************************************************************************/
    /*!
    \par        Project Umbra
    \file       Random.cpp
    \author     Brayan Lopez
    \date       2019/09/06
    \brief      Random module implementation

    Copyright � 2019 DigiPen, All rights reserved.
    */
    /******************************************************************************/
#include <UWUEngine/Random.h>
#include <ctime>

namespace UWUEngine
{

//initialize Random module, with a given seed
RandomSys::RandomSys(ISpace* p) : System(p)
{
#ifdef _DEBUG
  rng.seed(0);
#else
  rng.seed(std::time(nullptr));
#endif
}

//generates int between min and max INCLUSIVE
int RandomSys::Range(int min, int max)
{
  bool correct = min < max;
  std::uniform_int_distribution dist(correct ? min : max, correct ? max : min);
  return dist(rng);
}

//generates float between min and max INCLUSIVE
float RandomSys::Range(float min, float max)
{
  bool correct = min < max;
  std::uniform_real_distribution dist(correct ? min : max, std::nextafter(correct ? max : min, FLT_MAX));

  return dist(rng);
}

//generates double between min and max INCLUSIVE.
double RandomSys::Range(double min, double max)
{
  bool correct = min < max;
  std::uniform_real_distribution<double> dist(correct ? min : max, std::nextafter(correct ? max : min, DBL_MAX));
  return dist(rng);
}

glm::vec4 RandomSys::Range(const glm::vec4& min, const glm::vec4& max)
{
  bool correctx = min.x < max.x;
  bool correcty = min.y < max.y;
  bool correctz = min.z < max.z;
  bool correctw = min.w < max.w;
  std::uniform_real_distribution distx(correctx ? min.x : max.x, std::nextafter(correctx ? max.x : min.x, FLT_MAX));
  std::uniform_real_distribution disty(correcty ? min.y : max.y, std::nextafter(correcty ? max.y : min.y, FLT_MAX));
  std::uniform_real_distribution distz(correctz ? min.z : max.z, std::nextafter(correctz ? max.z : min.z, FLT_MAX));
  std::uniform_real_distribution distw(correctw ? min.w : max.w, std::nextafter(correctw ? max.w : min.w, FLT_MAX));

  return { distx(rng), disty(rng), distz(rng), distw(rng) };
}

glm::vec3 RandomSys::Range(const glm::vec3& min, const glm::vec3& max)
{
  bool correctx = min.x < max.x;
  bool correcty = min.y < max.y;
  bool correctz = min.z < max.z;

  std::uniform_real_distribution distx(correctx ? min.x : max.x, std::nextafter(correctx ? max.x : min.x, FLT_MAX));
  std::uniform_real_distribution disty(correcty ? min.y : max.y, std::nextafter(correcty ? max.y : min.y, FLT_MAX));
  std::uniform_real_distribution distz(correctz ? min.z : max.z, std::nextafter(correctz ? max.z : min.z, FLT_MAX));

  return { distx(rng), disty(rng), distz(rng) };
}

glm::vec2 RandomSys::Range(const glm::vec2& min, const glm::vec2& max)
{
  bool correctx = min.x < max.x;
  bool correcty = min.y < max.y;

  std::uniform_real_distribution distx(correctx ? min.x : max.x, std::nextafter(correctx ? max.x : min.x, FLT_MAX));
  std::uniform_real_distribution disty(correcty ? min.y : max.y, std::nextafter(correcty ? max.y : min.y, FLT_MAX));

  return { distx(rng), disty(rng) };
}

} // namespace UWUEngine
