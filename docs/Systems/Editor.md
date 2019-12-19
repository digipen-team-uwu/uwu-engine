# Editor

- [Launching the Editor](#launching-the-editor)
- [Closing the Editor](#closing-the-editor)

This system uses the Dear ImGui library to create a GUI editor for existing game objects.

In order to launch the Editor from your code, you must first include the file Editor.h.

## Launching the Editor
Since all the relevant Editor functions are static, you can launch it without having a reference to a specific instantiation of the Editor.
The code to launch the Editor then looks like this:
```cpp
Editor::Start();
```

## Closing the Editor
For safety's sake, it is important to close the Editor down before transferring between game states. This is different from destructing the Editor.
To do so, simply call
```cpp
Editor::Stop();
```
This will safely close the editor until is is reopened using Start.