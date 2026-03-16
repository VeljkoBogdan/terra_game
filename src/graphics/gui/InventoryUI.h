#pragma once

#include "core/inventory/Inventory.h"

class InventoryUI {
public:
    InventoryUI(Inventory* inventory) : inventory(inventory) {} ;

    virtual void render() = 0;
    virtual void update() = 0;
protected:
    Inventory* inventory;
};