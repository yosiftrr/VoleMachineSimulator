#ifndef CPU_H
#define CPU_H

#include "Register.h"
#include "Memory.h"
#include <vector>

class CPU {
private:
    std::vector<Register> registers;
    Memory memory;

    int programCounter;
    int instructionRegister;
    bool halted;

public:
    CPU();

    Register& getRegister(int index);
    Memory& getMemory();

    int getProgramCounter() const;
    void setProgramCounter(int address);

    bool isHalted() const;
    void halt();

    void executeInstruction(int instruction);
};

#endif