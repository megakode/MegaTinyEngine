//
// Created by Peter Bone on 14/06/2020.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "Base.h"
#include "GameObject.h"
#include "MoveAction.h"
#include "KinematicBody.h"

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

#endif //CAMERA_H
