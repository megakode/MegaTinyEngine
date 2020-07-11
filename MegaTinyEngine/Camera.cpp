//
// Created by Peter Bone on 14/06/2020.
//

#include "Camera.h"
#include "Core.h"
#include "Actions/MoveAction.h"
void Engine::Camera::update(float ticksSinceLast) {

    if(m_isMouseDragging && dragIsDirty){
        Vec2i newLocalPos = localPosAtStartDrag + (dragCurrentPos-dragStartPos);
        //int moveDist = newLocalPos.dist(getLocalPosition());
        float duration = 0.4; // Lets start with a fixed duration, and not factoring in the distance.
        auto move = MoveAction::create(shared_from_this(),duration,getLocalPosition(),newLocalPos);

        if(m_CurrentMoveAction != nullptr){
            m_CurrentMoveAction->stop();
        }

        m_CurrentMoveAction = move;

        Core::actionManager()->addAction(move);
        //setLocalPosition(newLocalPos.x,newLocalPos.y);
        dragIsDirty = false;
    }

    if(m_kinematicBody.velocity.x != 0 || m_kinematicBody.velocity.y != 0)
    {
        GameObject::setLocalPosition( (int)m_kinematicBody.position.x , (int)m_kinematicBody.position.y );
    }

    m_kinematicBody.update(ticksSinceLast);

    GameObject::update(ticksSinceLast);
}

void Engine::Camera::draw(SDL_Renderer *renderer) {
    GameObject::draw(renderer);
}

bool Engine::Camera::handleEvent(const Engine::InputEvent &event) {

    constexpr float force = 1000;

    if(m_isMouseDragging && event.deviceType == InputDeviceType::Mouse && event.state == InputKeyState::Moved){
        dragCurrentPos = Vec2i{(int)event.position.x,(int)event.position.y};
        dragIsDirty = true;
    }

    if(event.state == InputKeyState::Pressed ) {

        if(event.key == InputKey::MouseButtonRight ){
            m_isMouseDragging = true;
            m_kinematicBody.accel = {0, 0};
            m_kinematicBody.velocity = {0, 0};
            localPosAtStartDrag = getLocalPosition();
            dragStartPos = Vec2i{(int)event.position.x,(int)event.position.y};
            dragCurrentPos = Vec2i{(int)event.position.x,(int)event.position.y};
        }

        if (event.key == InputKey::Left) {
            m_kinematicBody.position = Vec2f{static_cast<float>(getLocalPosition().x),static_cast<float>(getLocalPosition().y)};
            m_kinematicBody.setAcceleration({force, 0});
        }

        if (event.key == InputKey::Right) {
            m_kinematicBody.position = Vec2f{static_cast<float>(getLocalPosition().x),static_cast<float>(getLocalPosition().y)};
            m_kinematicBody.setAcceleration({-force, 0});
        }

        if (event.key == InputKey::Up) {
            m_kinematicBody.position = Vec2f{static_cast<float>(getLocalPosition().x),static_cast<float>(getLocalPosition().y)};
            m_kinematicBody.setAcceleration({0, force});
        }

        if (event.key == InputKey::Down) {
            m_kinematicBody.position = Vec2f{static_cast<float>(getLocalPosition().x),static_cast<float>(getLocalPosition().y)};
            m_kinematicBody.setAcceleration({0, -force});
        }
    }

    if(event.state == InputKeyState::Released ){

        if( event.key == InputKey::Left || event.key == InputKey::Right || event.key == InputKey::Up || event.key == InputKey::Down){
            m_kinematicBody.setAcceleration({0, 0});
        } else if(event.key == InputKey::MouseButtonRight){
            m_isMouseDragging = false;
        }

    }

    return false;
}
