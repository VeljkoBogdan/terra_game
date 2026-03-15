#include "textureAtlas.h"

void TextureAtlas::setTexture(const Texture2D &texture) {
    this->texture = texture;
}

void TextureAtlas::addEntry(const std::string &id, const Rectangle &region) {
    entries[id] = region;
}

void TextureAtlas::unload() {
    UnloadTexture(texture);
}

const Rectangle TextureAtlas::getRegion(std::string textureID) const{
    auto entry = entries.find(textureID);
    if (entries.end() == entry) {
        throw std::runtime_error("Texture Atlas: Region not found for ID: " + textureID);
    }
    return entry->second;
}
