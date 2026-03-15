#pragma once

#include "textureAtlas.h"
#include "raylib.h"
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iostream>

class TextureAtlasBuilder {
public:
    TextureAtlas buildAtlas(const std::string& folder);
};