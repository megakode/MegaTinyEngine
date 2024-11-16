//
// Created by peter on 25/07/2020.
//

#ifndef SCENE_H
#define SCENE_H

#include "GameObjects/GameObject.h"
#include "GameObjects/Layer.h"
#include <list>
#include <memory>

namespace Engine
{
class Scene
{

  public:
    void addLayer(const std::shared_ptr<Layer> &layer);
    /**
     * Add an empty layer to the scene
     * @param tag Integer used to identify the layer
     * @return Shared pointer to newly created layer
     */
    std::shared_ptr<Layer> addLayer(int tag);

    /**
     * Add an empty layer to the scene
     * @param layerId Integer used to identify the layer
     * @param backgroundColor Color used to fill the entire layer. Note all layers added before this layer will not be visible if the color is fully opaque.
     * @return Shared pointer to newly created layer
     */
    std::shared_ptr<Layer> addLayer(int layerId, ColorRGBA8 backgroundColor);

    /**
     * Add an empty layer to the scene
     * @param layerId Integer used to identify the layer
     * @param backgroundTexture Texture drawn as the layers background
     * @param style Tiling style in which the texture is drawn
     * @return Shared pointer to newly created layer
     */
    std::shared_ptr<Layer> addLayer(int layerId, std::shared_ptr<Texture> backgroundTexture, Layer::BackgroundTextureStyle style);

    /**
     * Add an empty layer ABOVE another layer.
     * @param layerToAddTag Identifier of the new layer to add
     * @param aboveLayerTag Identifier of the layer to add above
     */
    void addLayerAboveLayer(int layerToAddTag, int aboveLayerTag);

    /**
     * Add an empty layer BELOW another layer.
     * @param layerToAddTag Identifier of the new layer to add
     * @param aboveLayerTag Identifier of the layer to add below
     */
    void addLayerBelowLayer(int layerToAddTag, int belowLayerTag);

    /**
     * An a GameObject to a layer.
     * @param object The object to add
     * @param layerTag The identifier of the layer
     */
    void addObjectToLayer(const std::shared_ptr<GameObject> &object, int layerTag);

    void draw(SDL_Renderer *renderer);

    void update(float deltaTime);

    void handleInput(const InputEvent &event);

  private:
    std::list<std::shared_ptr<Layer>> m_layers;
};
} // namespace Engine

#endif // SCENE_H
