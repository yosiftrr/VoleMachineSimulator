#ifndef REGISTER_H
#define REGISTER_H

class Register {
private:
    int registerNumber;
    int value;

public:
    Register(int number, int initialValue = 0);

    int getRegisterNumber() const;

    int getValue() const;

    void setValue(int newValue);
};

#endif