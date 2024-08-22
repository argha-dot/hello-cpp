# A Project so that I can learn how to use C++

The Idea is to create a game that uses a ray caster to render a semi-3D scene.

## Stuff Used

- C++, Why? that's the whole idea, learn C++.
- SFML, Why? dunno, saw it on YouTube, looked cool.

## How to run

Dunno how to do it in windows, but on linux, you can do this:
 - Clone the Repo
 - Make sure `g++` and `make` are installed, if not, install them by running `sudo apt install build-essential`
 - Install SFML by running `sudo apt install libsfml-dev`
 - Run `make` in the root directory of the project

## TODOs

- [x] Add a ray caster
- Add the rest of the game engine / Ray Caster things
  - Raycaster stuff
    - [x] Textured Ray Caster
    - [x] Refactor the main game logic into it's own class
    - [ ] Floors and Ceilings
    - [ ] Sprites and Decals
    - [ ] Doors, Transparent Walls, 
  - General Engine Stuff
    - [ ] Add something like a tile map, and use a texture atlas instead of loading the textures individually
    - [ ] Animations
    - [ ] Lighting
    - [ ] Use Something Like Portals (in Wolf3d) or Binary Space Partitioning to do the level loading
- Gameplay and Player Experience Stuff
  - [x] Add a basic minimap
    - [x] Make it look better, for eg, add a translucent background to the minimap
  - [x] Add Mouse Input (so moving the mouse changes the direction)
  - [x] Add Left and Right Arrows to strafe
  - [ ] Add a state machine for basic menus and states
  - [ ] Add a HUD
  - [ ] Add the Player Model
 
