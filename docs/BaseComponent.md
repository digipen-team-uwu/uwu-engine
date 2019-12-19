# Base Component

- [Base Component](#base-component)
  - [Interface](#interface)
  - [Creating A New Component](#creating-a-new-component)
    - [Class Declaration](#class-declaration)
    - [Required Implementations](#required-implementations)
    - [Specific Implementation](#specific-implementation)
    - [Registration](#registration)

The base component is a component of [uwu Engine](../README.md).

It automatically registers itself into the [Entity Manager](./Systems/EntityManager.md) which will handle construction, initialization, updating, and deconstruction of the component.
It is relatively easy to add new components to the engine.
The base component is available in the ``` BaseComponent.h ``` header.

## Interface

The base component has a simple interface. The IsActive method returns a boolean that represents whether the component has been activated for a certain entity.

## Creating A New Component

### Class Declaration
Any new component needs to first extend the BaseComponent class. It also needs to templatize the BaseComponent on itself, i.e.
```cpp
class MyNewComponent : public BaseComponent<MyNewComponent>
{
...
}
```
Note that it **must** be publicly inherited.

### Required Implementations
There are only a few more things to implement to make the new component work correctly. First, it must implement a default constructor and a destructor. It also needs to implement the functions InitObject and ShutdownObject, which take an entity's ID number and return void. It also needs to implement a function Update that has no parameters and returns void.
```cpp
MyNewComponent();
~MyNewComponent();
void InitObject(EntityID ID) override;
void ShutdownObject(EntityID ID) override;
void Update() override;
```
The constructor should initialize any data that the entire system needs. The destructor should release this data.
The InitObject function should initialize any data the component needs for the given entity. The ShutdownObject function should flush the data a component was using for a given entity. The Update function will be run once per frame, and should handle any state changes that the system needs. If any of these functions are not required, they should have a blank implementation in the header file.

### Specific Implementation
Now, the component can be implemented. **All members and methods must be static.** If you need a dynamically allocated member, use a static pointer and allocate it appropriately. The only exception to this is if your component has further children (such as the [Behavior Component](./Components/Behavior.md).)
Note: It is preferable to initialize static data members in the static initializer instead of the constructor.

### Registration
Immediately following the declaration of the class, it is time to set up the auto-registration. You can choose what order your component updates in, as it pertains to the SystemOrder. All components update within the [Entity Manager](./Systems/EntityManager.md), but some components need to update in a particular order. If this is the case, add an entry to the ```ComponentUpdateOrder``` enumeration for your system. If the order your component updates in does not matter, simply use ```ComponentUpdateOrder::LAST```. To enable the auto-registration:
```cpp
size_t RegisterComponentHelper<MyNewComponent>::RegisterComponentHelper_ID = EntityManager::AddComponent<MyNewComponent>(ComponentUpdateOrder:LAST);
```
Whew. With that line, registration will be completed for you and there is nothing else to do. Your component is complete!
