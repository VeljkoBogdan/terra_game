#include "tile.h"

#include "world/tileRegistry.h"
#include <functional>
#include <iostream>
#include "graphics/textureAtlas.h"

Tile Tile::of(const TileDef *def) {
    if (!def) throw std::runtime_error("Tile Definition does not exist");
    return Tile { 
        .blockID = def->id, 
        .wallID = def->id, 
        .solid = def->solid, 
        .breakable = def->breakable,
        .blockTex = TileRegistry::get().getAtlas()->getRegion(def->id),
        .wallTex = TileRegistry::get().getAtlas()->getRegion(def->id)
    };
}