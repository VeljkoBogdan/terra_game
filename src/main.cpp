#include "raylib.h"
#include "resource_dir.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "world.h"
#include "graphics/textureAtlasBuilder.h"
#include "graphics/tileRenderer.h"
#include "world/tiles.h"
#include "world/player.h"
#include "core/PlayerInput.h"
#include "world/tileRegistry.h"

int main () {
	SetConfigFlags(
        // FLAG_VSYNC_HINT | 
        FLAG_WINDOW_HIGHDPI
    );
	InitWindow(1280, 800, "Hello Raylib");
	SearchAndSetResourceDir("resources");

    // Startup
    Tiles::init();
    TextureAtlasBuilder texAtlasBuilder;
    TextureAtlas texAtlas = texAtlasBuilder.buildAtlas("C:\\Users\\pc\\Documents\\raylib\\terra_game\\resources\\textures");
    TileRegistry::get().setAtlas(texAtlas);

    // WorldGen
    World world = World();
    world.generateWorld(texAtlas);

    // End startup
    TileRenderer tileRenderer(texAtlas);
    tileRenderer.setWorld(world);

    Player player = Player(world);
    PlayerInput playerInput = PlayerInput(player);

    bool debug = false;
	// game loop
	while (!WindowShouldClose()) {
        // logic
        float dt = GetFrameTime();

        playerInput.update();
        player.update(dt);

        if (IsKeyPressed(KEY_P)) debug = !debug;

        Vector2 mousePos = GetMousePosition();
        Vector2 worldPos = GetScreenToWorld2D(mousePos, player.camera);
        int tileX = ((int)worldPos.x) / Constants::BLOCK_SIZE;
        int tileY = ((int)worldPos.y) / Constants::BLOCK_SIZE;

        // drawing
		BeginDrawing();
		    ClearBackground(BLACK);
            BeginMode2D(player.camera);
                tileRenderer.render(player.camera, debug);
                player.render();

                // DrawRectangleLines(tileX * Constants::BLOCK_SIZE, tileY * Constants::BLOCK_SIZE, Constants::BLOCK_SIZE, Constants::BLOCK_SIZE, BLUE);
            EndMode2D();

            player.inventoryUI.render();

            // debug
            if (debug) {
                DrawText(TextFormat("Total Render Time: %.2f ms", tileRenderer.totalMs), 5, 30, 12, GREEN);
                // DrawText(TextFormat("Highest Tile Time: %.3f ms", tileRenderer.maxMs), 5, 50, 12, GREEN);
                // DrawText(TextFormat("Average Tile Time: %.5f ms", tileRenderer.avgMs), 5, 70, 12, GREEN);

                // FPS
                const char* fps = TextFormat("FPS: %d", GetFPS());
                DrawText(fps, 10, 10, 12, GREEN);
            }

		EndDrawing();
	}

	// cleanup
    texAtlas.unload();

	CloseWindow();
	return 0;
}
