#ifndef MACHINE_H
#define MACHINE_H

#include "CPU.h"
#include <vector>

class Machine {
private:
    CPU cpu;

public:
    Machine();

    void loadProgram(const std::vector<int>& program);

    void run();

    CPU& getCPU();
};

#endif