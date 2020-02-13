#pragma once

namespace UWUEngine
{

// stupid hack class because GLFW callbacks only work with C functions
template <class SysType, typename MemberCallback, MemberCallback MemberCallbackFn, typename ReturnType, typename ...Args>
class CCallbackHelper
{
public:
	//CCallbackHelper<DragAndDropSys>(GLFWdropfun);

	CCallbackHelper(SysType* to_bind)
	{
		bound = to_bind;
	}

	static ReturnType CCallback(Args... args)
	{
		return (bound->*MemberCallbackFn)(args...);
	}

private:
	inline static SysType* bound{nullptr};
};

}