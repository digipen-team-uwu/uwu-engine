#include <UWUEngine/Modules/SSBOMod.h>

using namespace UWUEngine;

SSBOMod::SSBOMod(ISpace* space) : System(space)
{
}

void SSBOMod::CreateShaderStorageBufferObject(Type type, unsigned size, unsigned location)
{
  GLuint ssbo;
  glCreateBuffers(1, &ssbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  glNamedBufferStorage(ssbo, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, location);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, location, ssbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  data_[type] = std::make_tuple(ssbo, location, size);
}

unsigned SSBOMod::GetShaderStorageBufferObjectBindingLocation(Type type)
{
  return std::get<1>(data_[type]);
}

unsigned SSBOMod::GetShaderStorageBufferObjectSize(Type type)
{
  return std::get<2>(data_[type]);
}

unsigned SSBOMod::GetShaderStorageBufferObjectID(Type type)
{
  return std::get<0>(data_[type]);
}

void SSBOMod::ShootDataToShaderStorageBufferObject(Type type)
{
  unsigned size = std::get<2>(data_[type]);
  unsigned loc = std::get<1>(data_[type]);
  unsigned ssboID = std::get<0>(data_[type]);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboID);
  if (type == PointLight)
  {
    for (int i = 0; i < size; ++i)
    {
      // TODO: Sending data to ssbo
      //glNamedBufferSubData(ssboID, 0, size, )
    }
  }
  else if (type == DirectionalLight)
  {
    // TODO: Sending data to ssbo
  }
  else if (type = SpotLight)
  {
    // TODO: Sending data to ssbo
  }
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, loc);
}
