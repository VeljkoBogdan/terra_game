#include "world.h"

World::World() {
    worldGenerator = WorldGenerator();
}

void World::generateWorld(const TextureAtlas& atlas) {
    tiles = worldGenerator.generateWorld(1234u, atlas);
}