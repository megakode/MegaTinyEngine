//
// Created by peter on 25/07/2020.
//

#include "Scene.h"
#include "MegaTinyEngine/GameObjects/Layer.h"

namespace Engine {

std::shared_ptr<Layer> Engine::Scene::addLayer(int layerId, std::shared_ptr<Texture> backgroundTexture, Layer::BackgroundTextureStyle style)
{
    return m_layers.emplace_back(std::make_shared<Layer>(layerId,backgroundTexture,style));
}

std::shared_ptr<Layer> Engine::Scene::addBackgroundLayer( int layerId, ColorRGBA8 backgroundColor )
{
    return m_layers.emplace_front(std::make_shared<Layer>(layerId,backgroundColor));
}

std::shared_ptr<Layer> Engine::Scene::addLayer(int layerId )
{
    return m_layers.emplace_back(std::make_shared<Layer>(layerId));
}

void Engine::Scene::addLayerAboveLayer(int layerToAddTag, int aboveLayerTag)
{
    for(auto iter = m_layers.begin() ; iter != m_layers.end() ; ++iter )
    {
        // If layer matches the id to insert above, or if we reached the topmost layer, insert it here.
        if(iter->get()->layerId == aboveLayerTag || *iter == m_layers.back())
        {
            m_layers.emplace(iter,std::make_shared<Layer>(layerToAddTag));
            return;
        }
    }
}

void Engine::Scene::addLayerBelowLayer(int layerToAddTag, int belowLayerTag)
{
    for(auto iter = m_layers.begin() ; iter != m_layers.end() ; ++iter )
    {
        if(iter->get()->layerId == belowLayerTag || *iter == m_layers.back())
        {
            m_layers.emplace(--iter,std::make_shared<Layer>(layerToAddTag));
            return;
        }
    }
}

void Engine::Scene::addObjectToLayer(const std::shared_ptr<GameObject> &object, int layerId)
{
    for( auto layer : m_layers )
    {
        if( layer->layerId == layerId)
        {
            layer->addChild(object);
            return;
        }
    }
}

void Engine::Scene::draw(SDL_Renderer *renderer)
{
    for( auto layer : m_layers )
    {
        layer->draw(renderer);
    }
}

void Engine::Scene::update(float deltaTime)
{
    for( auto layer : m_layers )
    {
        layer->update(deltaTime);
    }
}

void Engine::Scene::handleInput(const Engine::InputEvent &event)
{
    for( auto reverseIter = m_layers.rbegin() ; reverseIter != m_layers.rend() ; ++reverseIter ){
        if(reverseIter->get()->handleEvent(event)){
            // A layer swallowed the event, stop sending it further
            return;
        }
    }
}


}