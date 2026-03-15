#pragma once

#include <vector>
#include "tile.h"
#include "constants.h"
#include "world/worldGenerator.h"
#include "constants.h"
#include <iostream>
#include "graphics/textureAtlas.h"

class World {
public:
    World();
    void generateWorld(const TextureAtlas& atlas);

    std::vector<Tile> tiles; // [y * Constants::WORLD_WIDTH + x]
private:
    WorldGenerator worldGenerator;
};