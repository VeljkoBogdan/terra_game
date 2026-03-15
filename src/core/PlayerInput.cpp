#include "PlayerInput.h"

PlayerInput::PlayerInput(Player& player) {
    this->player = &player;
}

void PlayerInput::update() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) player->tryMine(GetMousePosition());
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) player->tryPlace(GetMousePosition());
}
