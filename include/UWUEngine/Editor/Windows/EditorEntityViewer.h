/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorEntityViewer.h
\author     Yi Qian
\date       2019/12/28
\brief      Entity viewer

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editor/EditorWindow.h>
#include <unordered_map>

using EntityID = unsigned int;

namespace Editors
{
  //Forward declaration
  class ComponentViewer;

  class EntityViewer final : public Window
  {
  public:
    EntityViewer();
    ~EntityViewer() override;

    static EntityID GetSelectedEntity();

    //TODO::Entity names should not be managed by editor
    static void SetName(EntityID ID, std::string name);
    static bool HasName(EntityID ID);
    static std::string GetName(EntityID ID);
    static void RemoveName(EntityID ID);
    static void RemoveAllNames();

  protected:
    void Setup() override;
    void Update() override;

  private:
    static void UpdateEntity(EntityID id);
    static void PopUpRightClick();
    static EntityID selected;
    static std::unordered_map<EntityID, std::string> name;

    friend ComponentViewer;
  };
}