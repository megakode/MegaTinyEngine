/**
* This example shows how to load a single non animated texture, and display it on screen.
*/

#include "MegaTinyEngine/Core.h"
#include "MegaTinyEngine/IGame.h"

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

       Engine::Core::textureCache()->loadTexture("resources/slime_single.png","slime");
       Engine::Core::textureCache()->loadTexture("resources/missile.png","missile");

       // Then create a scene with a single layer

       scene = std::make_shared<Engine::Scene>();
       scene->addLayer(FOREGROUND_LAYER_TAG);

       // And last, create a sprite using the texture we loaded earlier, and sets its position to the center of the window.

       slime = Engine::Sprite::createWithTexture("slime");
       slime->setLocalPosition(Engine::Core::getLogicalWindowSize().width/2, Engine::Core::getLogicalWindowSize().height/2);
       slime->collision_mask_bits = 1;

       scene->addObjectToLayer(slime,FOREGROUND_LAYER_TAG);

       return scene;
   };

   void update( float deltaTime ) override  {
       // Here we would update game logic, move stuff around, etc.
       timeSinceLastMissile += deltaTime;

       if(timeSinceLastMissile >= MISSILE_SPAWN_INTERVAL){
           auto missile = Engine::Sprite::createWithTexture("missile");
           missiles.push_back(missile);
           missile->setLocalPosition(Engine::Core::getLogicalWindowSize().width,std::rand() % 200);
           missile->setKinematicsEnabled(true);
           missile->setVelocity({-100.f,0.0f});
           missile->setFriction(1.0f);
           timeSinceLastMissile = 0;
           scene->addObjectToLayer(missile,FOREGROUND_LAYER_TAG);
       }

       auto deletePredicate = [](Engine::SpritePtr& missile){
           if(missile->getLocalPosition().x < 0){
               missile->removeFromParent();
               return true;
           }
           return false;
       };
       missiles.erase(std::remove_if(missiles.begin(),missiles.end(),deletePredicate), missiles.end());

       /*
       auto iterator = missiles.begin();
       while( iterator != missiles.end() ){
           if(iterator->get()->getLocalPosition().x < 0){
               iterator->get()->removeFromParent();
               iterator = missiles.erase(iterator);
           } else {
               iterator++;
           }
       }
*/

       /*
       for( auto &missile : missiles){
            if(missile->getLocalPosition().x < 0){

            }
       }
       */
   };

   void draw( SDL_Renderer *renderer ) override {
       // Here we could render additional stuff each frame using the SDL renderer directly.
   };

   void handleInput( const Engine::InputEvent& event ) override {

   };

private:

   Engine::SpritePtr slime;
   std::vector<Engine::SpritePtr> missiles;
   std::shared_ptr<Engine::Scene> scene;

   float timeSinceLastMissile = 0;

   static constexpr int FOREGROUND_LAYER_TAG = 10;
   static constexpr int MISSILE_SPAWN_INTERVAL = 1.0f;
};


int main()
{
   ExampleGame game;

   Engine::Core::createWindowAndRenderer(320,200,3,false,"Example - Collision");
   Engine::Core::runGame(&game);

   return 0;
}