#include <UWUEngine/constants.h>
#include <UWUEngine/Entity/EntityVector.h>
size_t EntityVectorManager::vectorSize = GameObjectConstants::INITIAL_OBJECT_COUNT;

template<>
int RegisterSystemHelper<EntityVectorManager>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<EntityVectorManager>(SystemInitOrder::EntityVec, SystemUpdateOrder::EntityVec);