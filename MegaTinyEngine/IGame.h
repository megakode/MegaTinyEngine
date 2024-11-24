//
// Created by Peter Bone on 28/06/2020.
//

#ifndef IGAME_H
#define IGAME_H

#include "InputManager.h"
#include "Scene.h"
#include <SDL.h>

namespace Engine {

/**
 * The primary interface a game must implement, for the engine to be able to run it.
 * The engines main run loop can be illustrated with the following pseudo code:
 *
 * game->createScene()
 * while(!quit) {
 *   game->update()
 *   for all gameobjects in scene:
 *      draw(gameobject)
 *   game->draw()
 *   while(input_events_available)
 *      game->handleInput(next_input_event)
 * }
 *
 */
class IGame : public IInputListener {

public:
    virtual ~IGame() = default;
    /**
     * Subclasses must create a `Scene` object and return it in this function.
     * It will only be called once when the game starts, and the subclass is allowed to hold its own reference to the Scene object as well.
     * @return Shared pointer to the newly created `Scene` object.
     */
    virtual std::shared_ptr<Scene> createScene() = 0;
    /**
     * Called once pr. frame
     * @param deltaTime Time passed since last frame
     */
    virtual void update(float deltaTime) = 0;
    /**
     * Method for doing additional drawing.
     * The engine automatically handles drawing of all Layers and the GameObjects added to them, but if you need any additional drawing, this is the place to do it.
     * @param renderer renderer that can be used to draw stuff.
     */
    virtual void draw(SDL_Renderer* renderer) = 0;
    /**
     * Method for handling input events to the game (keyboard and mouse).
     * @param event Input event to be processed by the game.
     */
    void handleInput(const InputEvent& event) override = 0;
};

}

#endif // IGAME_H
