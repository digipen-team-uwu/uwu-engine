#include <UWUEngine/Modules/ShaderMod.h>
#include <UWUEngine/Systems/LogSys.h>

using namespace UWUEngine;

ShaderMod::ShaderMod(ISpace* space) : System(space),
  entity_program(CreateShader("./data/shaders/pass-thru-pos2d-clr.vert", "./data/shaders/basic-color.frag")),
  spine_program(CreateShader("./data/shaders/spineShader.vert", "./data/shaders/spineShader.frag")),
  hud_program(CreateShader("./data/shaders/HUD.vert", "./data/shaders/HUD.frag")),
  collider_program(CreateShader("./data/shaders/colliderShader.vert", "./data/shaders/colliderShader.frag"))
{
}

ShaderMod::~ShaderMod()
{
  entity_program.DeleteShaderProgram();
  spine_program.DeleteShaderProgram();
  hud_program.DeleteShaderProgram();
  collider_program.DeleteShaderProgram();
  //light_program.DeleteShaderProgram();
}

GLSLShader ShaderMod::CreateShader(const char* vertex_shader_filePath, const char* fragment_shader_filePath) const
{
  std::vector<std::pair<GLenum, std::string>> shdr_files;
  GLSLShader shdr_pgm{};
  shdr_files.emplace_back(std::make_pair(
    GL_VERTEX_SHADER,
    vertex_shader_filePath));

  shdr_files.emplace_back(std::make_pair(GL_FRAGMENT_SHADER,
    fragment_shader_filePath));

  shdr_pgm.CompileLinkValidate(shdr_files);

  if (GL_FALSE == shdr_pgm.IsLinked())
  {
    Get<LogSys>().Log(Get<LogSys>().FAILURE) << "Unable to compile/link/validate shader programs" <<
      std::endl;
    Get<LogSys>().Log(Get<LogSys>().FAILURE) << shdr_pgm.GetLog() << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return shdr_pgm;
}

GLSLShader ShaderMod::CreateComputeShader(char const* compute_shader_filePath) const
{
  std::vector<std::pair<GLenum, std::string>> files;
  GLSLShader compute_shader_program{};
  files.emplace_back(std::make_pair(GL_COMPUTE_SHADER, compute_shader_filePath));

  compute_shader_program.CompileLinkValidate(files);

  if (compute_shader_program.IsLinked() == GL_FALSE)
  {
    Get<LogSys>().Log(Get<LogSys>().FAILURE) << "Unable to compile/link/validate shader programs" <<
      std::endl;
    Get<LogSys>().Log(Get<LogSys>().FAILURE) << compute_shader_program.GetLog() << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return compute_shader_program;
}

const GLSLShader& UWUEngine::ShaderMod::GetEntityShader() const
{
  return entity_program;
}

const GLSLShader& UWUEngine::ShaderMod::GetSpineShader() const
{
  return spine_program;
}

const GLSLShader& UWUEngine::ShaderMod::GetHUDShader() const
{
  return hud_program;
}

const GLSLShader& UWUEngine::ShaderMod::GetColliderShader() const
{
  return collider_program;
}

