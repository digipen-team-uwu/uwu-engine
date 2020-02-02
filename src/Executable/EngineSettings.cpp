#include <UWUEngine/EngineSettings.h>

#ifdef _Editor
bool EngineSettings::Lighting = false;
bool EngineSettings::DynamicCamera = false;

#else
bool EngineSettings::Lighting = true;
bool EngineSettings::DynamicCamera = true;

#endif
