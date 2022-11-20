# Destruction
Physics Game made for Software build-a-thon

# Setup
This is a visual studio project for windows, I unfortunately have no idea how to use CMake so sorry about that.
Just extract the project and you can run the executable that is there.
You can also build the sln file and go through the memory CPU, and GPU trackers.

# How To Play!
- click and drag ball to lauch it
- press any key to recover it
- repeat until you clear the platform of blocks

# Notes
This project is written entirely in C++ using the SDL and SDL_image libraries which abstract away some OpenGL functionality and provide image texture loading.
Feel free to check CPU GPU and memory usage we tried to optimize as much as possible but any pointers appreciated.
Any tips on collision detection are appreciated it was rough to do in the 2 days, kinda hacky.
This is the first physics engine (if I can call it that) that we've both written so would love feedback.
We work mainly with embedded systems but branching to graphics was fun!

# Libraries
- SDL.lib
- SDL_image.lib
- std libraries like vector and cmath
