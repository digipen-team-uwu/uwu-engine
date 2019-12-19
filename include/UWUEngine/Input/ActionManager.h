/******************************************************************************/
	/*!
	\par        Project Umbra
	\file       EntityManager.h
	\author     Brayan Lopez
	\date       2019/09/13
	\brief      Game Object Manager

	Copyright � 2019 DigiPen, All rights reserved.
	*/
	/******************************************************************************/

#pragma once

#include <UWUEngine/BaseSystem.h>
#include <UWUEngine/constants.h>
#include <vector>

namespace ic = InputConstants;

class ActionManager : public BaseSystem<ActionManager>
{
public:
  //todo: have controller inputs serialize/deserialize
  enum Action
  {
    Run    ,          //horizontal movement is being registered (left stick or dpad)
    Jump   ,          //jump button was pressed
    Select ,          //select button was pressed
    Dash   ,          //dash action was registered (moved right stick)
    Pause  ,          //pause button is pressed (not held)
    Move   ,          //movement is being registered (left stick or dpad)
    Back   ,          //back button is pressed
    Up     ,          //up input was registered (left stick or dpad)
    Down   ,          //down input was registered (left stick or dpad)
    Right  ,          //right input was registered (left stick or dpad)
    Left   ,          //left input was registered (left stick or dpad)
    Attack ,          //attack buttons pressed
    ActionAmount = 12 //total number of actions
  };
  ActionManager();
  static InputConstants::InputResult GetAction(Action action);
  static bool GetAction(Action action, const std::vector<ic::InputResult>& results);
  static bool GetActionPressed(Action action); //action was pressed?
  static bool GetActionHeld(Action action); //action was held?
  static bool GetActionReleased(Action action); //action was released?
  static bool GetInaction(Action action); //action has no state?
  static glm::vec2 GetDashVec(int controllerID = 0);
  static float GetDashAngle(int controllerID = 0);
  void Update() override;

private:
  static int actions[ActionAmount];
  static int prevActions[ActionAmount];

};
