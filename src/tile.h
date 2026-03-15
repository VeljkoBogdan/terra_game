#pragma once

#include "raylib.h"
#include <string>

struct TileDef {
    std::string id;
    bool solid = false;
    bool breakable = false;
};

struct Tile {
    std::string blockID = "air";   // air
    std::string wallID = "air";    // no wall
    bool solid = false;
    bool breakable = false;
    Rectangle blockTex = Rectangle{0,0,0,0};
    Rectangle wallTex = Rectangle{0,0,0,0};

    static Tile of(const TileDef* def);
};