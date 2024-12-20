/**
 * This example shows how to load a single non animated texture, and display it on screen.
 */

#include "Core.h"
#include "Destroy.h"
#include "IGame.h"
#include "Move.h"
#include "Repeat.h"
#include "Sequence.h"

using namespace Engine;

class ExampleGame : public IGame {
public:
    virtual ~ExampleGame() = default;

    ExampleGame() = default;

    /**
     * Every game must implement this method. It creates the Scene which forms the graphical foundation for our game.
     * A scene is basically like one or more pieces of paper (called layers in the engine) which will be displayed on top of each other.
     * All objects you create can be added to one of the scenes layers, and will automatically be drawn when the layer is drawn.
     */
    std::shared_ptr<Scene> createScene() override
    {

        // First tell the texture cache to load the slime texture

        Core::textureCache()->loadTexture("resources/slime_single.png", "slime");

        // Then create a scene with a single layer

        auto scene = std::make_shared<Scene>();
        scene->addLayer(FOREGROUND_LAYER);

        // And last, create a sprite using the texture we loaded earlier, and sets its position to the center of the window.

        SpritePtr slime = Sprite::createWithTexture("slime");
        slime->setLocalPosition(Core::getLogicalWindowSize().width / 2, Core::getLogicalWindowSize().height / 2);
        scene->addObjectToLayer(slime, FOREGROUND_LAYER);

        // Make a repeating sequence of actions, that moves a sprite back and forth

        const Vec2i to = { Core::getLogicalWindowSize().width / 2, 100 };
        const Vec2i from = { Core::getLogicalWindowSize().width / 2, 50 };
        constexpr float duration = 1.0f;

        auto move = Actions::Move::create(slime, duration, from, to, Actions::EasingType::OutBounce);

        auto moveBack = Actions::Move::create(slime, duration, to, from);
        // All IntervalAction subclasses (including Move) have the easingType property.
        moveBack->easingType = Actions::EasingType::InBounce;

        // Create a sequence with the two Move actions...
        auto seq = Actions::Sequence::create({ move, moveBack });
        // ...and repeat it forever
        auto repeat = Actions::Repeat::createRepeatForever(seq);

        // Remember to add the action to the ActionManager, otherwise they will not run.
        Core::actionManager()->addAction(repeat);

        return scene;
    };

    void update(float deltaTime) override {
        // Here we would update game logic, move stuff around, etc.
    };

    void draw(SDL_Renderer* renderer) override {
        // Here we could render additional stuff each frame using the SDL renderer directly.
    };

    void handleInput(const Engine::InputEvent& event) override {

    };

private:
    static constexpr int FOREGROUND_LAYER = 10;
};

int main()
{
    ExampleGame game;

    Engine::Core::createWindowAndRenderer(320, 200, 3, false, "Example - Actions");
    Engine::Core::runGame(&game);

    return 0;
}
