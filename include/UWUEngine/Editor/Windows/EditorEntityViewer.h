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
#include <unordered_map>

using EntityID = unsigned int;

class EditorEntityViewer final : public EditorWindow
{
public:
  EditorEntityViewer();
  ~EditorEntityViewer() override;
  void Setup() override;
  void Update() override;

  static EntityID GetSelectedEntity();

  static void SetName(EntityID ID, std::string name);
  static bool HasName(EntityID ID);
  static std::string GetName(EntityID ID);

private:
  static void UpdateEntity(EntityID id);
  static EntityID selected;
  static std::unordered_map<EntityID, std::string> name;
};
