#pragma once

#include <vector>
#include "tile.h"
#include "util/PerlinNoise.hpp"
#include <iostream>
#include "constants.h"
#include "graphics/textureAtlas.h"

class WorldGenerator {
public:
    WorldGenerator();
    const std::vector<Tile>& generateWorld(unsigned int seed, const TextureAtlas& atlas);
private:
    std::vector<Tile> tiles;
};