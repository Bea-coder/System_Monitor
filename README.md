# System-Monitor

Submitted code for System Monitor Project in the Object Oriented Programming Course of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 
I completed the implementation of  the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.
---
## System Monitor
System Monitor is a similar application of **htop** for linux OS where
memory and cpu usages are displayed for all processes.

### Requirements: 
It requires **ncurses** library.

---
## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all build-artifacts

## Instructions

1. Build the project: `make build`

2. Run the resulting executable: `./build/monitor`
