
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PUBLIC Actions)
target_include_directories(${PROJECT_NAME} PUBLIC Collision)
target_include_directories(${PROJECT_NAME} PUBLIC GameObjects)
target_include_directories(${PROJECT_NAME} PUBLIC Resources)
target_include_directories(${PROJECT_NAME} PUBLIC UI)

target_sources(${PROJECT_NAME} PUBLIC
        Actions/ActionManager.cpp
        Actions/Action.cpp
        Actions/FadeAction.cpp
        Actions/MoveAction.cpp
        Actions/DestroyAction.cpp
        Actions/RepeatAction.cpp
        Actions/Sequence.cpp
        Collision/BoxCollider.cpp
        Collision/CollisionManager.cpp
        Collision/CollisionInfo.cpp
        Resources/ResourceLoader.cpp
        Resources/ResourcePathUtils.cpp
        UI/UIManager.cpp
        UI/FontManager.cpp
        UI/Button.cpp
        AnimationManager.cpp
        GameObjects/Camera.cpp
        Core.cpp
        GameObjects/GameObject.cpp
        InputManager.cpp
        KinematicBody.cpp
        GameObjects/Sprite.cpp
        GameObjects/TextNode.cpp
        Texture.cpp
        TextureCache.cpp
        Scene.cpp
        GameObjects/Layer.cpp
        Base.cpp
)