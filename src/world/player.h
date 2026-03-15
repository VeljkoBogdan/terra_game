#pragma once

#include "raylib.h"
#include "constants.h"
#include <algorithm>
#include "world.h"
#include "util/TerraMath.cpp"

#include <iostream>

class Player {
public:
    Player();
    Player(World& world);
    void update(float dt);
    void render();

    void tryMine(Vector2 mousePos);
    void tryPlace(Vector2 mousePos);

    Camera2D camera;
private:
    Rectangle hitbox;
    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    bool onGround;
    bool canJump;
    int range;
    double jumpHeight;
    double speed;
    double fallSpeed;

    World* world;
};