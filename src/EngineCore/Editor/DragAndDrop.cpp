/******************************************************************************/
/*!
\par        Project Umbra
\file       DragAndDrop.cpp
\author     Brayan Lopez
\date       2019/11/15
\brief      Drag and Drop implementation

Copyright � 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Component/TransformComponentManager.h>

#include <UWUEngine/Entity/EntityManager.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Engine.h>
#include <UWUEngine/Input/InputManager.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/DragAndDrop.h>
#include "UWUEngine/Graphics/Texture/TextureAtlaser.h"

template<>
int RegisterSystemHelper<DragAndDrop>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<DragAndDrop>(SystemInitOrder::LAST, SystemUpdateOrder::LAST);

DragAndDrop::DragAndDrop()
{
  glfwSetDropCallback(WindowManager::getWindowHandle(), DropCallback);
}

void DragAndDrop::DropCallback(GLFWwindow* window, int count, const char** paths)
{
  GLint viewport[4]; //hold viewport info
  GLdouble model2View[16]; //model to view coords
  GLdouble projection[16]; //projection matrix
  glm::vec<2, GLdouble> mousePos; //mouse position
  GLdouble worldX = 0.0; //world coord
  GLdouble worldY = 0.0; //world coord
  GLdouble worldZ = 0.0; //world coord

  glGetDoublev(GL_MODELVIEW_MATRIX, model2View); //get modelview info
  glGetDoublev(GL_PROJECTION_MATRIX, projection); //get projection matrix
  glGetIntegerv(GL_VIEWPORT, viewport); //get viewport info

  mousePos = InputManager::GetMousePos();
  mousePos.y -= (float)viewport[3];

  //TODO::Put this back with glm::unProject
  //gluUnProject(mousePos.x, mousePos.y, 100.f ,  model2View, projection, viewport, &worldX, &worldY, &worldZ);

  for(int i = 0; i < count; ++i)
  {
    TraceLogger::Log(TraceLogger::INFO, "Reading file: %s\n", paths[i]);
    std::string path(paths[i]);
    size_t const start = path.find("assets");
    if(start == path.npos)
    {
      size_t const nameStart = path.find("Users\\") + std::string("Users\\").length();
      size_t const nameEnd = path.find('\\', nameStart);
      path = path.substr(nameStart, nameEnd - nameStart);
      path.insert(0, "I'm not loading this, please make sure this asset is in the asset folder before dropping into uwuENGINE ");
      path.append("!!!\n");
      TraceLogger::Log(TraceLogger::WARNING, path.c_str());
      continue;
    }
    path = path.substr(start - 2);
    path[0] = '.';
    path[1] = '/';
    TraceLogger::Log(TraceLogger::INFO, "In progress path: %s\n", path.c_str());
    for (int j = 0; j < path.length();)
    {
      size_t pos = path.find('\\', j);
      if(pos != path.npos)
      {
        j = pos;
        path.replace(pos, 1, "/");
      }
      else
      {
        break;
      }
    }
    TraceLogger::Log(TraceLogger::INFO, "Finished modifying path: %s\n", path.c_str());

    EntityID newEnt = EntityManager::New(EntityManager::Type::Dropped);
    TransformComponentManager::Activate(newEnt);
    TransformComponentManager::SetScale(glm::vec3(TextureAtlaser::GetBrayanTexture(paths[i]), 1.f), newEnt);
    TransformComponentManager::SetTranslation(glm::vec<4, double>(worldX, worldY, worldZ, 1.0), newEnt);
    TextureComponentManager::Activate(newEnt);
    TextureComponentManager::SetFilePath(newEnt, path.c_str());
    
  }
  TextureAtlaser::LoadAtlasPage(true);
}
