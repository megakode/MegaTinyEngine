//
// Created by Peter Bone on 24/06/2020.
//
#include "Vendor/json.hpp"
#include "ResourceFile.h"

#ifndef SDLTEST_JSONSERIALIZATION_H
#define SDLTEST_JSONSERIALIZATION_H

using nlohmann::json;

namespace Engine
{
    /// Sprite Frame

    void to_json(json& j, const SpriteFrame& frame)
    {
        j = json{{"x", frame.x}, {"y", frame.y}, {"w", frame.w}, {"h", frame.h} };
    }

    void from_json(const json& j, SpriteFrame& frame)
    {
        j.at("x").get_to(frame.x);
        j.at("y").get_to(frame.y);
        j.at("w").get_to(frame.w);
        j.at("h").get_to(frame.h);
    }


    /// Sprite animation

    void to_json(json& j, const SpriteAnimation& spriteAnimation)
    {
        j = json{{"ticksPrFrame", spriteAnimation.ticksPrFrame}, {"type", spriteAnimation.type}, {"direction", spriteAnimation.direction}, {"texture", spriteAnimation.textureId}};

        for( auto& frame : spriteAnimation.frames)
        {
            j["frames"].push_back(frame);
        }

    }

    void from_json(const json& j, SpriteAnimation& sa)
    {
        j.at("ticksPrFrame").get_to(sa.ticksPrFrame);
        j.at("type").get_to(sa.type);
        j.at("direction").get_to(sa.direction);
        j.at("texture").get_to(sa.textureId);
        for( auto& element : j.at("frames") ){
            auto frame = element.get<SpriteFrame>();
            sa.frames.push_back(frame);
        }
        sa.numberOfFrames = sa.frames.size();

    }

    // Font resource definition

    void from_json(const json& j, FontDefinition& font)
    {
        j.at("texture").get_to(font.texture);
        j.at("charWidth").get_to(font.charWidth);
        j.at("charHeight").get_to(font.charHeight);
        j.at("numStyles").get_to(font.numStyles);
    }

}


#endif //SDLTEST_JSONSERIALIZATION_H
