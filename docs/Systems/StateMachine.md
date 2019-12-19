# StateMachine

- [StateMachine](#statemachine)
  - [Getting Started](#getting-started)
  - [Your Specific Implementation](#your-specific-implementation)
  - [Switching States](#switching-states)
    - [Restarting a State](#restarting-a-state)

This system allows for very easy instantiation and updating of finite state machines.

## Getting Started
First, include StateMachine.hpp. This file contains everything you will need.
To create a finite state machine, simply use the macro StateMachine. Its first parameter is the name of the state machine. After that, simply fill in the names of all of the states you wish the machine to have.
```cpp
StateMachine(Example, State1, State2);
```
This will create a class called ExampleStateMachine with several functions that are unimplemented. It is up to you to implement these. Depending on the nature of your state machine, it may be preferable to implement them in separate files so that each state can have its own static state.

## Your Specific Implementation
The Finite State Machine is based on each state having specific code that is run at certain times while updating or switching states.

| State Functions | Notes |
|:---------------:|-------|
| Load_StateName   | Doesn't get called when restarting state. |
| Enter_StateName  | |
| Update_StateName | Gets called once per frame. |
| Exit_StateName   | |
| Unload_StateName | Doesn't get called when restarting state. |

All of these functions have the signature `void f(void)`. If your state doesn't need to do one of these, simply implement it with a blank body.
For instance:
```cpp
void Load_State1() { /* load files for state1 here */ }
```

## Switching States
In order to switch the state of a Finite State Machine, just call SetNextState from within your state code. The state of a state machine cannot be changed outside of itself.
```cpp
SetNextState(State2);
```
The above code will switch to the State2 state when the machine is updated.
When a Finite State Machine changes state from State1 to State2, code executes in the following order:
* Update State1
* Exit State1
* Unload State1
* Load State2
* Enter State2
* Update State2 (next frame)

### Restarting a State
You can also restart the current state by using the code:
```cpp
SetNextState(Restart);
```

If this code was run from within State1, this will cause the following code to execute:
* Update State1
* Exit State1
* Enter State1
* Update State1 (next frame)
