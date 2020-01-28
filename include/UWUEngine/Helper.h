#pragma once
#include <type_traits>
#include <string>
#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Random.h>
#include <fstream>

#define EXPAND(x) x

namespace non_std
{
  static std::ofstream cnull{};
}

std::string str_toupper(std::string const& str);
std::string str_tolower(std::string const& str);

template < typename C, C beginVal, C endVal>
class Iterator {
    typedef typename std::underlying_type<C>::type val_t;
    int val;
public:
    Iterator(const C& f) : val(static_cast<val_t>(f)) {}
    Iterator() : val(static_cast<val_t>(beginVal)) {}
    Iterator operator++() {
        ++val;
        return *this;
    }
    C operator*() { return static_cast<C>(val); }
    Iterator begin() { return *this; } //default ctor is good
    Iterator end() {
        static const Iterator endIter = ++Iterator(endVal); // cache it
        return endIter;
    }
    bool operator!=(const Iterator& i) { return val != i.val; }
};

typedef Iterator<EntityManager::Type, EntityManager::Type::Empty, EntityManager::Type::End> EntityManagerTypeIterator;


template <typename Iter, typename Cont>
bool is_last(Iter iter, const Cont& cont)
{
    return (iter != cont.end()) && (next(iter) == cont.end());
}

inline glm::mat4 perspective_invZ(float fovY_radians, float aspectWbyH, float zNear)
{
	float f = 1.0f / tan(fovY_radians / 2.0f);
	return glm::mat4(
		f / aspectWbyH, 0.0f, 0.0f, 0.0f,
		0.0f, f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, zNear, 0.0f);
}

float intpow(float number, int exponent);



class Polynomial
{
public:
  enum PolynomialSpecials
  {
    NONE, SIN, COS, LN
  };
  Polynomial() = default;

  Polynomial(int exponent, float coefficient, char variable, PolynomialSpecials special = NONE, float specialCoeff = 1) : exponent(exponent), coefficient(coefficient), variable(variable), next(0), special(special), specialCoeff(specialCoeff){}
  void AddPolynomial(int exponent, float coefficient, char variable, PolynomialSpecials special = NONE, float specialCoeff = 1)
  {
    Polynomial** last = &next;
    while (*last)
    {
      last = &((*last)->next);
    }
    *last = new Polynomial(exponent, coefficient, variable, special);
  }
  float Evaluate(glm::vec2 pos)
  {
    float curr = 0;
    switch (variable)
    {
    case 'x':
      curr = pos.x;
      break;
    case 'y':
      curr = pos.y;
      break;
    }
    curr *= specialCoeff;
    switch (special)
    {
    case SIN:
      curr = sin(curr);
      break;
    case COS:
      curr = cos(curr);
      break;
    case LN:
      curr = log(curr);
      break;
    }
    return intpow(curr, exponent) * coefficient + ((next != NULL) ? next->Evaluate(pos) : 0);
  }
  ~Polynomial()
  {
    delete next;
  }
private:
  char variable;
  int exponent;
  float coefficient;
  PolynomialSpecials special;
  float specialCoeff;
  Polynomial* next;
};

template<typename T>
class FlatOrRange
{
public:
  FlatOrRange(T min, T max) : min(min), max(max), ranged(true) {}
  FlatOrRange(T flat) : flat(flat), ranged(false) {}
  FlatOrRange() = default;

  void SetFlat(T flat_) { flat = flat_; ranged = false; }
  void SetRange(T min_, T max_) { min = min_; max = max_; ranged = true; }
  
  void SetToRads()
  {
    if (ranged)
    {
      min = glm::radians(min);
      max = glm::radians(max);
    }
    else
    {
      flat = glm::radians(flat);
    }
  }

  T Get()
  {
    if (ranged)
      return Random::Range(min, max);
    return flat;
  }

private:
  T flat;
  T min;
  T max;
  bool ranged;
};

inline float RotationFromVec(const glm::vec4& vec)
{
  return atan2f(vec.y, vec.x);
}

inline glm::vec4 VectorFromAngle(float angle)
{
  return glm::vec4(glm::cos(angle), glm::sin(angle), 0, 0);
}

inline glm::vec4 VectorFromTwoAngles(float angle1, float angle2)
{
  return glm::vec4(sin(angle1)*cos(angle2), sin(angle1)*sin(angle2), cos(angle1), 0);
}

