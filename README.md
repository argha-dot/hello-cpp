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

- Add the rest of the game engine / Ray Caster things
  - Raycaster stuff
    - [x] Add a ray caster
    - [x] Textured Ray Caster
    - [x] Refactor the main game logic into it's own class
    - [x] Floors and Ceilings
    - [ ] Sprites and Decals
    - [ ] Doors, Transparent Walls,
  - General Engine Stuff
    - [x] Render everything into an image and then scale that image to the window size.
      > This is done due to the performance issues with the ray caster and software rendering itself. 
      > Rendering something like floors and ceilings which blits to the whole screen every frame lead to significant performance loss. The game went from running at 120 FPS at 720p to 90 FPS.
      > One possible solution would've been to optimize the floor/ceiling rendering, but that would've been a bit more work than I wanted, and what I've been using is apparently kinda optimized.
      > And it still wouldn't have solved the performance issues completely, just using the ray caster to render the walls at 1080p, without the floors, without any event checking dropped the FPS to 45,
      > So now I render the ray casted walls and the ceiling / floor to a smaller [sf::Image](https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Image.php), and then scale that image to the window size by a factor of `WINDOW_WIDTH / SCREEN_WIDTH`.
      > This leads to a solid 120 FPS at 1080p, at the cost of a bit of texture quality. But because of the pixel art style, it's not noticeable at around 200% scaling.
    - [ ] Add something like a tile map, and use a texture atlas instead of loading the textures individually
    - [ ] Animations
    - [ ] Lighting
    - [ ] Use Something Like Portals (in Wolf3d) or Binary Space Partitioning to do the level loading
- Gameplay and Player Experience Stuff
  - [x] Add a basic minimap
    - [ ] Make it look better, for eg, add a translucent background to the minimap
  - [x] Add Mouse Input (so moving the mouse changes the direction)
  - [x] Add Left and Right Arrows to strafe
  - [ ] Add a state machine for basic menus and states
  - [ ] Add the Player Model
  - [ ] Add a HUD
 
