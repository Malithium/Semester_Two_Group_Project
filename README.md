# *Semester Two Group Project*

A simple 3D Platformer where you collect collectables to finish the level. 

11/02/2015 : It will feature two levels, to begin with, and hopefully time won't constrain us from expanding it beyond this small design. The player will run around collecting diamonds, which will try and avoid the player using A* path-finding, however we will be using OpenGL to load in blocks of cubes to create interactive levels.

11/03/2015 : The game will now include 5 tutorial levels, and once these are completed we hope to add an additional level with high difficulty. Core mechanics, so collecting diamonds and trasversing through the level are still the main goals, but we hope the level designs will provide the challenge to our game. Code wise we have transitioned from into calling cube assets (Of different sizes) in preparation for bounding boxes (Collision detection). We are facing difficulties with the camera, but I trust my colleague to have it working completely by the end of the month. 

27/03/2015 : Due to making progress alot faster than anticipated I thought I would give a brief update regarding where we currently are in regards to a finished product. We have created a system that generates levels based on vector positions stored in text files, effectively giving us the ability to load and unload levels. We have also made some major changes to the Camera class and it's condition is now satisfactory, this means the majority of work on the camera will be bug fixes and performance tweaks. 

Our next goal is to create bounding boxes around our objects so that we can start implementing collision detection into our program. This will enable us to implement gravity, jumping, collectables, doors and allow us to properly transition between level's. After this feature has been implemented we have effectively met all of our core goals and can work towards finishing the game. As my colleague has more experience with drawing our objects to the screen I shall leave the task of creating bounding boxes to him, in return I will work on the math's involved with collision detection as I have more experience with the camera class where all the camera movement happens.

We will try to post new information the 11th of every month (Until the 30th of April).

# Prerequisites #

* GNU Autotools
* OpenGL 3.0
* C++11 compiler (tested with GCC 4.8.3+)
* [Boost](http://www.boost.org/)
* [GLEW](http://glew.sourceforge.net/)
* [SDL2](https://www.libsdl.org/)
* [GLM](http://glm.g-truc.net/)

On Fedora 20 or later you can install these using a single command (as root):

> $ yum install boost-* glew-devel SDL2_* glm-devel

# Building #

After cloning the source code or extracting a distributed archive, change to the
directory where the source code is:

``` bash
$ autoreconf -i
$ ./configure
$ make
```

Alternatively, if you'd like to build the project in debug mode use:

> $ make CXXFLAGS=-DDEBUG

# Running #

The build process should create a binary that can be executed as follows:

> $ ./src/shaderexample

See

> $ ./src/shaderexample --help

for usage instructions.

