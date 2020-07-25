//
// Created by peter on 25/07/2020.
//

#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <memory>
#include "GameObject.h"
#include "Layer.h"

namespace Engine {
    class Scene {

    public:
        void addLayer( int tag );
        void addLayerAboveLayer( int layerToAddTag , int aboveLayerTag );
        void addLayerBelowLayer( int layerToAddTag , int belowLayerTag );
        void addObjectToLayer( const std::shared_ptr<GameObject>& object , int layerTag );

        void draw( SDL_Renderer *renderer );

        void update( float deltaTime );

        void handleInput( const InputEvent& event );


    private:

        std::list<std::shared_ptr<Layer>> m_layers;

    };
}

#endif //SCENE_H
