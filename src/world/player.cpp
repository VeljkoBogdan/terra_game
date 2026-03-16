#include "player.h"

#include "tileRegistry.h"

Player::Player(World &world) {
    this->canJump = false;
    this->onGround = false;
    this->direction = Vector2{0, 0};
    this->jumpHeight = 600.0;
    this->position = Vector2{Constants::WORLD_WIDTH / 2.0f, Constants::WORLD_HEIGHT * 0.7f};
    this->velocity = Vector2{0, 0};
    this->speed = 300.0;
    this->hitbox = Rectangle{position.x, position.y, 16, 32};
    this->fallSpeed = 700.0;
    this->range = 6;

    camera = { 0 };
    camera.zoom = 1.0f;
    camera.target = this->position;
    camera.offset = Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

    this->world = &world;
}

void Player::update(float dt) {
    position.x = hitbox.x;
    position.y = hitbox.y;
    direction.x = 0;
    direction.y = 0;

    // gravity
    if (!onGround) velocity.y = TerraMath::lerp(velocity.y, fallSpeed, 1.0f - pow(0.05f, dt * 0.5f));

    // poll input and set direction
    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;

    // jumping
    if (IsKeyPressed(KEY_SPACE) && canJump) {
        canJump = false;
        onGround = false;
        velocity.y -= jumpHeight;
    }

    // adjust velocity
    velocity.x = direction.x == 0 ? 
        TerraMath::lerp(velocity.x, 0, 1.0f - pow(0.001f, dt * 0.5f)) : 
        TerraMath::lerp(velocity.x, speed * direction.x, 1.0f - pow(0.001f, dt * 0.5f));

    // prevent infinite lerp when stopping
    if (direction.x == 0 && velocity.x <= 30 && velocity.x >= -30) velocity.x = 0;
        
    // y pass
    hitbox.y += velocity.y * dt;
    onGround = false;
    int yTop = (int)hitbox.y / Constants::BLOCK_SIZE - 1;
    int yBot = (int)(hitbox.y + hitbox.height) / Constants::BLOCK_SIZE + 1;
    int yLeft = (int)hitbox.x / Constants::BLOCK_SIZE - 1;
    int yRight = (int)(hitbox.x + hitbox.width) / Constants::BLOCK_SIZE + 1;
    for (int y = yTop; y <= yBot; y++) {
        if (y < 0 || y >= Constants::WORLD_HEIGHT) continue;
        for (int x = yLeft; x <= yRight; x++) {
            if (x < 0 || x >= Constants::WORLD_WIDTH) continue;

            auto& tile = world->tiles[y * Constants::WORLD_WIDTH + x];
            if (!tile.solid) continue;

            // any collision
            if (hitbox.y < (y + 1) * Constants::BLOCK_SIZE && 
                hitbox.y + hitbox.height > y * Constants::BLOCK_SIZE &&
                hitbox.x < (x + 1) * Constants::BLOCK_SIZE && 
                hitbox.x + hitbox.width > x * Constants::BLOCK_SIZE
            ) {
                if (velocity.y > 0) {
                    onGround = true;
                    canJump = true;
                }

                velocity.y = 0;
                hitbox.y = position.y;
            }
        }
    }

    // x pass
    hitbox.x += velocity.x * dt;
    int xTop = (int)hitbox.y / Constants::BLOCK_SIZE - 1;
    int xBot = (int)(hitbox.y + hitbox.height) / Constants::BLOCK_SIZE + 1;
    int xLeft = (int)hitbox.x / Constants::BLOCK_SIZE - 1;
    int xRight = (int)(hitbox.x + hitbox.width) / Constants::BLOCK_SIZE + 1;
    for (int x = xLeft; x <= xRight; x++) {
        if (x < 0 || x >= Constants::WORLD_WIDTH) continue;
        for (int y = xTop; y <= xBot; y++) {
            if (y < 0 || y >= Constants::WORLD_HEIGHT) continue;

            auto& tile = world->tiles[y * Constants::WORLD_WIDTH + x];
            if (!tile.solid) continue;

            // any collision
            if (hitbox.y < (y + 1) * Constants::BLOCK_SIZE && 
                hitbox.y + hitbox.height > y * Constants::BLOCK_SIZE &&
                hitbox.x < (x + 1) * Constants::BLOCK_SIZE && 
                hitbox.x + hitbox.width > x * Constants::BLOCK_SIZE
            ) {
                velocity.x = 0;
                hitbox.x = position.x;
            }
        }
    }

    if (velocity.y > 0) canJump = false;

    position.x = hitbox.x;
    position.y = hitbox.y;
    camera.target = position;
}

void Player::render() {
    DrawRectangle(position.x, position.y, 16, 32, WHITE);
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, GREEN);
}

void Player::tryMine(Vector2 mousePos) {
    Vector2 worldPos = GetScreenToWorld2D(mousePos, camera);
    int tileX = ((int)worldPos.x) / Constants::BLOCK_SIZE;
    int tileY = ((int)worldPos.y) / Constants::BLOCK_SIZE;

    float dist = TerraMath::vector2Dist(position, worldPos);
    if (dist < range * Constants::BLOCK_SIZE) {
        world->tiles[tileY * Constants::WORLD_WIDTH + tileX] = Tile{};
    }
}

void Player::tryPlace(Vector2 mousePos) {
    Vector2 worldPos = GetScreenToWorld2D(mousePos, camera);
    int tileX = ((int)worldPos.x) / Constants::BLOCK_SIZE;
    int tileY = ((int)worldPos.y) / Constants::BLOCK_SIZE;

    float dist = TerraMath::vector2Dist(position, worldPos);
    if (dist < range * Constants::BLOCK_SIZE) {
        world->tiles[tileY * Constants::WORLD_WIDTH + tileX] = Tile::of(TileRegistry::get().getTile("stone"));
    }
}
