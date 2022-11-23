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

   /**
    * Every game must implement this method. It creates the Scene which forms the graphical foundation for our game.
    * A scene is basically like one or more pieces of paper (called layers in the engine) which will be displayed on top of each other.
    * All objects you create can be added to one of the scenes layers, and will automatically be drawn when the layer is drawn.
    */
   std::shared_ptr<Engine::Scene> createScene() override
   {

       // First tell the texture cache to load the slime texture

       Core::textureCache()->loadTexture("resources/slime.png","slime");

       // Then create a scene with a single layer

       auto scene = std::make_shared<Scene>();
       scene->addLayer(FOREGROUND_LAYER);

       // Create animation preset and add it to AnimationManager. When added there, all sprites can easily access it.

       auto anim = SpriteAnimation();
       anim.textureId = "slime";
       anim.direction = AnimationDirection::Forward;
       anim.ticksPrFrame = 100;
       anim.generateFrames(3,0,0,16,14);
       anim.type = AnimationType::PingPong;
       Core::animationManager()->addAnimationPreset("slime_animation",anim);

       // And last, create a sprite using the texture we loaded earlier, and sets its position to the center of the window.

       slime = Sprite::createWithAnimation("slime_animation");
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

   };

 private:

   Engine::SpritePtr slime;

   static constexpr int FOREGROUND_LAYER = 10;
};


int main()
{
   ExampleGame game;

   Engine::Core::createWindowAndRenderer(320,200,3,false,"Example - Animation");
   Engine::Core::runGame(&game);

   return 0;
}