#include <iostream>
#include "./model.hpp"
#include "./eval.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "readFile.hpp"

using namespace std;

// global variables {

int *stack = new int[1024];
Registers *registers = new Registers();
vector<int> instructions = {};

// vector<int> instructions = {
//     PUSH,
//     1,
//     PUSH,
//     3,
//     ADD,
//     DUP,
//     CFUNCTION,
//     0,
//     PUSH,
//     10,
//     MUL,
//     CFUNCTION,
//     0,
// };

// }

int main()
{
    initInstructionSetMap();
    initRegisters(registers);
    readAssemblyFile("./test/localvariable.asm");

    StackFrame *globalStackFrame = new StackFrame();
    globalStackFrame->localStack = new int[1024];

    bool stop = false;
    while (!stop)
    {
        eval(globalStackFrame);

        if (registers->ip >= instructions.size())
        {
            stop = true;
        }
    }
    return 0;
}