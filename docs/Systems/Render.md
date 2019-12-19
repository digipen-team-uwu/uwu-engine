# Render

This is a system of [UWU Engine](../../README.md)

Our rendering system uses GLEW to load openGL functions and GLFW to create a window and openGL context. It also utilized graphics instancing to draw every entity with only one draw call except spine animated entities.

We used rectpack2D for atlas page packing after loading in all the textures.
