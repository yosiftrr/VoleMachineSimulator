#include "CPU.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstdint>

// Convert an 8-bit floating-point pattern to a number
double decodeFloat8(int bits) {
    int sign = (bits >> 7) & 1;
    int exponent = (bits >> 4) & 7;
    int mantissa = bits & 15;

    if (exponent == 0)
        return 0.0;

    double value = (1.0 + mantissa / 16.0)
                   * std::pow(2.0, exponent - 3);

    return sign ? -value : value;
}

// Convert a number to our 8-bit floating-point format
int encodeFloat8(double value) {
    if (value == 0.0)
        return 0;

    int sign = value < 0 ? 1 : 0;

    value = std::abs(value);

    int exponent;
    double fraction = std::frexp(value, &exponent);

    fraction *= 2.0;
    exponent--;

    int exponentBits = exponent + 3;

    if (exponentBits < 1)
        return 0;

    if (exponentBits > 7)
        return (sign << 7) | 0x7F;

    int mantissa = static_cast<int>(
        std::round((fraction - 1.0) * 16.0)
    );

    if (mantissa == 16) {
        mantissa = 0;
        exponentBits++;

        if (exponentBits > 7)
            return (sign << 7) | 0x7F;
    }

    return (sign << 7) |
           (exponentBits << 4) |
           mantissa;
}

CPU::CPU() {
    for (int i = 0; i < 16; i++) {
        registers.emplace_back(i, 0);
    }

    programCounter = 0;
    instructionRegister = 0;
    halted = false;
}

Register& CPU::getRegister(int index) {
    if (index < 0 || index >= 16)
        throw std::out_of_range("Invalid register");

    return registers[index];
}

Memory& CPU::getMemory() {
    return memory;
}

int CPU::getProgramCounter() const {
    return programCounter;
}

void CPU::setProgramCounter(int address) {
    if (address < 0 || address >= 256)
        throw std::out_of_range("Invalid address");

    programCounter = address;
}

bool CPU::isHalted() const {
    return halted;
}

void CPU::halt() {
    halted = true;
}

void CPU::executeInstruction(int instruction) {

    int opcode = (instruction >> 12) & 0xF;
    int R = (instruction >> 8) & 0xF;
    int X = (instruction >> 4) & 0xF;
    int Y = instruction & 0xF;

    int XY = instruction & 0xFF;

    switch (opcode) {

        // LOAD from memory
        case 1:
            registers[R].setValue(memory.getCell(XY));
            break;

        // LOAD immediate value
        case 2:
            registers[R].setValue(XY);
            break;

        // STORE
        case 3:
            if (XY == 0xFF) {
                std::cout << static_cast<char>(
                    registers[R].getValue()
                );
            }
            else {
                memory.setCell(XY, registers[R].getValue());
            }
            break;

        // MOVE
        case 4:
            if (R == 0) {
                registers[Y].setValue(
                    registers[X].getValue()
                );
            }
            break;

        // ADD integer values
        case 5: {
            int a = registers[X].getValue();
            int b = registers[Y].getValue();

            int result = a + b;

            registers[R].setValue(result & 0xFF);
            break;
        }

        // ADD floating-point values
        case 6: {
            double a = decodeFloat8(
                registers[X].getValue()
            );

            double b = decodeFloat8(
                registers[Y].getValue()
            );

            double result = a + b;

            registers[R].setValue(
                encodeFloat8(result)
            );

            break;
        }

        // OR
        case 7:
            registers[R].setValue(
                registers[X].getValue() |
                registers[Y].getValue()
            );
            break;

        // AND
        case 8:
            registers[R].setValue(
                registers[X].getValue() &
                registers[Y].getValue()
            );
            break;

        // XOR
        case 9:
            registers[R].setValue(
                registers[X].getValue() ^
                registers[Y].getValue()
            );
            break;

        // ROTATE RIGHT
        case 10: {
            int value = registers[R].getValue();

            for (int i = 0; i < Y; i++) {
                value = ((value >> 1) |
                         ((value & 1) << 7));
            }

            registers[R].setValue(value);
            break;
        }

        // JUMP
        case 11:
            if (registers[R].getValue() ==
                registers[0].getValue()) {

                programCounter = XY;
            }
            break;

        // HALT
        case 12:
            halted = true;
            break;

        default:
            throw std::runtime_error("Invalid opcode");
    }
}