#include <sstream>
#include <regex>
#include <iostream>
#include <UWUEngine/Debugs/ColoredOutput.h>

namespace
{
  constexpr int BG_offset = 10;
  const std::regex color_code("\\x1b[[0-9;]*m");
}

std::string ColoredOutput::Strip(std::string& text)
{
  if (!GetSetColorEnabled(true, false))
  {
    return text;
  }
  return text = Strip(text.c_str());
}

std::string ColoredOutput::Strip(std::string const& text)
{
  if (!GetSetColorEnabled(true, false))
  {
    return text;
  }
  return Strip(text.c_str());
}

std::string ColoredOutput::Strip(char const* text)
{
  if (!GetSetColorEnabled(true, false))
  {
    return text;
  }
  std::stringstream result;
  std::regex_replace(std::ostream_iterator<char>(result), text, text + std::strlen(text), color_code, "");
  return result.str();
}

bool ColoredOutput::GetSetColorEnabled(bool get, bool set)
{
  static bool color_enabled = false;
  if (!get)
  {
    color_enabled = set;
  }
  return color_enabled;
}

std::string ColoredOutput::Set(Color foreground, Color background, Style decoration)
{
  if (!GetSetColorEnabled(true, false))
  {
    return "";
  }

  std::stringstream esc_seq;
  esc_seq << "\033[";

  int print_count = (foreground != Reset) + (background != Reset) + (decoration != Normal);

  if (print_count < 3)
  {
    esc_seq << "0;";
  }

  if (foreground != Reset)
  {
    esc_seq << foreground;
    if (--print_count != 0)
    {
      esc_seq << ";";
    }
  }

  if (background != Reset)
  {
    esc_seq << background + BG_offset;
    if (--print_count != 0)
    {
      esc_seq << ";";
    }
  }

  if (decoration != Normal)
  {
    esc_seq << decoration;
    if (--print_count != 0)
    {
      esc_seq << ";";
    }
  }

  esc_seq << "m";
  return esc_seq.str();
}

std::string ColoredOutput::Set(ColorRGB const&& foreground, ColorRGB const&& background, Style decoration)
{
  if (!GetSetColorEnabled(true, false))
  {
    return "";
  }

  glm::vec<3, uint8_t> integer_foreground{};
  glm::vec<3, uint8_t> integer_background{};

  glm::vec3 const invalid = { -1, -1, -1 };

  int print_count = 3 + (3 * (background != invalid)) + (decoration != NoChange);

  integer_foreground.r = static_cast<uint8_t>(foreground.r * 255);
  integer_foreground.g = static_cast<uint8_t>(foreground.g * 255);
  integer_foreground.b = static_cast<uint8_t>(foreground.b * 255);

  if (background != invalid)
  {
    integer_background.r = static_cast<uint8_t>(background.r * 255);
    integer_background.g = static_cast<uint8_t>(background.g * 255);
    integer_background.b = static_cast<uint8_t>(background.b * 255);
  }

  std::stringstream esc_seq;

  esc_seq << "\033[";

  if (decoration != NoChange)
  {
    esc_seq << decoration;
    if (--print_count)
    {
      esc_seq << ";";
    }
  }

  /* Escape code for 24-bit RGB (true color) output in the foreground. */
  esc_seq << "38;2;";

  esc_seq << int{ integer_foreground.r } << ";";
  esc_seq << int{ integer_foreground.g } << ";";
  esc_seq << int{ integer_foreground.b };

  if (print_count -= 3)
  {
    esc_seq << ";";
  }

  if (background != invalid)
  {
    /* Escape code for 24-bit RGB (true color) output in the background. */
    esc_seq << "48;2;";

    esc_seq << int{ integer_background.r } << ";";
    esc_seq << int{ integer_background.g } << ";";
    esc_seq << int{ integer_background.b };
    if (print_count -= 3)
    {
      esc_seq << ";";
    }
  }

  esc_seq << "m";

  return esc_seq.str();
}
