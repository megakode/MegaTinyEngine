//
// Created by Peter Bone on 24/06/2020.
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "MegaTinyEngine/Core.h"
#include "MegaTinyEngine/Resources/JSONSerialization.h"
#include "MegaTinyEngine/Resources/ResourceFile.h"
#include "MegaTinyEngine/Resources/ResourceLoader.h"
#include "MegaTinyEngine/Resources/ResourcePathUtils.h"
#include "Vendor/json.hpp"

using json = nlohmann::json;

namespace Engine
{

bool ResourceLoader::loadResourceFile(const std::string &jsonFileName, ResourceFile &resourceFile)
{

    json json;
    std::string resourceFolder = ResourcePathUtils::getResourcePath();

    // ResourcePathUtils::convertPathSeparatorsToCurrentPlatform(fullPath);
    std::filesystem::path jsonFilePath(jsonFileName);
    std::ifstream inputFile(jsonFileName);

    if (!inputFile)
    {
        std::cerr << "could not open JSON file: " << jsonFileName << std::endl;
        assert(0);
        return false;
    }

    try
    {
        inputFile >> json;
    }
    catch (json::parse_error &ex)
    {
        std::cerr << "could not load: " << jsonFileName << std::endl;
        std::cerr << "JSON error:" << ex.what() << std::endl;
        assert(0);

        return false;
    }

    for (auto &element : json.items())
    {

        if (element.key() == "animations" && element.value().is_object())
        {

            std::cout << "Parsing animations:" << std::endl;

            for (auto &singleAnimationDictionary : element.value().items())
            {
                const std::string &animName = singleAnimationDictionary.key();
                SpriteAnimation anim = singleAnimationDictionary.value();
                std::cout << animName << std::endl;
                if (anim.frames.empty())
                {
                    std::cerr << "Could not load animation without any frames: " << animName << std::endl;
                    assert(0);
                }
                else
                {
                    resourceFile.animations[animName] = anim;
                }
            }
        }
        else if (element.key() == "textures" && element.value().is_array())
        {
            for (auto &textureName : element.value())
            {
                resourceFile.textureFileNames.push_back(textureName);
            }
        }
        else if (element.key() == "fonts")
        {
            for (auto &singleFontDictionary : element.value().items())
            {
                const std::string &fontName = singleFontDictionary.key();
                FontDefinition font = singleFontDictionary.value();

                resourceFile.fontDefinitions.emplace_back(font);
            }
        }
    }

    return true;
}

bool ResourceLoader::loadResources(const std::string &jsonFileName)
{
    ResourceFile resourceFile;

    if (!loadResourceFile(jsonFileName, resourceFile))
    {
        return false;
    }

    std::filesystem::path jsonFilePath(jsonFileName);
    std::filesystem::path basePath = jsonFilePath.parent_path();

    // Add loaded data to core managers

    // Textures (including fonts)

    for (auto &texture : resourceFile.textureFileNames)
    {
        std::filesystem::path relativeFileName(texture);
        std::string absoluteTextureFileName = basePath / relativeFileName;
        Core::textureCache()->loadTexture(absoluteTextureFileName, texture);
    }

    for (auto &fontDef : resourceFile.fontDefinitions)
    {
        std::filesystem::path relativeFileName(fontDef.texture);
        std::string absoluteTextureFileName = basePath / relativeFileName;
        Core::textureCache()->loadTexture(absoluteTextureFileName, fontDef.texture);
        Core::fontManager()->addFont(fontDef);
    }

    // animations

    for (auto &animation : resourceFile.animations)
    {
        Core::animationManager()->addAnimationPreset(animation.first, animation.second);
    }
}

/// Save animations to filename
/// \param filename
void ResourceLoader::saveAnimations(std::string filename)
{

    json j;

    // Animations

    auto presets = Core::animationManager()->getAllPresets();
    json jsonPresets;

    for (auto &preset : presets)
    {
        jsonPresets[preset.first] = preset.second;
    }

    j["animations"] = jsonPresets;

    // TODO: Textures

    std::ofstream outputFile(filename);

    try
    {
        outputFile << j;
    }
    catch (json::other_error &error)
    {
        std::cout << "Error saving json to " << filename << ":" << error.what() << std::endl;
    }

    std::cout << j << std::endl;
}

} // namespace Engine