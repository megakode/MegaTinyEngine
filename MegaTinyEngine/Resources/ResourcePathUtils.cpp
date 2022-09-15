//
// Created by sbeam on 9/10/22.
//

#include <string>
#include <SDL.h>
#include <iostream>
#include <algorithm>
#include "MegaTinyEngine/Resources/ResourcePathUtils.h"

#ifdef _WIN32
const char PATH_SEP = '\\';
#else
const char PATH_SEP = '/';
#endif

void ResourcePathUtils::convertPathSeparatorsToCurrentPlatform( std::string& input ){
#ifdef _WIN32
    const char FROM = '/';
        const char TO = '\\';
#else
    const char TO = '/';
    const char FROM = '\\';
#endif
    std::replace( input.begin(), input.end(), FROM, TO );
}


std::string ResourcePathUtils::getDirectoryFromFilename( const std::string& path ){

    const size_t lastIndex = path.rfind(PATH_SEP);
    if (std::string::npos != lastIndex)
    {
        return path.substr(0, lastIndex+1); // +1 to include the last path seperator itself
    } else {
        return path;
    }
}


/// Get the resource path
/// \param subDir sub directory from resources
/// \return

std::string ResourcePathUtils::getResourcePath(const std::string &subDir)
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