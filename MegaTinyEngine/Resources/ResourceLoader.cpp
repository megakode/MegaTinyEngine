//
// Created by Peter Bone on 24/06/2020.
//
#include <string>
#include <fstream>
#include <iostream>

#include "Vendor/json.hpp"
#include "MegaTinyEngine/Core.h"
#include "MegaTinyEngine/Resources/JSONSerialization.h"
#include "MegaTinyEngine/Resources/ResourceFile.h"
#include "MegaTinyEngine/Resources/ResourceLoader.h"
#include "MegaTinyEngine/Animation.h"

using json = nlohmann::json;

namespace Engine {

#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif

    void ResourceLoader::convertPathSeparatorsToCurrentPlatform( std::string& input ){
#ifdef _WIN32
        const char FROM = '/';
        const char TO = '\\';
#else
        const char TO = '/';
        const char FROM = '\\';
#endif
        std::replace( input.begin(), input.end(), FROM, TO );
    }


    std::string ResourceLoader::getDirectoryFromFilename( const std::string& path ){

        const size_t lastIndex = path.rfind(PATH_SEP);
        if (std::string::npos != lastIndex)
        {
            return path.substr(0, lastIndex+1); // +1 to include the last path seperator itself
        } else {
            return path;
        }
    }

    void ResourceLoader::loadFromJSON( std::string jsonFileName )
    {

        json json;
        ResourceFile resourceFile;
        std::string resourceFolder = getResourcePath();

        convertPathSeparatorsToCurrentPlatform(jsonFileName);

        std::ifstream inputFile(resourceFolder + jsonFileName);

        if(!inputFile){
            std::cerr << "could not open JSON file: " << resourceFolder << jsonFileName << std::endl;
            assert(0);
            return;
        }

        try {
            inputFile >> json;
        } catch (json::parse_error& ex) {
            std::cerr << "could not load: " << resourceFolder << jsonFileName << std::endl;
            std::cerr << "JSON error:" << ex.what() << std::endl;
            assert(0);
            return;
        }

        //std::cout << "Loaded JSON: " << json << std::endl;

        std::string jsonFilePath = getDirectoryFromFilename(resourceFolder + jsonFileName);

        for (auto& element : json.items()) {

            if(element.key() == "animations" && element.value().is_object())
            {
                std::cout << "Parsing animations:" << std::endl;

                for( auto& singleAnimationDictionary : element.value().items() )
                {
                    const std::string& animName = singleAnimationDictionary.key();
                    SpriteAnimation anim = singleAnimationDictionary.value();
                    std::cout << animName << std::endl;
                    if(anim.frames.size() == 0){
                        std::cerr << "Could not load animation without any frames: " << animName << std::endl;
                        assert(0);
                    } else {
                        resourceFile.animations[animName] = anim;
                    }

                }
            }
            else if(element.key() == "textures" && element.value().is_array() )
            {
                for( auto& textureName : element.value() ){
                    resourceFile.textureFileNames.push_back(textureName);
                }
            }
        }


        // Add loaded data to core managers

        for( auto& texture : resourceFile.textureFileNames){
            std::string absoluteTextureFileName = jsonFilePath + texture;
            Core::textureCache()->loadTexture(absoluteTextureFileName,texture);
        }

        for( auto& animation : resourceFile.animations){
            Core::animationManager()->addAnimationPreset(animation.first,animation.second);
        }

    }

    /// Save animations to filename
    /// \param filename
    void ResourceLoader::saveAnimations( std::string filename )
    {

        json j;

        // Animations

        auto presets = Core::animationManager()->getAllPresets();
        json jsonPresets;

        for( auto& preset : presets ){
            jsonPresets[preset.first] = preset.second;
        }

        j["animations"] = jsonPresets;

        // TODO: Textures


        std::ofstream outputFile(filename);

        try {
            outputFile << j;
        } catch (json::other_error& error){
            std::cout << "Error saving json to " << filename << ":" << error.what() << std::endl;
        }

        std::cout << j << std::endl;
    }


    /// Get the resource path
    /// \param subDir sub directory from resources
    /// \return

    std::string ResourceLoader::getResourcePath(const std::string &subDir)
    {

        //This will hold the base resource path: /res/
        //We give it static lifetime so that we'll only need to call
        //SDL_GetBasePath once to get the executable path
        static std::string baseRes;
        if (baseRes.empty()){
            //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
            char *basePath = SDL_GetBasePath();
            if (basePath){
                baseRes = basePath;
                SDL_free(basePath);
            }
            else {
                std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
                return "";
            }
            //We replace the last bin/ with res/ to get the the resource path
            //size_t pos = baseRes.rfind("bin");
            //baseRes = baseRes.substr(0, pos) + "Resources" + PATH_SEP;
        }
        //If we want a specific subdirectory path in the resource directory append it to the base path.
        return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
    }

}