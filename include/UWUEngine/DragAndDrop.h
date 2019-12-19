/******************************************************************************/
	/*!
	\par        Project Umbra
	\file       DragAndDrop.h
	\author     Brayan Lopez
	\date       2019/11/15
	\brief      Drag and Drop class declaration

	Copyright � 2019 DigiPen, All rights reserved.
	*/
	/******************************************************************************/

#pragma once
#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/WindowManager.h>

//class Editor;
//class IBaseComponent;

//TODO: factory construction of different GameObjects (Maybe?)

//ladies and gentlemen: we got drag and drop!
//DragonDrop
class DragAndDrop : public BaseSystem<DragAndDrop>
{
public:
  DragAndDrop();
  static void DropCallback(GLFWwindow* window, int count, const char** paths);

};

//Christine was here uwu
// "I prefer Dragon Drop"
