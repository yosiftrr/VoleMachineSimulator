#include "Memory.h"
#include <stdexcept>

Memory::Memory() {
    clear();
}

int Memory::getCell(int address) const {
    if (address < 0 || address >= 256) {
        throw std::out_of_range("Invalid memory address");
    }

    return cells[address];
}

void Memory::setCell(int address, int value) {
    if (address < 0 || address >= 256) {
        throw std::out_of_range("Invalid memory address");
    }

    if (value < 0 || value > 255) {
        throw std::out_of_range("Invalid memory value");
    }

    cells[address] = value;
}

void Memory::clear() {
    for (int i = 0; i < 256; i++) {
        cells[i] = 0;
    }
}