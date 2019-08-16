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
#include "Stack.hpp"

using namespace std;

// global variables {

Stack *OPstack = new Stack(1024);
Registers *registers = new Registers();
vector<InstructionObj> instructions = {};
StackFramePool stackframepool = StackFramePool();

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
    stackframepool.activeStackFrame = globalStackFrame;
    stackframepool.baseStackFrame = globalStackFrame;

    bool stop = false;
    while (!stop)
    {
        eval(stackframepool.activeStackFrame);

        if (registers->ip >= instructions.size())
        {
            stop = true;
        }
    }
    return 0;
}