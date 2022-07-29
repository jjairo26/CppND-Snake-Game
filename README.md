# CPPND: Capstone Snake Game

This is my own version of a Snake game as a Capstone project for the Udacity C++ Nanodegree Program. The code for this repo uses [this repo](https://github.com/udacity/CppND-Capstone-Snake-Game) as a basis.

## Additional Features

Some additional game features include the following:

* A gift appears randomly every once in a while for some seconds. Eating it gives bonus points (as in the classical Snake2 game)
* Game information is now rendered in the main window:
  * The current score
  * Gift countdown timer until it disappears

On a more technical side, the renderer class has been extended to allow for PNG image and text rendering. Additionally, a new "Gift" class has been created.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2-TTF >= 2.0 (for font rendering)
  * Linux: `sudo apt-get install sdl2-ttf-dev`
  * MacOS: Download from [the GitHub repo](https://github.com/libsdl-org/SDL_ttf/releases) and install e.g. by following [this](https://www.youtube.com/watch?v=GROeu4fL730) video
  * Windows: Download from [the GitHub repo](https://github.com/libsdl-org/SDL_ttf/releases) and install e.g. by following [this](https://www.youtube.com/watch?v=9Ca-RVPwnBE) video
* SDL2-Image >= 2.0 (for PNG image rendering)
  * Linux: `sudo apt-get install sdl2-image-dev`
  * MacOS: Download from [the GitHub repo](https://github.com/libsdl-org/SDL_image). Or use [MacPorts](https://ports.macports.org/port/libsdl2_image/).
  * Windows: Download from [the GitHub repo](https://github.com/libsdl-org/SDL_image) and install e.g. by following [this](https://www.youtube.com/watch?v=YrWQsuDT3NE) video

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## File Structure

```bash
├── cmake
│   ├── FindSDL2_image.cmake
│   └── FindSDL2TTF.cmake
├── CMakeLists.txt
├── CODEOWNERS
├── LICENSE.md
├── README.md
├── res
│   ├── BOMBARD.ttf
│   └── gift.png
└── src
    ├── controller.cpp
    ├── controller.h
    ├── game.cpp
    ├── game.h
    ├── gift.cpp
    ├── gift.h
    ├── main.cpp
    ├── renderer.cpp
    ├── renderer.h
    ├── snake.cpp
    └── snake.h

```

## Addressed Rubric Points (Udacity)

### Loops, Functions I/O

| Criteria     | Specifications   | Explanation |
|--------------|-----------|------------|
| The project demonstrates an understanding of C++ functions and control structures. | A variety of control structures are used in the project. <br> The project code is clearly organized into functions.    | See e.g. Update method in game class and Render method in renderer class.  |

### Object-Oriented Programming

| Criteria | Specifications | Explanation |
|-----------|---------------|-------------|
|The project uses Object Oriented Programming techniques. | The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.| See the files for each class in `./src`|
|Classes use appropriate access specifiers for class members.|All class data members are explicitly specified as public, protected, or private. | See the files for each class in `./src` |
|Class constructors utilize member initialization lists.| All class members that are set to argument values are initialized through member initialization lists. | See e.g. `gift.cpp`|
|Classes abstract implementation details from their interfaces.|All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.| See e.g. `gift.cpp` |
|Classes encapsulate behavior.|Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.| See e.g. get and set functions in `gift.cpp` |
|Overloaded functions allow the same function to operate on different parameters.| One function is overloaded with different signatures for the same function name.| See e.g. RenderTexture method in Renderer class |

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
