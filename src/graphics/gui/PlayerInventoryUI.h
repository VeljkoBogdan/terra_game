#pragma once

#include "raylib.h"
#include "graphics/gui/InventoryUI.h"
#include "core/inventory/PlayerInventory.h"

class PlayerInventoryUI : public InventoryUI {
public:
    PlayerInventoryUI(PlayerInventory* playerInventory) : InventoryUI(playerInventory) {}

    void render() override;
    void update() override;
private:
    Vector2 position = {10, 10};
    int columns = 9;
    int rows = 4;
};