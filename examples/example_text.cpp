/**
* This example shows how to load a bitmap font and draw text with it
*/

#include "MegaTinyEngine/Core.h"
#include "MegaTinyEngine/IGame.h"
#include "MegaTinyEngine/TextNode.h"

class ExampleGame : public Engine::IGame
{
 public:

   ExampleGame() = default;

   std::shared_ptr<Engine::Scene> createScene() override
   {

       // First tell the texture cache to load the font texture

       auto font_texture = Engine::Core::textureCache()->loadTexture("../examples/resources/big_numbers.png","numbers");

       // Create a scene with a single colored layer

       auto scene = std::make_shared<Engine::Scene>();
       scene->addLayer(FOREGROUND_LAYER,{73,132,205,255});

       // *** Example 1: Create the text object using a font already defined in the FontManager ***

       // The first font added to the font manager becomes the default, and will be used for TextNode instances unless anything else is specified.
       Engine::Core::fontManager()->addFont(Engine::FontDefinition{"numbers",25,32,'0','9'});

       textNodeLeft = Engine::TextNode::createWithDefaultFont();
       textNodeLeft->setLocalPosition(0, 0);
       textNodeLeft->setText("123");
       textNodeLeft->alignment = Engine::TextNodeAlignment::Left;
       scene->addObjectToLayer(textNodeLeft,FOREGROUND_LAYER);

       // *** Example 2: Create the text object directly from a texture ***

       textNodeCenter = Engine::TextNode::createWithTexture("numbers",'0','9',25,32);
       textNodeCenter->setLocalPosition(Engine::Core::getLogicalWindowSize().width/2, Engine::Core::getLogicalWindowSize().height/2-16);
       textNodeCenter->alignment = Engine::TextNodeAlignment::Center;
       scene->addObjectToLayer(textNodeCenter,FOREGROUND_LAYER);

       return scene;
   };

   void update( float deltaTime ) override  {

       static float current_number = 0;

       current_number += deltaTime;

       textNodeCenter->setText(std::to_string((int)current_number));
   };

   void draw( SDL_Renderer *renderer ) override {
       // Empty as we don't need any additional drawing
   };

   void handleInput( const Engine::InputEvent& event ) override {
       // Empty as we don't need any input handling
   };

 private:

   std::shared_ptr<Engine::TextNode> textNodeCenter;
   std::shared_ptr<Engine::TextNode> textNodeLeft;

   static constexpr int FOREGROUND_LAYER = 10;
};


int main()
{
   ExampleGame game;

   Engine::Core::createWindowAndRenderer(320,200,3,false,"Example - Actions");
   Engine::Core::runGame(&game);

   return 0;
}