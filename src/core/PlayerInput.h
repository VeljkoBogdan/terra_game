#pragma once

#include "raylib.h"
#include "world/player.h"

class PlayerInput {
public:
    PlayerInput(Player& player);
    void update();
private:
    Player* player;
};