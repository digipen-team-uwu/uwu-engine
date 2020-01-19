#include <UWUEngine/statemachine.hpp>
#include <UWUEngine/FrameRateController.h>

void StateMachineUpdater::StartUp()
{
	for (auto& machine : GetMachines())
	{
		machine->Load();
		machine->Enter();
	}
}

void StateMachineUpdater::Update()
{
	const auto dt = FrameRateController::GetDeltaTime<float>();
	for (auto& machine : GetMachines())
	{
		machine->UpdateState(dt);
	}
}

unsigned GetNextId() noexcept
{
	static unsigned nextID = 0;
	return ++nextID;
}