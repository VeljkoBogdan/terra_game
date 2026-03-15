#pragma once

#include <vector>
#include "raylib.h"
#include "tile.h"
#include <inttypes.h>
#include <string>
#include "textureAtlas.h"
#include "constants.h"
#include <chrono>
#include "world.h"

class TileRenderer {
public:
    TileRenderer(TextureAtlas atlas) : atlas(atlas) {};
    void setWorld(World& world);
    void render(const Camera2D& camera, bool debug);

    //degub
    double totalMs;
    double avgMs;
    double maxMs;
private:
    World* world = nullptr;
    TextureAtlas atlas;
    
};