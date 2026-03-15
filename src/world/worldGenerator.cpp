#include "worldGenerator.h"

#include "world/tileRegistry.h"

WorldGenerator::WorldGenerator() {}

const std::vector<Tile>& WorldGenerator::generateWorld(unsigned int seed, const TextureAtlas &atlas)
{
    const int height = Constants::WORLD_HEIGHT;
    const int width = Constants::WORLD_WIDTH;

    std::cout << "Inititalized World Generation" << std::endl; 
    
    std::cout << "Resizing tiles vector" << std::endl;
    tiles.assign(width * height, Tile{});

    std::cout << "Noise world gen started" << std::endl;
    const siv::PerlinNoise::seed_type noise_seed = seed;
    const siv::PerlinNoise perlin { noise_seed };

    const double baseHeight = height * 0.66; // average ground level
    const double frequency = 0.01;           // horizontal scale
    const int octaves = 4;
    const double amplitude = 8.0;            // max vertical variation

    for (int x = 0; x < width; ++x) {
        // noise in range (0, 1) i think
        double noise = perlin.octave1D(x * frequency, octaves);

        // noise to terrain height
        double terrainHeight = baseHeight + noise * amplitude;

        // fill column
        for (int y = (int)terrainHeight; y < height; ++y) {
            tiles[y * width + x] = Tile::of(TileRegistry::get().getTile("stone"));
        }
    }

    std::cout << "World Gen finished" << std::endl;

    return tiles;
}