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
#include <UWUEngine/CCallbackHelper.h>

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

private:
	using DropCallbackFn = void (DragAndDropSys::*)(GLFWwindow* window, int count, const char** paths);
	using DropCallbackHelper = CCallbackHelper<DragAndDropSys, DropCallbackFn, DropCallback, void, GLFWwindow*, int, const char**>;
};

}

//Christine was here uwu
// "I prefer Dragon Drop"
