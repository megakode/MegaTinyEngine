# MegaTinyEngine

Mega Tiny Engine is a small work-in-progress 2D game engine written in modern C++. 

The engine is a hobby engine meant to make me more productive in making small casual indie games, rather than relying on one of the huge all-in-one engine solutions like Unreal, GoDot and Unity, and at the same time making me code in C++ as opposed to various scripting languages used in other engines. Thus the small feature-set.

I develop the engine in tandem with a couple of small example games, as this has turned out to be a great productive and fun way for me. I therefore only add features once i actually need them in a game, and many obvious and common things might therefore be missing.

![example_layers](https://user-images.githubusercontent.com/6302832/203104411-4bf35be4-7102-4a5f-a5e7-666999684798.gif)

### Features

- Scene tree
- Layers
- Actions with chaining and easing (Fade, Rotate, Move, etc.)
- AABB collision
- Kinematics
- Sprite animation
- Bitmap text
- JSON based resource loading

### Dependencies

- CMake for building
- SDL for rendering
- https://github.com/nlohmann/json for handling JSON.

# Basics

See: `example/example_basic.cpp` for a basic example of setting up a minimal game run loop, and drawing a sprite on screen.

Every game must implement the `IGame` interface by subclassing it. The interface has a set of basic methods:

```cpp
std::shared_ptr<Scene> createScene();
void update( float deltaTime );
void draw( SDL_Renderer *renderer );
void handleInput( const InputEvent& event );
```

*createScene* must create and setup a Scene, which is the root node for a games tree of object. A Scene is a container node composed of Layers, which again contains different GameObject subclasses such as Sprite.

Once the scene is created, the core enters its main run loop, which is illustrated in pseudo code below:

```
while (!quit) {
    draw_scene_layers_and_objects()
    game.draw()
    game.update(time_since_last_frame)
    game.handleInput(keys_pressed)
}
```

First, all the Scenes layers are drawn, as well as all the objects that are added to them.

Second, `draw()` is called on `IGame`, which is the games chance to do any additional drawing, not related to any specific GameObject.

Third, `update()` is called, which is where all the game logic is usually placed. Here you can move objects, spawn bullets, etc.

Fourth, ` handleInput()` is called if any input event has occurred. (Mouse / keyboard)
