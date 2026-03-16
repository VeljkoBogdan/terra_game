#include "PlayerInventoryUI.h"

#include "constants.h"

void PlayerInventoryUI::render() {
    for (int i = 0; i < this->inventory->getSize(); i++) {
        int x = i % columns;
        int y = i / columns;

        Vector2 slotPos = {
            position.x + x * Constants::SLOT_SIZE + x * 4,
            position.y + y * Constants::SLOT_SIZE + y * 4
        };

        DrawRectangleLines(slotPos.x, slotPos.y, Constants::SLOT_SIZE, Constants::SLOT_SIZE, GRAY);

        // Slot& slot = inventory->getSlot(i);

        // empty check and item render
    }
}

void PlayerInventoryUI::update() {
    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < inventory->getSize(); i++) {

        int x = i % columns;
        int y = i / columns;

        Rectangle rect = {
            position.x + x * Constants::SLOT_SIZE,
            position.y + y * Constants::SLOT_SIZE,
            Constants::SLOT_SIZE,
            Constants::SLOT_SIZE
        };

        if (CheckCollisionPointRec(mouse, rect)) {

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // pick up item
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                // split stack
            }
        }
    }
}
