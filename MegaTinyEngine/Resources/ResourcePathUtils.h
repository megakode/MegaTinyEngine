//
// Created by sbeam on 9/10/22.
//

#ifndef MEGATINEEDITOR_RESOURCEPATHUTILS_H
#define MEGATINEEDITOR_RESOURCEPATHUTILS_H


class ResourcePathUtils {

public:
    static void convertPathSeparatorsToCurrentPlatform(std::string &input);

    static std::string getDirectoryFromFilename(const std::string &path);

    static std::string getResourcePath(const std::string &subDir = "");

};


#endif //MEGATINEEDITOR_RESOURCEPATHUTILS_H
