#pragma once

#include <cmath>
#include "raylib.h"

class TerraMath {
public:
    static float lerp(const float& from, const float& to, const float& step) {
        return from + step * (to - from);
    }

    static float vector2Dist(const Vector2& first, const Vector2& second) {
        return fabs(sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2)));
    }
};