#undef main
#define GLM_FORCE_SWIZZLE
#include <UWUEngine/Engine.h>
#include <UWUEngine/WindowManager.h>

int main(int argc, char* argv[]) 
{   
    Engine::StartUp();

    //init hints to GLFW
    //glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_TRUE);

    while (glfwWindowShouldClose(WindowManager::getWindowHandle()) == false)
    {
        glfwPollEvents();
        Engine::Update();
    }

    // free frame rate controller
    Engine::ShutDown();
	return 0;
}