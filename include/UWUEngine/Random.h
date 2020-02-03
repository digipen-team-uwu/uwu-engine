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

    enum RNG
    {
        Uniform,
        Normal,
        RNGCount
    };

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
  static int Range(int min, int max, RNG distro = Uniform);

  //! \brief
  //   generates float between min and max INCLUSIVE
  //  \param min
  //    min value
  //  \param max
  //    max value 
  //  \return
  //    random number between min and max 
  static float Range(float min, float max, RNG distro = Uniform);

  //! \brief
  //   generates double between min and max INCLUSIVE
  //  \param min
  //    random number between min and max 
  //  \param max
  //    random number between min and max 
  //  \return
  //    random number between min and max
  static double Range(double min, double max, RNG distro = Uniform);

  //! \brief
  //   generates vec4 with values ranging from min to max
  //  \param min
  //    min values
  //  \param max
  //    max values
  //  \return
  //    random vec4 with values ranging from min to max
  static glm::vec4 Random::Range(glm::vec4 min, glm::vec4 max, RNG distro = Uniform);

  //! \brief
  //   generates vec3 with values ranging from min to max
  //  \param min
  //    min values
  //  \param max
  //    max values
  //  \return
  //    random vec3 with values ranging from min to max
  static glm::vec3 Random::Range(glm::vec3 min, glm::vec3 max, RNG distro = Uniform);

  static glm::vec2 Random::Range(glm::vec2 min, glm::vec2 max, RNG distro = Uniform);

private:
  static std::mt19937_64 rng; //!< random number generator, uses 64 bit Mersenne Twister engine

  /*!
    \brief
        helper function to prevent RNG from throwing by forcing min < max
    \param min
        "min" values
    \param max
        "max" values
  */
  template <typename T>
  static void FixRange(T& min, T& max) //for non glm vectors
  {
      if (min > max)
      {
          T temp = max;
          max = min;
          min = temp;
      }
  }

  template <>
  static void FixRange<glm::vec4>(glm::vec4& min, glm::vec4& max) //specialization for glm vec4
  {
      if (min.x < max.x)
      {
          auto temp = max.x;
          max.x = min.x;
          min.x = temp;
      }
      if (min.y < max.y)
      {
          auto temp = max.y;
          max.y = min.y;
          min.y = temp;
      }
      if (min.z < max.z)
      {
          auto temp = max.z;
          max.z = min.z;
          min.z = temp;
      }
      if (min.w < max.w)
      {
          auto temp = max.w;
          max.w = min.w;
          min.w = temp;
      }
  }
  template <>
  static void FixRange<glm::vec3>(glm::vec3& min, glm::vec3& max) //specialization for glm vec3
  {
      if (min.x < max.x)
      {
          auto temp = max.x;
          max.x = min.x;
          min.x = temp;
      }
      if (min.y < max.y)
      {
          auto temp = max.y;
          max.y = min.y;
          min.y = temp;
      }
      if (min.z < max.z)
      {
          auto temp = max.z;
          max.z = min.z;
          min.z = temp;
      }
  }
  template <>
  static void FixRange<glm::vec2>(glm::vec2& min, glm::vec2& max) //specialization for glm vec2
  {
      if (min.x < max.x)
      {
          auto temp = max.x;
          max.x = min.x;
          min.x = temp;
      }
      if (min.y < max.y)
      {
          auto temp = max.y;
          max.y = min.y;
          min.y = temp;
      }
  }
};
