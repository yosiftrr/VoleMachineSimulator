#include "Machine.h"
#include <iostream>
#include <stdexcept>

Machine::Machine() {
}

void Machine::loadProgram(const std::vector<int>& program) {
    if (program.size() * 2 > 256) {
        throw std::runtime_error("Program is too large");
    }

    for (int i = 0; i < program.size(); i++) {
        int instruction = program[i];

        int highByte = (instruction >> 8) & 0xFF;
        int lowByte = instruction & 0xFF;

        cpu.getMemory().setCell(i * 2, highByte);
        cpu.getMemory().setCell(i * 2 + 1, lowByte);
    }

    cpu.setProgramCounter(0);
}

void Machine::run() {
    while (!cpu.isHalted()) {

        int pc = cpu.getProgramCounter();

        if (pc < 0 || pc >= 255) {
            throw std::runtime_error("Invalid program counter");
        }

        int highByte = cpu.getMemory().getCell(pc);
        int lowByte = cpu.getMemory().getCell(pc + 1);

        int instruction = (highByte << 8) | lowByte;

        cpu.setProgramCounter(pc + 2);

        cpu.executeInstruction(instruction);
    }
}

CPU& Machine::getCPU() {
    return cpu;
}