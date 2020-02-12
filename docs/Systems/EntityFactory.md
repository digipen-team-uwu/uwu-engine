# Entity Factory

- [Creating an Entity](#creating-an-entity)

The EntityFactory is a system that provides functions which perform the work required
to create an entity in the engine and return the ID of the newly created entity.

There is only one include file required to use Enity Factory functions, which is EnityFactory.h
EntityFactory.h itself includes several .h files, including [EntitySys.h](./EnityManager.h) and rapidjson library headers.


## Creating an Entity
Since EntityFactory derives from BaseSystem, all of its non-update functions are static and can be called from any file that includes the header.
There are two methods of Entity creation through the Entity Factory, each performed using the same overloaded function CreateObject.
Each version of this function automatically adds the created entity to the Entity Manager.
One requires that the user pass in an EntityType such as Player, like so:
```cpp
EntityID id = EntityFactory::CreateObject(EntitySys::Player);
```
This function activates all components used by the type of object passed to the function as well.

The other requires a reference to a rapidjson object and the filepath the object originated from:
```cpp
EntityID id = EntityFactory::CreateObject(object, filePath);
```
This function will fail if the rapidjson object doesn't have a type member, and will activate all components used by the type referenced in the json object as well as any additional components referenced in the object.