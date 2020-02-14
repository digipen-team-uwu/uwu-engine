#include <UWUEngine/EngineSettings.h>

using namespace UWUEngine;

#ifdef _Editor
bool EngineSettings::Editor = true;
bool EngineSettings::Lighting = false;
bool EngineSettings::DynamicCamera = false;

#else
bool EngineSettings::Editor = false;
bool EngineSettings::Lighting = true;
bool EngineSettings::DynamicCamera = true;

#endif
