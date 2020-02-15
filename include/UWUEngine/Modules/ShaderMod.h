#pragma once
#include <UWUEngine/System.h>
#include <UWUEngine/Graphics/GLSLShader.h>

namespace  UWUEngine
{
  class ShaderMod : public System
  {
  public:
    ShaderMod(ISpace* space);
    ~ShaderMod() override;

    GLSLShader CreateShader(const char* vertex_shader_filePath,
      const char* fragment_shader_filePath) const;
    GLSLShader CreateComputeShader(char const* compute_shader_filePath) const;

    const GLSLShader& GetEntityShader() const;
    const GLSLShader& GetSpineShader() const;
    const GLSLShader& GetHUDShader() const;
    const GLSLShader& GetColliderShader() const;

  private:
    GLSLShader& entity_program;
    GLSLShader& spine_program;
    GLSLShader& hud_program;
    GLSLShader& collider_program;
    // TODO: Re-add light shader
    //GLSLShader light_program;
  };
}