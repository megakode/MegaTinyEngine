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

    std::shared_ptr<Engine::Scene> createScene() override
    {

        Core::textureCache()->loadTexture("../examples/resources/slime.png","slime");
        auto top_texture = Core::textureCache()->loadTexture("../examples/resources/sky_top.png","sky_top");
        auto cloud_texture = Core::textureCache()->loadTexture("../examples/resources/sky.png","sky");
        auto hills_texture = Core::textureCache()->loadTexture("../examples/resources/hills.png","hills");
        auto grass_texture = Core::textureCache()->loadTexture("../examples/resources/grass_single.png","grass");

        auto scene = std::make_shared<Scene>();

        // Create a colored background layer.
        scene->addLayer(0, {69,186,230,255});

        // Create a layer with the blue checkered pattern texture at the top of the screen
        scene->addLayer(1, top_texture, Layer::BackgroundTextureStyle::TileHorizontal);

        // Create a layer with the clouds at the bottom of the screen
        cloud_layer = scene->addLayer(2, cloud_texture, Layer::BackgroundTextureStyle::TileHorizontal);
        cloud_layer->setLocalPosition(0, Core::getLogicalWindowSize().height- cloud_texture->getHeight());
        clouds_texture_width = cloud_texture->getWidth();

        // Create a layer with hills
        hills_layer = scene->addLayer(3,hills_texture,Layer::BackgroundTextureStyle::TileHorizontal);
        hills_layer->setLocalPosition(0, Core::getLogicalWindowSize().height- hills_texture->getHeight());
        hills_texture_width = hills_texture->getWidth();

        grass_layer = scene->addLayer(4,grass_texture,Layer::BackgroundTextureStyle::TileHorizontal);
        grass_layer->setLocalPosition(0, Core::getLogicalWindowSize().height- grass_texture->getHeight());
        grass_texture_width = grass_texture->getWidth();

        // Create a layer for adding our sprite(s)
        scene->addLayer(FOREGROUND_LAYER);

        // Create animation preset

        auto anim = SpriteAnimation();
        anim.textureId = "slime";
        anim.direction = AnimationDirection::Forward;
        anim.ticksPrFrame = 100;
        anim.generateFrames(3,0,0,16,14);
        anim.type = AnimationType::PingPong;
        Core::animationManager()->addAnimationPreset(ANIM_SLIME_WALK,anim);

        // Create a sprite using the animation we just created

        slime = Sprite::createWithAnimation(ANIM_SLIME_WALK);
        slime->setLocalPosition(Core::getLogicalWindowSize().width/2, Core::getLogicalWindowSize().height-30);
        scene->addObjectToLayer(slime,FOREGROUND_LAYER);

        return scene;
    };

    void update( float deltaTime ) override  {
        // Scroll the clouds
        static float cloud_scroll = 0;
        cloud_scroll += 0.08;
        if(cloud_scroll >= clouds_texture_width) cloud_scroll = 0;
        cloud_layer->setLocalPosition(-clouds_texture_width+(int)cloud_scroll, cloud_layer->getY());
        // Scroll the hills
        static float hills_scroll = 0;
        hills_scroll += 0.3;
        if(hills_scroll >= hills_texture_width) hills_scroll = 0;
        hills_layer->setLocalPosition(-hills_texture_width+(int)hills_scroll, hills_layer->getY());
        // Scroll the grass
        static float grass_scroll = 0;
        grass_scroll += 0.6;
        if(grass_scroll >= grass_texture_width) grass_scroll = 0;
        grass_layer->setLocalPosition(-grass_texture_width+(int)grass_scroll, grass_layer->getY());
    };

    void draw( SDL_Renderer *renderer ) override {
        // Here we could render additional stuff each frame using the SDL renderer directly.
    };

    void handleInput( const InputEvent& event ) override {
    };

  private:
    static constexpr int FOREGROUND_LAYER = 10;
    static constexpr char ANIM_SLIME_WALK[] = "slime_walk";

    Engine::SpritePtr slime;
    std::shared_ptr<Layer> cloud_layer;
    std::shared_ptr<Layer> hills_layer;
    std::shared_ptr<Layer> grass_layer;
    int clouds_texture_width;
    int hills_texture_width;
    int grass_texture_width;


};


int main()
{
    ExampleGame game;

    Engine::Core::createWindowAndRenderer(320,200,3,false,"MegaTinyEngine Example - Layers");
    Engine::Core::runGame(&game);

    return 0;
}