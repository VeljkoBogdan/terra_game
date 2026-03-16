#pragma once

#include "ItemStack.h"
#include "Slot.h"
#include <vector>

// handles adding and removing items and holding slots

class Inventory {
public:
    Inventory(int size);
    int getSize() const;
    Slot& getSlot(int index);
    bool addItem(ItemStack stack);
private:
    std::vector<Slot> slots;
};