# Game of Life (C++11)

A test driven (sub-optimal) implementation of Conway's Game of Life. It is a C++11 OpenGL 3.2 app that uses the [GLFW](http://www.glfw.org), [GLEW](http://glew.sourceforge.net/) and [GLM](http://glm.g-truc.net/) libraries and builds with [CMake](http://www.cmake.org/). [Bandit](http://banditcpp.org/) is used for unit testing.

All libraries are included as git submodules and built from source with the application to ensure portability.

![](http://andystanton.github.io/game-of-life-cpp/gameoflife.png)

A Youtube video of the implementation working can be found [here](http://youtu.be/EQOfD_yJMBU).

## Rules

From the [Wikipedia entry on Conway's Game of Life](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life):

The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead. Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overcrowding.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## Requirements

* gcc 4.9.1 or clang 3.4
* CMake >= 2.8.12
* Make >= 3.81
* Rake >= 10.3
* OpenGL >= 3.2

## Quick Start

```sh
git clone https://github.com/andystanton/game-of-life-cpp.git --recursive

cd game-of-life-cpp

rake default start
```

## Libraries

* [glfw](http://www.glfw.org/) 3.0.4
* [glm](http://glm.g-truc.net/) 0.9.5
* [glew](http://glew.sourceforge.net/) 1.10.0
* [bandit](http://banditcpp.org/) ffa30f3
* [gmock](https://code.google.com/p/googlemock/) & [gtest](https://code.google.com/p/googletest/) 1.7.0
