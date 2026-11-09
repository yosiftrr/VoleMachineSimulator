#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    int cells[256];

public:
    Memory();

    int getCell(int address) const;

    void setCell(int address, int value);

    void clear();
};

#endif