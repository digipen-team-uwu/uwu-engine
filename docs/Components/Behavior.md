# Behavior
The Behavior component in [UWU Engine](../../README.md) allows you to give any entity type-specific data and functionality. Any type can have its own specializization of a behavior, and specific polymorphic functions will be called automatically for any object with an instantiated specialized behavior.

To use this component, `#include "BehaviorComponentManager.h"`

## Usage
 Behaviors should be used to give any entity-type functionality not covered by any other component. For example, a text entity-type needs a string stream to store the text it needs to render, a custom update function that gets called automatically by the engine that creates character entities for each character, and a function to set the text.

 ## Create a behavior
 To create a behavior, specialize a Behavior class by the type of the entity you want to make a behavior for, and it inherit the base behavior. Here is how you would create a behavior for a text object:

```cpp
template<>
class Behavior<EntitySys::Type::Text> : public BaseBehavior
{
};
```

Then, in order for the manager to be able to create your behavior, you must add the prototype for the constructor specialization for your object to the allBehaviors map, declared in
`BehaviorComponentManager.h`
For example, for a text object to be able to use your text behavior, allBehaviors should look like this:

```cpp
const std::map<EntitySys::Type, BaseBehavior * (* const)()> allBehaviors =
{ 
    { EntitySys::Type::Text_, CreateBehavior<EntitySys::Type::Text_> }
}
```
Finally, in order for the manager to find your constructor, include the location of its declaration to the bottom of `BehaviorComponentManager.h`

## Core behavior functionality
The most useful methods any behavior specialization can define include:

* An update function that gets called for each existing entity every frame by the engine:
```cpp
virtual void Update();
```

* An render function that gets called by the renderer for objects that need to render in a special way:
```cpp
virtual void Render();
```

* An deserialize function that gets called by the entity factory to deserialize a behavior's entity-specific data from a json file:
```cpp
virtual void Deserialize(rapidjson::Value& object, EntityID ID, const char* filePath);
```
* In order to get the ID of the entity that contains your behavior (so you can change its data in any behavior metod), call the base behavior's GetID() function like so:
```cpp
void Behavior<EntitySys::Type::Text> Update()
{
    EntityID currentID = GetID();
}
```
## Access your behavior
First, in order to give the entity that your behavior was specialized for your behavior, you must activate it. For example, tp create an object of type text and give it your specialized behavior component, do this:

```cpp
EntityID text = EntitySys::New(EntitySys::Type::Text);
BehaviorComponentManager::Activate(text);
```

Now, to call any of the functions defined by the base behavior, such as the Update or Deserialize methods, access the BaseBehavior for any entity directly by calling GetBaseBehavior, prototyped below:
```cpp
BaseBehavior* GetBaseBehavior(EntityID ID);
```

In order to get the specialized behavior for any entity (so you can call any entity-specific method not declared by the base behavior), you can either dynamically cast the base behavior pointer obtained by the function above, or call GetBehavior for your specialization, prototyped below:
```cpp
template<EntitySys::Type T>
  static Behavior<T>* GetBehavior(EntityID ID);
```

For example, you can set the text of a text object with an EntityID named text like so:
```cpp
BehaviorComponentManager::GetBehavior<EntitySys::Type::Text>(text)->SetText();
```
