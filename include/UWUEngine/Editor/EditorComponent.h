/******************************************************************************/
/*!
\par        Project Umbra
\file       EditorComponent.h
\author     Yi Qian
\date       2019/12/29
\brief      Component viewer

Copyright © 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/
#pragma once

#include <string>
#include <utility>

namespace Editors
{
  using EntityID = unsigned;

  template<typename T>
  class Element
  {
  public:
    Element(std::string label, T* element):
    label(std::move(label)), element(element)
    {}

    void UpdateUI();
    void UpdateElement(T* newElement);

  private:
    std::string label;
    T* element;
  };

  class Component
  {
  public:
    Component(std::string name):
    name(std::move(name))
    {}
    virtual ~Component() = default;

    const std::string& GetName() const;
    void Render(EntityID id);

  protected:
    virtual bool IsActive(EntityID id) = 0;
    virtual void UpdateID(EntityID id) = 0;
    virtual void UpdateUI() = 0;

  private:
    bool isActive{false};
    EntityID current{0};
    std::string name;
  };

  //Inline Implementation
  template <typename T>
  void Element<T>::UpdateElement(T* newElement)
  {
    element = newElement;
  }

}
