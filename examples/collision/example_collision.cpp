/**
* This example shows how to load a single non animated texture, and display it on screen.
*/

#include "MegaTinyEngine/Core.h"
#include "MegaTinyEngine/IGame.h"
#include "Scale.h"

class ExampleGame : public Engine::IGame, Engine::ICollisionManagerListener
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
       slime->setLocalPosition(Engine::Core::getLogicalWindowSize().width/2, SPAWN_Y);
       slime->collision_mask_bits = 1;

       scene->addObjectToLayer(slime,FOREGROUND_LAYER_TAG);

       Engine::Core::collisionManager()->addCollider(slime);
       Engine::Core::collisionManager()->setListener(this);

       return scene;
   };

   void update( float deltaTime ) override  {

       timeSinceLastMissile += deltaTime;

       // Spawn new missile

       if(timeSinceLastMissile >= MISSILE_SPAWN_INTERVAL){
           auto missile = Engine::Sprite::createWithTexture("missile");
           missiles.push_back(missile);
           missile->setLocalPosition(Engine::Core::getLogicalWindowSize().width,SPAWN_Y);
           missile->setKinematicsEnabled(true);
           missile->setVelocity({-100.f,0.0f});
           missile->setFriction(1.0f);
           missile->collision_mask_bits = 1;
           missile->collision_group_id = MISSILE_COLLISION_GROUP;
           timeSinceLastMissile = 0;
           scene->addObjectToLayer(missile,FOREGROUND_LAYER_TAG);
           // TODO: Refactor this.. it's a bit tedious for users to have to manually add objects to the collision manager
           Engine::Core::collisionManager()->addCollider(missile);
       }

       // Remove all the missiles going past the screen border

       erase_if(missiles, [](auto missile){
          if(missile->getLocalPosition().x < 0){
              missile->removeFromParent();
              // TODO: Refactor this.. it's a bit tedious for users to have to manually remove objects from the collision manager
              Engine::Core::collisionManager()->removeCollider(missile);
              return true;
          }
          return false;
      });


   };

   void draw( SDL_Renderer *renderer ) override {
       // Here we could render additional stuff each frame using the SDL renderer directly.
   };

   void handleInput( const Engine::InputEvent& event ) override {

   };

   // ICollisionManagerListener

   void collisionManagerDetectedCollisionBetween( const std::shared_ptr<Engine::BoxCollider>& firstObject , const std::shared_ptr<Engine::BoxCollider>& secondObject )
   {
       auto scale = Engine::Actions::Scale::create(slime,1.0f, {1.5f,1.5f},{1.0f,1.0f});
       Engine::Core::actionManager()->addAction(scale);

       if(firstObject->collision_group_id == MISSILE_COLLISION_GROUP){
           Engine::Core::collisionManager()->removeCollider(firstObject);
       }

       if(secondObject->collision_group_id == MISSILE_COLLISION_GROUP){
           Engine::Core::collisionManager()->removeCollider(secondObject);
       }

   };

private:

   Engine::SpritePtr slime;
   std::vector<Engine::SpritePtr> missiles;
   std::shared_ptr<Engine::Scene> scene;

   float timeSinceLastMissile = 0;

   static constexpr int FOREGROUND_LAYER_TAG = 10;
   static constexpr int MISSILE_SPAWN_INTERVAL = 1.0f;
   static constexpr int SPAWN_Y = 100;
   static constexpr int MISSILE_COLLISION_GROUP = 1;
};


int main()
{
   ExampleGame game;

   Engine::Core::createWindowAndRenderer(320,200,3,false,"Example - Collision");
   Engine::Core::runGame(&game);

   return 0;
}