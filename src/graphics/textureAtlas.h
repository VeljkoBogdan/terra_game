#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <iostream>

class TextureAtlas {
public:
    void setTexture(const Texture2D& texture);
    void addEntry(const std::string& id, const Rectangle& region);
    const Texture2D& getTexture() const { return texture; };
    void unload();
    const Rectangle getRegion(std::string textureID) const;
private:
    Texture2D texture;
    std::unordered_map<std::string, Rectangle> entries;
};