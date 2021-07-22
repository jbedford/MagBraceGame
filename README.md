# MagBraceGame
MagBrace - 2D arcade style game inspired by NEMS Story event.

## Project Description
Project chosen is a Homemade Arcade Style Game similar to Asteroids that I call "MagBrace". 

Player (Charon- trapzoid) must avoid asteroids while saving 4 survivors (red squares). If an asteroid hits you, you die and can't win the game. (Player turns from blue to red). 
Even if you save more people, you yourself dies and game is lost. (You will still be able to play game and rescue survivors,but you just won't win).

You navigate and maneuver thru asteroid belt using magbraces, which launch then anchor to asteroids. Once clamped you can push and pull yourself relative to the asteroid. 

Be careful asteroids will start to be pushed or pulled in the direction relative to you. 

In space there is no friction, you will continue to drift, unless you slow your momentum with magbraces. 

Player can rotate in place and use the bright green aim lines to indictate the direction you launch the mag braces. 

**Controls:**
- Player can **Rotate** in place using **"<-"** or **"->**" arrow keys or "c" and "n" keys
- Player can **Launch** MagBrace using **"w"** key
- Player can **Pull** an anchored MagBrace using **"s"** key
- Player can **Push** an anchored MagBrace using **"d"** key
    (MagBraces must be anchored before pull or push can take effect)
- Player can **Release** MagBrace using **"a"** key or **"SPACE"** key
    (Note Magbraces must be released before launching again)

**Objectice: Player must save 4 survivors and as well as survive the Roid Belt themselves to win the game.**

## Dependencies for Running Locally
- cmake >= 3.7
- make >= 4.1 (Linus, Mac), 3.81 (Windows)
- SDL2 >= 2.0
- gcc/g++ >= 5.4

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it `./CharonGame`

## Rubric Points Addressed from Criteria List:

**Loops, Functions, I/O:**
- The project demonstrates an understanding of C++ functions and control structures:
  - see file magbrace.cpp - MagBrace::UpdateBracePoints()
  - see file renderer.cpp - Renderer::Render()
- Project reads from file
  - N/A
- Project accepts user input and processes the input: 
  - see controller.cpp - Controller::HandleInput()


**Object Oriented Programming:**
- Project Uses Object Oriented Programming Techniques
  - see magbrace.h magbrace.cpp roid.h roid.cpp
- Classes use appropriate access for class members
  - see magbrace.h magbrace.cpp roid.h roid.cpp charon.h charon.cpp
- Class constructors utilize member initializatoin lists.
  - see magbrace.h roid.h charon.h
- Classes abstract implementatoin details form their interfaces
  - see magbrace.h  N/A
- Classes encapsulate behavior
  - see magbrace.h magbrace.cpp currentState
    

**Memory Management:**
- The project uses destructors appropriately
  - see roid.h 
        see magbrace.h
- The project follows the Rule of 5
  - see magbrace.h
    
**Concurrency**
- N/A
