#include <UWUEngine/GameStatesManager.h>

template<>
int RegisterStateHelper<GameStateMachine>::RegisterStateHelper_ID = StateMachineUpdater::AddMachine<GameStateMachine>();
