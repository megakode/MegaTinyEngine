//
// Created by Peter Bone on 14/06/2020.
//

#ifndef SDLTEST_CAMERA_H
#define SDLTEST_CAMERA_H

#include "MegaTinyEngine/Base.h"
#include "GameObject.h"
#include "MegaTinyEngine/Actions/MoveAction.h"
#include "MegaTinyEngine/KinematicBody.h"

// God forklaring af simpel camera formel:
// https://gamedev.stackexchange.com/a/123844
// basically: screen = world - camera
namespace Engine {

    class Camera : public GameObject  {

    public:
        void update(float ticksSinceLast) override;

        void draw(SDL_Renderer *renderer) override;

        bool handleEvent(const InputEvent &event) override;

        /// Set the size of the scrollable canvas. The x and y can also be set to offset the displayed canvas.
        /// \param rect Bounds rect
        void setScrollingBounds( const Rect& rect );

    private:

        KinematicBody m_kinematicBody;
        bool m_isMouseDragging = false;
        Vec2i localPosAtStartDrag; // The local position of the camera when the drag started
        Vec2i dragStartPos; // The mouse window position at start of drag
        Vec2i dragCurrentPos; // The current mouse window position when dragging
        bool dragIsDirty = false;
        std::shared_ptr<MoveAction> m_CurrentMoveAction = nullptr;
        Rect m_bounds;

    };

}

#endif //SDLTEST_CAMERA_H