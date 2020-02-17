/******************************************************************************/
/*!
\par        Project Umbra
\file       EntityViewer.h
\author     Yi Qian
\date       2019/12/28
\brief      Entity viewer

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <UWUEngine/Editors/Window.h>

using EntityID = unsigned int;

namespace UWUEngine
{
  namespace Editors
  {
    //Forward declaration
    class ComponentViewer;

    class EntityViewer final : public Window
    {
    public:
      EntityViewer(ISpace*);
      ~EntityViewer() override;

      static EntityID GetSelectedEntity();
      static ISpace* GetComponentSpace();

      static void SetSelectedEntity(EntityID ID);

    protected:
      void Setup() override;
      void Update() override;

    private:
      static EntityID selected;
      static ISpace* componentSpace;

      void UpdateEntity(EntityID id);
      void PopUpRightClick();

      void SpaceSelect() const;
    };
  }
}
