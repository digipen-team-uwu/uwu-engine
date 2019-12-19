#pragma once
#include <string>
#include <glm/vec3.hpp>

namespace ColoredOutput
{
  typedef glm::vec3 ColorRGB;
  enum Color
  {
    Black = 30,
    Crimson,
    Green,
    Olive,
    Navy,
    Purple,
    Aqua,
    Default,
    Gray = 90,
    Red,
    Lime,
    Yellow,
    Blue,
    Pink,
    Cyan,
    White,

    Reset = 0,
  };

  enum Style
  {
    Bold = 1,
    Underlined,
    Inverted,

    Normal = 0,
    NoChange = -1,
  };

  std::string Set(Color foreground = Reset, Color background = Reset, Style decoration = Normal);
  std::string Set(ColorRGB const&& foreground, ColorRGB const&& background = {-1, -1, -1}, Style decoration = NoChange);
  std::string Strip(std::string&);
  std::string Strip(std::string const &);
  std::string Strip(char const*);

  bool GetSetColorEnabled(bool get, bool set);
}
