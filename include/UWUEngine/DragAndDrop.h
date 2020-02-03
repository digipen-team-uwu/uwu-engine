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
#include <UWUEngine/System.h>
#include <UWUEngine/WindowSys.h>

//class Editor;
//class IBaseComponent;

namespace UWUEngine
{

//TODO: factory construction of different GameObjects (Maybe?)

//ladies and gentlemen: we got drag and drop!
//DragonDrop
class DragAndDropSys : public System
{
public:
	DragAndDropSys(ISpace*);
	void DropCallback(GLFWwindow* window, int count, const char** paths);

	// stupid hack class because GLFW callbacks only work with C functions
	class DragAndDropCallbackHelper
	{
	public:
		DragAndDropCallbackHelper(DragAndDropSys* bound);
		static void CDropCallback(GLFWwindow* window, int count, const char** paths);
		static DragAndDropSys* bound;
	};

	DragAndDropCallbackHelper ch;
};

}

//Christine was here uwu
// "I prefer Dragon Drop"
