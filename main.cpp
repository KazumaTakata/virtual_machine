#include <iostream>
#include "./model.hpp"
#include "./eval.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

// global variables {

int *stack = new int[1024];
Registers *registers = new Registers();
vector<int> instructions = {
    PUSH,
    1,
    PUSH,
    3,
    ADD,
    DUP,
    CFUNTION,
    0,
    PUSH,
    10,
    MUL,
    CFUNTION,
    0,
};

// }

void readAssemblyFile()
{
    std::ifstream file("./test/simpleCalc.asm");
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            for (string s; iss >> s;)
            {

                // cout << s;
                // cout << "\n";
            }
            // using printf() in all tests for consistency
        }
        file.close();
    }
}

int main()
{
    initRegisters(registers);
    readAssemblyFile();

    bool stop = false;
    while (!stop)
    {
        eval();

        if (registers->ip >= instructions.size())
        {
            stop = true;
        }
    }
    return 0;
}