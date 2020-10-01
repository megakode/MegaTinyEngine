//
// Created by Peter Bone on 06/06/2020.
//

#include <iostream>
#include "SDL_image.h"
#include "Core.h"
#include "Sprite.h"

namespace Engine {

    AnimationManager* Core::m_animationManager;
    TextureCache* Core::m_textureCache;
    InputManager* Core::m_inputManager;
    CollisionManager* Core::m_collisionManager;
    ActionManager* Core::m_actionManager;
    UIManager* Core::m_uiManager;
    FontManager* Core::m_fontManager;
    SDL_Renderer* Core::m_renderer;
    SDL_Window* Core::m_window;

    bool Core::init() {

        assert(m_renderer);

        m_animationManager = new AnimationManager();
        m_textureCache = new TextureCache(m_renderer);
        m_inputManager = new InputManager();
        m_collisionManager = new CollisionManager();
        m_actionManager = new ActionManager();
        m_uiManager = new UIManager();
        m_fontManager = new FontManager();

        return true;
    }

    bool Core::createWindowAndRenderer(int pixelWidth, int pixelHeight, int scaling, bool resizable)
    {
        // Init SDL

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) // SDL_INIT_GAMECONTROLLER
        {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        // Create Window

        Uint32 flags = SDL_WINDOW_SHOWN;

        if (resizable) {
            flags |= SDL_WINDOW_RESIZABLE;
        }

        m_window = SDL_CreateWindow("SDL MegaMiniEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pixelWidth*scaling, pixelHeight*scaling, flags );
        if (m_window == nullptr)
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        // Init SDL_Image library, so we can load PNGs

        if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            std::cerr << "Could not init PNG image library";
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        // Create renderer

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

        SDL_RenderSetLogicalSize(m_renderer, pixelWidth, pixelHeight);
        SDL_RenderSetIntegerScale(m_renderer,SDL_TRUE);

        if (m_renderer == nullptr)
        {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        if(!Core::init()){
            return false;
        };

        return true;
    }

    int Core::runGame(IGame *game)
    {
        bool quit = false;
        Uint32 lastTime, currentTime;
        SDL_Event e;

        auto sceneNode = game->initialize();

        Core::inputManager()->setListener(game);

        lastTime = currentTime = SDL_GetTicks();

        while (!quit) {

            //First clear the renderer
            SDL_SetRenderDrawColor(m_renderer, 25, 42, 88, 255);
            SDL_RenderClear(m_renderer);

            // Draw scene
            sceneNode->draw(m_renderer);
            // Let the game do additional drawing
            game->draw(m_renderer);

            //Update the screen
            SDL_RenderPresent(m_renderer);

            currentTime = SDL_GetTicks();

            float frameTime = (float)(currentTime-lastTime) / 1000;

            Core::animationManager()->updateAnimations(frameTime);

            // Update Game

            sceneNode->update(frameTime);
            game->update(frameTime);

            Core::collisionManager()->doCollisionChecks();


            Core::actionManager()->update(frameTime);


            lastTime = currentTime;


            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
                    case SDL_MOUSEBUTTONDOWN:
                    case SDL_MOUSEBUTTONUP:
                    case SDL_MOUSEMOTION:
                        Core::inputManager()->processInput(e);
                        break;
                }

            }

            // Get the last mouse position instead of doing it pr. SDL event, so we reduce the heavy uiManager call to once pr. frame
            m_uiManager->handleInput(m_inputManager->getLastMousePosition());
        }

        Core::inputManager()->setListener(nullptr);

        delete m_animationManager;
        delete m_textureCache;
        delete m_inputManager;
        delete m_collisionManager;
        delete m_actionManager;
        delete m_uiManager;
        delete m_fontManager;

        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return 0;
    }

    AnimationManager* Core::animationManager() {
        return m_animationManager;
    }

    TextureCache* Core::textureCache() {
        return m_textureCache;
    }

    InputManager *Core::inputManager() {
        return m_inputManager;
    }

    CollisionManager *Core::collisionManager() {
        return m_collisionManager;
    }

    ActionManager *Core::actionManager() {
        return m_actionManager;
    }

    FontManager *Core::fontManager()
    {
        return m_fontManager;
    }

    Rect Core::getLogicalWindowSize() {
        if(m_renderer != nullptr ){
            Rect size;
            SDL_RenderGetLogicalSize(m_renderer,&size.width,&size.height);
            return size;
        } else {
            return {0,0,0,0};
        }
    }

    // Private stuff

    void Core::destroy(){

    }

    SDL_Window *Core::getWindow()
    {
        return m_window;
    }


}
