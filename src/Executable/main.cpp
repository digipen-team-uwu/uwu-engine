#undef main
#define GLM_FORCE_SWIZZLE
#include <UWUEngine/Engine.h>

int main(int argc, char* argv[]) 
{   
  UWUEngine::Engine engine;
  engine.Run();
	return 0;
}