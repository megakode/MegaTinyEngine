//
// Created by Peter Bone on 06/06/2020.
//

#ifndef SDLTEST_CORE_H
#define SDLTEST_CORE_H


#include <MegaTinyEngine/Actions/ActionManager.h>
#include <MegaTinyEngine/UI/UIManager.h>
#include <MegaTinyEngine/UI/FontManager.h>
#include "Collision/CollisionManager.h"
#include "AnimationManager.h"
#include "TextureCache.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Resources/ResourceLoader.h"
#include "IGame.h"

namespace Engine {

    class Core {

    public:

        // Singleton
    /*
        static Core& getInstance(){
            static Core instance;
            return instance;
        }
    */
        // Delete copy constructor and copy assignment
        Core(const Core&) = delete;
        Core& operator=(const Core&) = delete;

        // Initialization

        /**
         * Create the window that the game will be shown in.
         * @param pixelWidth Horizontal resolution
         * @param pixelHeight Vertical resolution
         * @param scaling Scale the pixels by this factor
         * @param resizable Whether the window will be resizable
         * @param title Window title
         * @return Whether the window could be created
         */
        static bool createWindowAndRenderer(int pixelWidth, int pixelHeight, int scaling, bool resizable, const std::string& title);

        /**
         * Enter a continuous game run loop.
         * @param game The game to run
         * @param framePerSecond not used
         * @return
         */
        static int runGame(IGame *game);

        // Getters for the managers

        static AnimationManager* animationManager();
        static TextureCache* textureCache();
        static InputManager* inputManager();
        static CollisionManager* collisionManager();
        static ActionManager* actionManager();
        static FontManager* fontManager();

        static SDL_Window* getWindow();
        static SDL_Renderer * getRenderer();

        // Settings

        static Rect getLogicalWindowSize();

        static void destroy();

    private:

        Core() = default;
        ~Core() = default;

        static bool init();

        static AnimationManager *m_animationManager;
        static TextureCache *m_textureCache;
        static InputManager *m_inputManager;
        static CollisionManager *m_collisionManager;
        static ActionManager *m_actionManager;
        static UIManager *m_uiManager;
        static FontManager *m_fontManager;
        static SDL_Renderer *m_renderer;
        static SDL_Window *m_window;


    };

}

#endif //SDLTEST_CORE_H
