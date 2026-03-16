#pragma once

#include "Inventory.h"

class PlayerInventory : public Inventory {
public:
    PlayerInventory() : Inventory(9*4) {}
};