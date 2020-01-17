/******************************************************************************/
/*!
\par        Project Umbra
\file       PlayerStartUp.cpp
\author     Yi Qian
\date       2019/12/05
\brief      Player startup behavior,I hate file header comments

Copyright 2019 DigiPen, All rights reserved.
*/
/******************************************************************************/

#include <UWUEngine/GamePlay/PlayerController.h>

// Don't implement
void PlayerStateMachine::Load_StartUp()
{
}

void PlayerStateMachine::Enter_StartUp()
{
	
}

void PlayerStateMachine::Update_StartUp(float dt)
{
	SetNextState(Grounded);
}

void PlayerStateMachine::Exit_StartUp()
{
	
}

// Don't implement
void PlayerStateMachine::Unload_StartUp()
{
}
