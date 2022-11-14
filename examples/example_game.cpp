/**
* This example shows how to load a sprite-sheet texture, and create an animated sprite from it.
 */

#include "MegaTinyEngine/Core.h"
#include "MegaTinyEngine/IGame.h"

using namespace Engine;

class ExampleGame : public Engine::IGame
{
  public:

    ExampleGame() = default;

    std::shared_ptr<Engine::Scene> initialize() override
    {

        Core::textureCache()->loadTexture("../examples/resources/slime.png","slime");
        Core::textureCache()->loadTexture("../examples/resources/slime_stand.png","slime_stand");
        auto skytop_texture = Core::textureCache()->loadTexture("../examples/resources/sky_top.png","sky_top");
        auto sky_texture = Core::textureCache()->loadTexture("../examples/resources/sky.png","sky");

        auto scene = std::make_shared<Scene>();
        scene->addBackgroundLayer(0,{69,186,230,255});
        scene->addLayer(1,skytop_texture,Layer::BackgroundTextureStyle::TileHorizontal);
        auto bottom_cloud_layer = scene->addLayer(2,sky_texture,Layer::BackgroundTextureStyle::TileHorizontal);
        bottom_cloud_layer->setLocalPosition(0,Core::getLogicalWindowSize().height-sky_texture->getHeight());

        scene->addLayer(FOREGROUND_LAYER);




        // Create animation presets

        auto anim = SpriteAnimation();
        anim.textureId = "slime";
        anim.direction = AnimationDirection::Forward;
        anim.ticksPrFrame = 100;
        anim.generateFrames(3,0,0,16,14);
        anim.type = AnimationType::PingPong;
        Core::animationManager()->addAnimationPreset(ANIM_SLIME_WALK,anim);

        auto animStand = SpriteAnimation();
        anim.textureId = "slime_stand";
        anim.ticksPrFrame = 500;
        anim.generateFrames(2,0,0,16,14);
        anim.type = AnimationType::Loop;
        Core::animationManager()->addAnimationPreset(ANIM_SLIME_STAND,anim);

        // And last, create a sprite using the texture we loaded earlier, and sets its position to the center of the window.

        slime = Sprite::createWithAnimation(ANIM_SLIME_STAND);
        slime->setLocalPosition(Core::getLogicalWindowSize().width/2, Core::getLogicalWindowSize().height/2);
        scene->addObjectToLayer(slime,FOREGROUND_LAYER);


        return scene;
    };

    void update( float deltaTime ) override  {
        // Here we would update game logic, move stuff around, etc.
    };

    void draw( SDL_Renderer *renderer ) override {
        // Here we could render additional stuff each frame using the SDL renderer directly.
    };

    void handleInput( const InputEvent& event ) override {

        if(event.state == InputKeyState::Pressed)
        {
            slime->setAnimation(ANIM_SLIME_WALK);
        } else if (event.state == InputKeyState::Released){
            slime->setAnimation(ANIM_SLIME_STAND);
        }

    };

  private:

    static constexpr int FOREGROUND_LAYER = 10;
    static constexpr char ANIM_SLIME_WALK[] = "slime_walk";
    static constexpr char ANIM_SLIME_STAND[] = "slime_stand";

    Engine::SpritePtr slime;


};


int main()
{
    ExampleGame game;

    Engine::Core::createWindowAndRenderer(320,200,3,false,"Example - Animation");
    Engine::Core::runGame(&game);

    return 0;
}