//
//  GameObject.hpp
//  SDLTest
//
//  Created by Peter Bone on 19/05/2020.
//  Copyright © 2020 megakode. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h

#include "Base.h"
#include "InputManager.h"
#include "SDL.h"
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace Engine {

    class GameObject : public std::enable_shared_from_this<GameObject> {

    public:

        std::string debugName;

        GameObject();
        ~GameObject();

        void addChild(const std::shared_ptr<GameObject>& child);
        const std::list<std::shared_ptr<GameObject>>& getChildren();

        void removeAllChildren();

        void removeFromParent();

        void setLocalPosition( int x, int y );

        void setLocalPosition( const Vec2i& position );

        const Vec2i& getLocalPosition() const;

        int getX() const;
        int getY() const;

        Vec2i getWorldPosition();

        void setVisible( bool visible );
        bool isVisible() const;

        virtual void update(float ticksSinceLast );
        virtual void draw( SDL_Renderer *renderer );

        /// Event function called on all GameObjects in a tree whenever an event occurs.
        /// \param event The event received from SDL (keyboard, mouse, etc.)
        /// \return Whether the GameObject wants to swallow the event, and prevent it from being sent further into the tree.
        virtual bool handleEvent( const InputEvent& event );

    protected:

        bool isWorldPositionDirty;

        bool m_isVisible = true;

        std::list<std::shared_ptr<GameObject>> children;
        GameObject *parent = nullptr;

        ///
        /// Set isWorldPositionDirty recursively on all children. Our own member variable is also set.
        ///
        void setWorldPositionIsDirtyRecursively( bool isDirty );

    private:

        Vec2i localPosition = {0,0};
        Vec2i worldPosition = {0,0};

        void removeChild(GameObject *object);

    };

}
#endif /* GameObject_h */
