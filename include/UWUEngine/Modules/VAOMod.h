#pragma once
#include <UWUEngine/System.h>
#include <GL/glew.h>

namespace UWUEngine
{
  class VAOMod : public System
  {
  public:
    VAOMod(ISpace* space);
    ~VAOMod() override;

  private:
    const std::tuple<GLenum, GLuint, GLuint>& vao_space_environment;
    const std::tuple<GLenum, GLuint, GLuint>& vao_space_ui;
    const std::tuple<GLenum, GLuint, GLuint>& vao_space_particle;
    const std::tuple<GLenum, GLuint, GLuint>& vao_space_gameplay;
    const std::tuple<GLenum, GLuint, GLuint>& vao_space_debug;
  };
}