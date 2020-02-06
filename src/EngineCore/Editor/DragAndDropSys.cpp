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

#include <UWUEngine/Entity/EntityFactory.h>
#include <UWUEngine/Component/TextureComponentManager.h>
#include <UWUEngine/Input/InputSys.h>
#include <UWUEngine/Debugs/TraceLogger.h>
#include <UWUEngine/DragAndDropSys.h>
#include <UWUEngine/CCallbackHelper.h>
#include "UWUEngine/Graphics/Texture/AtlasModule.h"

#define DropTextures

namespace UWUEngine
{

DragAndDropSys::DragAndDropSys(ISpace* p) : System(p)
{
  DropCallbackHelper binder(this);
  glfwSetDropCallback(Get<WindowSys>().getWindowHandle(), DropCallbackHelper::CCallback);
}

void DragAndDropSys::DropCallback(GLFWwindow* window, int count, const char** paths)
{
  for (int i = 0; i < count; ++i)
  {
    const std::string path = paths[i];
    const bool jsonCheck = path.find(".json") != path.npos || path.find(".JSON") != path.npos;
    if (jsonCheck)
    {
      EntityFactory::CreateObject(path);
    }
    else
      TraceLogger::Log(TraceLogger::WARNING, "Dropped file is not a json/JSON file!!!\n");

  }


#ifdef DropTextures //I'll leave this here just in case we ever want this feature again
  //TODO::to be replaced by picker
//  GLint viewport[4]; //hold viewport info
//  GLdouble model2View[16]; //model to view coords
//  GLdouble projection[16]; //projection matrix
//  glm::vec<2, GLdouble> mousePos; //mouse position
  GLdouble worldX = 0.0; //world coord
  GLdouble worldY = 0.0; //world coord
  GLdouble worldZ = 0.0; //world coord
//
//  glGetDoublev(GL_MODELVIEW_MATRIX, model2View); //get modelview info
//  glGetDoublev(GL_PROJECTION_MATRIX, projection); //get projection matrix
//  glGetIntegerv(GL_VIEWPORT, viewport); //get viewport info
//
//  mousePos = InputManager::GetMousePos();
//  mousePos.y -= (float)viewport[3];

  //
  //gluUnProject(mousePos.x, mousePos.y, 100.f ,  model2View, projection, viewport, &worldX, &worldY, &worldZ);

  for (int i = 0; i < count; ++i)
  {
    TraceLogger::Log(TraceLogger::INFO, "Reading file: %s\n", paths[i]);
    std::string path(paths[i]);
    size_t const start = path.find("assets");
    if (start == std::string::npos) //if texture is not in assets folder
    {
      size_t nameStart;
      size_t nameEnd;
#ifdef _WIN64
      nameStart = path.find("Users\\") + std::string("Users\\").length();
      nameEnd = path.find('\\', nameStart);
#else
      nameStart = path.find("home/") + std::string("home/").length();
      nameEnd = path.find('/', nameStart);
#endif
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
      size_t pos;
#ifdef _WIN64
      pos = path.find('\\', j);
#else
      pos = path.find('/', j);
#endif
      if (pos != path.npos)
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
    TransformComponentManager::SetScale(glm::vec3(AtlasModule::GetBrayanTexture(paths[i]), 1.f), newEnt);
    TransformComponentManager::SetTranslation(glm::vec<4, double>(worldX, worldY, worldZ, 1.0), newEnt);
    TextureComponentManager::Activate(newEnt);
    TextureComponentManager::SetFilePath(newEnt, path.c_str());

  }
  AtlasModule::LoadAtlasPage(true);
#endif
}

}
