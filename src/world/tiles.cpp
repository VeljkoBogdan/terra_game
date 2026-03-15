#include "tiles.h"

#include "tileRegistry.h"

void Tiles::init() {
    TileDef air {
        .id = "air",
        .solid = false,
        .breakable = false
    };

    TileDef dirt {
        .id = "dirt",
        .solid = true,
        .breakable = true
    };

    TileDef stone {
        .id = "stone",
        .solid = true,
        .breakable = true
    };

    TileDef grass {
        .id = "grass",
        .solid = true,
        .breakable = true
    };

    TileRegistry::get().registerTile(air);
    TileRegistry::get().registerTile(dirt);
    TileRegistry::get().registerTile(stone);
    TileRegistry::get().registerTile(grass);
}