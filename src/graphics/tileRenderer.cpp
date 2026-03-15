#include "tileRenderer.h"
#include <chrono>
#include <algorithm>

void TileRenderer::setWorld(World& world) {
    this->world = &world;
}

void TileRenderer::render(const Camera2D& camera, bool debug) {
    auto startTotal = std::chrono::high_resolution_clock::now();

    Vector2 topLeft  = GetScreenToWorld2D({0, 0}, camera);
    Vector2 botRight = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);

    int startX = std::max((int)(topLeft.x / 16) - 1, 0);
    int startY = std::max((int)(topLeft.y / 16) - 1, 0);
    int endX   = std::min((int)(botRight.x / 16) + 1, Constants::WORLD_WIDTH);
    int endY   = std::min((int)(botRight.y / 16) + 1, Constants::WORLD_HEIGHT);

    const Texture2D& atlasTex = atlas.getTexture();
    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            const Tile& tile = world->tiles[y * Constants::WORLD_WIDTH + x];
            
            if (!tile.blockID.empty())
                DrawTextureRec(atlasTex, tile.blockTex, {x*16.0f, y*16.0f}, WHITE);

            if (!tile.wallID.empty())
                DrawTextureRec(atlasTex, tile.wallTex, {x*16.0f, y*16.0f}, GRAY);
        }
    }

    if (debug) {
        auto endTotal = std::chrono::high_resolution_clock::now();
        totalMs = std::chrono::duration<double, std::milli>(endTotal - startTotal).count();
        // avgMs = count == 0 ? 0 : sumMs / count;
    }
}
