//
// Created by Peter Bone on 06/06/2020.
//

#ifndef SDLTEST_CORE_H
#define SDLTEST_CORE_H


#include <MegaTinyEngine/Actions/ActionManager.h>
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

        static bool init(SDL_Renderer *renderer );

        static int runGame(IGame *game, int windowWidth, int windowHeight, int logicalWidth, int logicalHeight);

        // Factory functions

        static std::shared_ptr<Sprite> createSprite(const std::string& textureId, const std::string& animationId = "");

        // Getters for the managers

        static AnimationManager* animationManager();
        static TextureCache* textureCache();
        static InputManager* inputManager();
        static CollisionManager* collisionManager();
        static ActionManager* actionManager();

        // Settings

        static Rect getLogicalWindowSize();

    private:

        Core() = default;
        ~Core() = default;

        static AnimationManager *m_animationManager;
        static TextureCache *m_textureCache;
        static InputManager *m_inputManager;
        static CollisionManager *m_collisionManager;
        static ActionManager *m_actionManager;
        static SDL_Renderer *m_renderer;
    };

}

#endif //SDLTEST_CORE_H
