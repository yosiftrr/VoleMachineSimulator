#include <iostream>
#include <vector>
#include <string>
#include "Machine.h"

using namespace std;

int main() {
    Machine machine;
    vector<int> program;

    cout << "===== Vole Machine Simulator =====\n";
    cout << "Enter instructions in hexadecimal.\n";
    cout << "Example: 20A3\n";
    cout << "Enter C000 to finish entering instructions.\n\n";

    string instruction;

    while (true) {
        cout << "Instruction: ";
        cin >> instruction;

        try {
            size_t pos;
            int value = stoi(instruction, &pos, 16);

            if (pos != instruction.length() ||
                value < 0 || value > 0xFFFF) {
                cout << "Invalid instruction!\n";
                continue;
            }

            program.push_back(value);

            if (value == 0xC000) {
                break;
            }
        }
        catch (...) {
            cout << "Invalid hexadecimal input!\n";
        }
    }

    try {cout << "Number of instructions: " << program.size() << endl;
        machine.loadProgram(program);

        cout << "\n===== Program Execution =====\n";

        machine.run();

        cout << "\n===== Program Finished =====\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}