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
#include<UWUEngine/Helper.h>
#include <string>
#include <utility>

namespace Editors
{
  using EntityID = unsigned;

  template<typename T>
  class Element
  {
  public:
    Element(std::string label, T* element = nullptr):
    label(std::move(label)), element(element)
    {}

    void UpdateUI();
    void UpdateElement(T* newElement);

  private:
    bool range;
    std::string label;
    T* element;
  };


  template<typename T>
  class Element<FlatOrRange<T>>
  {
  public:
    Element(std::string label, FlatOrRange<T>* element = nullptr) :
      label(std::move(label)), element(element)
    {}

    void UpdateElement(FlatOrRange<T>* newElement)
    {
      element = newElement;
    }

    void UpdateUI()
    {
      ImGui::Checkbox(label.c_str(), &range);
      element->SetToRanged(range);
      if (range)
      {
        Element<T>{"Min", & (element->Min())}.UpdateUI();
        Element<T>{"Max", & (element->Max())}.UpdateUI();
      }
      else
      {
        Element<T>{label, & (element->Flat())}.UpdateUI();
      }
    }

  private:
    std::string label;
    FlatOrRange<T>* element;
    bool range;
  };

  class Component
  {
  public:
    Component(std::string name):
    name(std::move(name))
    {}
    virtual ~Component() = default;

    const std::string& GetName() const;
    void Render();
    void UpdateID(EntityID id);
    bool IsActive() const;

  protected:
    virtual void CheckActive(EntityID id) = 0;
    virtual void UpdateComponent(EntityID id) = 0;
    virtual void UpdateUI() = 0;

    bool isActive{ false };

  private:
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
