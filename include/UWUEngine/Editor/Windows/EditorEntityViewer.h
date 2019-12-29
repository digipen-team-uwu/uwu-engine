/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorEntityViewer.h
\author     Yi Qian
\date       2019/12/28
\brief      Editor window

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editor/EditorWindow.h>

class EditorEntityViewer final : public EditorWindow
{
public:
  EditorEntityViewer();
  ~EditorEntityViewer() override;
  void Setup() override;
  void Update() override;
};
