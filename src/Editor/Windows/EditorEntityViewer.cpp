/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorEntityViewer.cpp
\author     Yi Qian
\date       2019/12/28
\brief      Entity viewer window

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/Editor/Windows/EditorEntityViewer.h>
#include <imgui.h>
#include <UWUEngine/Debugs/TraceLogger.h>

EditorEntityViewer::EditorEntityViewer():
EditorWindow("EntityViewer")
{
}

EditorEntityViewer::~EditorEntityViewer() = default;

void EditorEntityViewer::Setup()
{
}

void EditorEntityViewer::Update()
{
  if (ImGui::Button("This is a random button"))
  {
    TraceLogger::Log(TraceLogger::DEBUG) << "You pressed the random button??!!" << std::endl;
  }
}
