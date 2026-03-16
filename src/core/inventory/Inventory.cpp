#include "Inventory.h"

Inventory::Inventory(int size) {
    slots.resize(size);
}

int Inventory::getSize() const {
    return slots.size();
}

Slot &Inventory::getSlot(int index) {
    return slots.at(index);
}

bool Inventory::addItem(ItemStack stack) {
    return false;
}