inline glm::vec4 VectorFromTwoAngles(glm::vec2 angles)
{
  return glm::vec4(sin(angles.x) * cos(angles.y), sin(angles.x) * sin(angles.y), cos(angles.x), 0);
}
// APU APUSTAJA ("Help Helper")
#define apu "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/.    ....      ,&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&  .&@@@@@@@@@@@@@@@@@@,  #@@@@@@@@@@@#.                  ./&@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@@@@@@&  #@@@@@@@@@@@@@@@@@@@@@@@@@( .@@@@,  .&@@@@@@@@@@@@@@@@@@@@@@@(   ,@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@@@@( ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&   #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@(  @@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@@@, @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@# (@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/ @@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@@. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@, &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ .@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@@ &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@, @@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@&///.  ../@@@@@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@&/.    ...            ../&&&&@  @@@/            ......./&@@@@@@@@@@@@&  ,@@@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@/ @@@@@@@@#   /&@@@@@@@@@@@@@@@@@@@@@@@@@@@&/   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  (@@@@@@@@ \n\
@@@@@@@@@@@@@@@@@@@@@  (@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@ \n\
@@@@@@@@@@@@@@@@@@    &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@& ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@, @@@@@@ \n\
@@@@@@@@@@@@@@@( ,@@. @@@@@@@@@@@@@@@@@&.  .&@@@@@@@@@//        .(@@@, &@@@@@@@@@@@@@@@@@@#.                     (@@@   \n\
@@@@@@@@@@@@@@  @@@# @@@@@@@@@...    .#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&,     @@@@@@@@@/     /&@@@@@@@@@@@@@@@@@@@@@@@ &@@ \n\
@@@@@@@@@@@@( &@@@@.&@@@@@@@@@@@@, ,@@@@@@@@@@@@@@@@@&/          /@@@@@@@& &@@@/  .&@@@@@@@&.       ../////////,    &@@ \n\
@@@@@@@@@@@# @@@@@@@@@@@@@@@@@@@@@@& ,@@@@@@@@@@@@                 ,@@@@@@     @@@@@&/    &@@@@@@@@@#     .#@@@@@@@  @@ \n\
@@@@@@@@@@( @@@@@@@@@@@@@@@@@@@@@@@@@(  @@@@@@@@&      &@           /@@@@@ ,@@&////(@@@@@@@@@@@@@/           @@@@@@@ &@ \n\
@@@@@@@@@@ &@@@@@@@@@@@@@@@@@@@@@@@@@@@@#  ,@@@@&                    @@@@, @@@@@@@@@@@@@@@@@@@@@              @@@@@@ &@ \n\
@@@@@@@@@ ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&   /               /    @@   @@@@@@@@@@@@@@@@@@@@&               .@@@@ .@@ \n\
@@@@@@@@. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/                        (@@@@@@@@@@@@@@@@@@@           &@    @&   @@@ \n\
@@@@@@@@ #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&(@@#  @@,   @@@@@@@@@@@@@                    #&  @@@ \n\
@@@@@@@ /@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&(.  (@@@@@@@@&.     ......             .,&@@@# /@@@@@ \n\
@@@@@@# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&/.              .///&@@@@/  &@@@@@@@@@@@@@@@@@@@@/ @@@@@@@@@@@/    &@@@@@@@ \n\
@@@@@@ .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@(  .#@@@@@@@@@@@@@@@@@@@@@@@@@@,      .,#&@@# .@@@@@@@@ \n\
@@@@@& @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#..&@@@@@@@@@@@@@@@#.                            #& &@@@@@@ \n\
@@@@@ .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&@@@@@@@@@@@@@@@@@&,    #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@& &@@@@@@ \n\
@@@@@ &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&  ,@@@@@@@&/////////////(&@@@/    ,&&@@@@@&.    ....///////&@@#,  &@@@@@@@ \n\
@@@@@ &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ &@@@@@@@@@@@@@@@@@@@@@@&.   /@@@@@@@@@#//////&&&&@@@@@@@@@ .@@@@@@@@@@@@@@ \n\
@@@@@ &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@& @@@@@@@@@@&&&&&&//.   .&@@@@@@@/    ,&@@@@@@@@@@@@&       &@@@@@@@@@@@@@@@ \n\
@@@@@ /@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@& @@@@@@@@@@@@@@@@@@@@@@@@(,   .&@@@@@@@@@@@@@@@@@@@. @@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@. @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  &@@@@@@@@@@@@@@#/.    #@@@@@@@@@@@@@@@@@@@@@@@@@ /@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,.....,///&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@   \n\
@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#  @@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@( &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,  &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@(     &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@@@( .@, #    .&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.   (&  /@@.  /@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@@, @@@@@#  @@@@@/.      /&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&/    ,&@@@, ,@@@@@@@@&  @@@@@@@@@@@@@@@@@@@@@@@@@ \n\
@@@. @@@@@@@@@/  /@@@@@@@@@@@#.                                    /&@@@@@@@@/  @@@@@@@@@@@@@@  (@@@@@@@@@@@@@@@@@@@@@@ \n\
@@, @@@@@@@@@@@@@(.   .&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#   /@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@ \n\
@@ (@@@@@@@@@@@@@@@@@@@@(     ./#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&,    /@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@ \n\
@/ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&/.      ........  .....       ,&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@ \n\
@ /@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@ \n\
& &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ (@@@@@@@@@@@@@@@@@ \n\
& @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@( @@@@@@@@@@@@@@@@@ \n\
& @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@& @@@@@@@@@@@@@@@@@ \n\
& @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@ \n\
& @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@& @@@@@@@@@@@@@@@@@ "
