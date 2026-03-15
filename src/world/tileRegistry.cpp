#include "tileRegistry.h"

void TileRegistry::registerTile(TileDef definition) {
    registry[definition.id] = definition;
}

const TileDef *TileRegistry::getTile(const std::string &id) const {
    auto it = registry.find(id);
    if (it == registry.end()) return nullptr;
    return &it->second;
}
