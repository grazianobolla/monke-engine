# Monke Engine (Game Engine)

Monke Engine aims to be a simple and fast game engine, capable of reproducing any ideas quickly and efficiently.
Made for those who want something low-level while maintaining simplicity.

# Use (linux)
- Compile using `make`
- Create a new project folder and copy `include` and `shaders` into it
- Create a main.cpp file (there is a demo in the repo)
- Run using `export LD_LIBRARY_PATH=/usr/local/lib && g++ YOURMAINFILE.cpp -Iinclude -lmonke -lGL -lglfw -o app.o && ./app.o`

# Examples
## Single Static Sprite
This for example, is how you render a Sprite that follows your cursor:
![Code Example](https://github.com/grazianobolla/monke-engine/blob/main/readme/simple_sprite_code.png "Code Example")
#### This is how it looks:

![Code Example](https://github.com/grazianobolla/monke-engine/blob/main/readme/simple_sprite_example.png "Code Example")

## Multiple Animated Sprites
Drawing multiple sprites it's also quite easy, for example this is one simple way to render a tilemap.
First we load our texture, in this case a 128x32 sprite sheet with numbers:

![Code Example](https://github.com/grazianobolla/monke-engine/blob/main/readme/sheet.png "Code Example")

We can then tell the engine to dynamically update the sprites *Texture Coordinates* and render them on a loop.

![Code Example](https://github.com/grazianobolla/monke-engine/blob/main/readme/tilemap_code.png "Code Example")

#### Compile and see how it looks:

![Tilemap Gif](https://github.com/grazianobolla/monke-engine/blob/main/readme/tilemap_gif.gif)

As you can see, the framerate is extremely high, with this tilemap on a GTX1060 it was around 14000 FPS!

![Framerate](https://github.com/grazianobolla/monke-engine/blob/main/readme/tilemap_framerate.png "Framerate")
