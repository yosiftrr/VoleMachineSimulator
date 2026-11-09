#include "Register.h"

Register::Register(int number, int initialValue) {
    registerNumber = number;
    value = initialValue;
}

int Register::getRegisterNumber() const {
    return registerNumber;
}

int Register::getValue() const {
    return value;
}

void Register::setValue(int newValue) {
    value = newValue;
}