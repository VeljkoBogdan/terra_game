#pragma once

#include <unordered_map>
#include <string>
#include "tile.h"
#include "graphics/textureAtlas.h"

class TileRegistry {
public:
    static TileRegistry& get() {
        static TileRegistry instance;
        return instance;
    };
    
    void setAtlas(const TextureAtlas& atlas) { this->atlas = &atlas; }
    const TextureAtlas* getAtlas() const { return atlas; }
    void registerTile(TileDef definition);
    const TileDef* getTile(const std::string& id) const;

private:
    TileRegistry() = default;
    TileRegistry(const TileRegistry&) = delete;
    TileRegistry& operator=(const TileRegistry&) = delete;

    std::unordered_map<std::string, TileDef> registry;
    const TextureAtlas* atlas = nullptr;
};