/******************************************************************************/
    /*!
    \par        Project Umbra
    \file       Random.h
    \author     Brayan Lopez
    \date       2019/09/06
    \brief      Random module declaration

    Copyright � 2019 DigiPen, All rights reserved.
    */
    /******************************************************************************/

#pragma once
#include <UWUEngine/BaseSystem.h>
#include <time.h>
#include <random>
#include <glm/glm.hpp>

class Random : public BaseSystem<Random>
{
public:
  //initialize Random module, with a given seed
  explicit Random(unsigned long long int seed = 0);
  void Update() override {};
  ~Random() = default;

  //! \brief
  //    generates int between min and max INCLUSIVE
  //  \param min
  //    min value
  //  \param max
  //    max value
  //  \return
  //    random number between min and max
  static int Range(int min, int max);

  //! \brief
  //   generates float between min and max INCLUSIVE
  //  \param min
  //    min value
  //  \param max
  //    max value
  //  \return
  //    random float between min and max
  static float Range(float min, float max);

  //! \brief
  //   generates double between min and max INCLUSIVE
  //  \param min
  //    min value
  //  \param max
  //    max value
  //  \return
  //    random double between min and max
  static double Range(double min, double max);

  //! \brief
  //   generates vec4 with values ranging from min to max
  //  \param min
  //    min values
  //  \param max
  //    max values
  //  \return
  //    random vec4 with values ranging from min to max
  static glm::vec4 Range(const glm::vec4& min, const glm::vec4& max);
  //! \brief
  //   generates vec3 with values ranging from min to max
  //  \param min
  //    min values
  //  \param max
  //    max values
  //  \return
  //    random vec3 with values ranging from min to max
  static glm::vec3 Range(const glm::vec3& min, const glm::vec3& max);

  static glm::vec2 Range(const glm::vec2& min, const glm::vec2& max);

private:
  static std::mt19937_64 rng; //!< random number generator, uses 64 bit Mersenne Twister engine
};
