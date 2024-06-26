//
// Created by Peter Bone on 24/06/2020.
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Core.h"
#include "JSONSerialization.h"
#include "ResourceFile.h"
#include "ResourceLoader.h"
#include "ResourcePathUtils.h"
#include "Vendor/json.hpp"

using json = nlohmann::json;

namespace Engine {

/**
 * Loads and parses a JSON file into a ResourceFile struct
 * @param jsonFileName The absolute path for the input JSON file
 * @param resourceFile ResourceFile struct to output to
 * @return
 */
bool ResourceLoader::loadResourceFile(const std::string_view& jsonFileName, ResourceFile& resourceFile)
{
    json json;
    std::filesystem::path jsonFilePath(jsonFileName);
    std::ifstream inputFile(jsonFileName.data());

    if (!inputFile) {
        std::cerr << "could not open JSON file: " << jsonFileName << std::endl;
        assert(0);
        return false;
    }

    try {
        inputFile >> json;
    } catch (json::parse_error& ex) {
        std::cerr << "could not load: " << jsonFileName << std::endl;
        std::cerr << "JSON error:" << ex.what() << std::endl;
        assert(0);

        return false;
    }

    for (auto& element : json.items()) {

        if (element.key() == "animations" && element.value().is_object()) {

            std::cout << "Parsing animations:" << std::endl;

            for (auto& singleAnimationDictionary : element.value().items()) {
                const std::string& animName = singleAnimationDictionary.key();
                SpriteAnimation anim = singleAnimationDictionary.value();
                std::cout << animName << std::endl;
                if (anim.frames.empty()) {
                    std::cerr << "Could not load animation without any frames: " << animName << std::endl;
                    assert(0);
                } else {
                    resourceFile.animations[animName] = anim;
                }
            }
        } else if (element.key() == "textures" && element.value().is_array()) {
            for (auto& textureName : element.value()) {
                resourceFile.textureFileNames.push_back(textureName);
            }
        } else if (element.key() == "fonts") {
            for (auto& singleFontDictionary : element.value().items()) {
                const std::string& fontName = singleFontDictionary.key();
                FontDefinition font = singleFontDictionary.value();

                resourceFile.fontDefinitions.emplace_back(font);
            }
        }
    }

    resourceFile.baseDirectory = jsonFilePath.parent_path();

    return true;
}

bool ResourceLoader::loadResources(const std::string_view& jsonFileName)
{
    ResourceFile resourceFile;

    if (!loadResourceFile(jsonFileName, resourceFile)) {
        return false;
    }

    std::filesystem::path jsonFilePath(jsonFileName);

    // Add loaded data to core managers

    // Textures (including fonts)

    for (auto& texture : resourceFile.textureFileNames) {
        std::filesystem::path relativeFileName(texture);
        std::string absoluteTextureFileName = resourceFile.baseDirectory / relativeFileName;
        Core::textureCache()->loadTexture(absoluteTextureFileName, texture);
    }

    for (auto& fontDef : resourceFile.fontDefinitions) {
        std::filesystem::path relativeFileName(fontDef.texture);
        std::string absoluteTextureFileName = resourceFile.baseDirectory / relativeFileName;
        Core::textureCache()->loadTexture(absoluteTextureFileName, fontDef.texture);
        Core::fontManager()->addFont(fontDef);
    }

    // animations

    for (auto& animation : resourceFile.animations) {
        Core::animationManager()->addAnimationPreset(animation.first, animation.second);
    }

    return true;
}

/// Save animations to filename
/// \param filename
void ResourceLoader::saveAnimations(std::string_view filename)
{

    json j;

    // Animations

    auto presets = Core::animationManager()->getAllPresets();
    json jsonPresets;

    for (auto& preset : presets) {
        jsonPresets[preset.first.data()] = preset.second;
    }

    j["animations"] = jsonPresets;

    // TODO: Textures

    std::ofstream outputFile(filename.data());

    try {
        outputFile << j;
    } catch (json::other_error& error) {
        std::cout << "Error saving json to " << filename << ":" << error.what() << std::endl;
    }

    std::cout << j << std::endl;
}

} // namespace Engine
