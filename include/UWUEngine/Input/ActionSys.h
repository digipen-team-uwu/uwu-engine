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

#include <UWUEngine/System.h>
#include <UWUEngine/constants.h>
#include <vector>
#include <array>

namespace ic = InputConstants;

namespace UWUEngine
{

class ActionSys : public System
{
public:
  //todo: have controller inputs serialize/deserialize
  enum Action
  {
    Run,          //horizontal movement is being registered (left stick or dpad)
    Jump,          //jump button was pressed
    Select,          //select button was pressed
    Dash,          //dash action was registered (moved right stick)
    Pause,          //pause button is pressed (not held)
    Move,          //movement is being registered (left stick or dpad)
    Back,          //back button is pressed
    Up,          //up input was registered (left stick or dpad)
    Down,          //down input was registered (left stick or dpad)
    Right,          //right input was registered (left stick or dpad)
    Left,          //left input was registered (left stick or dpad)
    Attack,          //attack buttons pressed
    ActionAmount    //total number of actions
  };
  ActionSys(ISpace*);
  InputConstants::InputResult GetAction(Action action) const;
  bool GetAction(Action action, const std::vector<ic::InputResult>& results) const;
  bool GetActionPressed(Action action) const; //action was pressed?
  bool GetActionHeld(Action action) const; //action was held?
  bool GetActionReleased(Action action) const; //action was released?
  bool GetInaction(Action action) const; //action has no state?
  glm::vec2 GetDashVec(int controllerID = 0) const;
  float GetDashAngle(int controllerID = 0) const;
  void Update() override;

private:
  std::array<int, ActionAmount> actions;
  std::array<int, ActionAmount> prevActions;

};

} // namespace UWUEngine
