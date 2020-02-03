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
#include <UWUEngine/System.h>
#include <random>
#include <glm/glm.hpp>

namespace UWUEngine
{

class RandomSys : public System
{
public:
  //initialize Random module, with a given seed
  explicit RandomSys(ISpace*);
  void Update() override {}
  ~RandomSys() = default;

  //! \brief
  //    generates int between min and max INCLUSIVE
  //  \param min
  //    min value
  //  \param max
  //    max value
  //  \return
  //    random number between min and max
  int Range(int min, int max);

  //! \brief
  //   generates float between min and max INCLUSIVE
  //  \param min
  //    min value
  //  \param max
  //    max value
  //  \return
  //    random float between min and max
  float Range(float min, float max);

  //! \brief
  //   generates double between min and max INCLUSIVE
  //  \param min
  //    min value
  //  \param max
  //    max value
  //  \return
  //    random double between min and max
  double Range(double min, double max);

  //! \brief
  //   generates vec4 with values ranging from min to max
  //  \param min
  //    min values
  //  \param max
  //    max values
  //  \return
  //    random vec4 with values ranging from min to max
  glm::vec4 Range(const glm::vec4& min, const glm::vec4& max);
  //! \brief
  //   generates vec3 with values ranging from min to max
  //  \param min
  //    min values
  //  \param max
  //    max values
  //  \return
  //    random vec3 with values ranging from min to max
  glm::vec3 Range(const glm::vec3& min, const glm::vec3& max);

  glm::vec2 Range(const glm::vec2& min, const glm::vec2& max);

private:
  std::mt19937_64 rng{ std::random_device{}() }; //!< random number generator, uses 64 bit Mersenne Twister engine
};

} // namespace UWUEngine