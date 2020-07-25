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
    SDL_Renderer* Core::m_renderer;

    bool Core::init( SDL_Renderer *renderer ) {

        m_animationManager = new AnimationManager();
        m_textureCache = new TextureCache(renderer);
        m_inputManager = new InputManager();
        m_collisionManager = new CollisionManager();
        m_actionManager = new ActionManager();
        m_renderer = renderer;

        return true;
    }

    int Core::runGame(IGame *game, int windowWidth, int windowHeight, int logicalWidth, int logicalHeight)
    {
        // Init SDL

        if (SDL_Init(SDL_INIT_VIDEO) != 0){
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        // Create Window

        SDL_Window *win = SDL_CreateWindow("SDL MegaMiniEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
        if (win == nullptr){
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        // Init SDL_Image library, so we can load PNGs

        if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            std::cerr << "Could not init PNG image library";
            SDL_DestroyWindow(win);
            SDL_Quit();
            return 1;
        }

        // Create renderer

        SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

        SDL_RenderSetLogicalSize(ren, logicalWidth, logicalHeight);
        SDL_RenderSetIntegerScale(ren,SDL_TRUE);

        if (ren == nullptr){
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(win);
            SDL_Quit();
            return 1;
        }


        bool quit = false;
        Uint32 lastTime, currentTime;
        SDL_Event e;

        Core::init(ren);

        auto sceneNode = game->initialize();

        Core::inputManager()->setListener(game);

        lastTime = currentTime = SDL_GetTicks();

        while (!quit) {

            //First clear the renderer
            SDL_SetRenderDrawColor(ren, 25, 42, 88, 255);
            SDL_RenderClear(ren);

            sceneNode->draw(ren);
            game->draw(ren);

            //Update the screen
            SDL_RenderPresent(ren);

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
        }

        Core::inputManager()->setListener(nullptr);

        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();

        return 0;
    }

    std::shared_ptr<Sprite> Core::createSprite(const std::string& textureId, const std::string& animationId){

        auto texture = m_textureCache->getTextureWithIdentifier(textureId);
        assert(texture);
        auto sprite = std::make_shared<Sprite>(texture);


        if(!animationId.empty()){
            sprite->playAnimation(animationId);
        }

        return sprite;
    }

    /*
    std::shared_ptr<Sprite> Core::createSprite(const std::string& textureId ){
        auto sprite = std::make_shared<Sprite>(Core::getInstance().textureCache()->getTextureWithIdentifier("taco"));
        return sprite;
    }
    */
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

    Rect Core::getLogicalWindowSize() {
        if(m_renderer != nullptr ){
            Rect size;
            SDL_RenderGetLogicalSize(m_renderer,&size.width,&size.height);
            return size;
        } else {
            return {0,0,0,0};
        }
    }


}
