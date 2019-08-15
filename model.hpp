#ifndef HMODEL
#define HMODEL

#include <map>
#include <string>
using namespace std;

typedef struct Registers
{
    int sp;
    int ip;
} Registers;

void initRegisters(Registers *registers)
{
    registers->sp = -1;
    registers->ip = 0;
}

enum INSTRUCTIONSET
{
    PUSH,
    ADD,
    SUB,
    MUL,
    DIV,
    DUP,
    CFUNCTION,
    LT,
    GT
};

map<string, INSTRUCTIONSET> instructionSetMap;

void initInstructionSetMap()
{
    instructionSetMap.insert({"PUSH", PUSH});
    instructionSetMap.insert({"ADD", ADD});
    instructionSetMap.insert({"SUB", SUB});
    instructionSetMap.insert({"MUL", MUL});
    instructionSetMap.insert({"DIV", DIV});
    instructionSetMap.insert({"DUP", DUP});
    instructionSetMap.insert({"CFUNCTION", CFUNCTION});
    instructionSetMap.insert({"LT", LT});
    instructionSetMap.insert({"GT", GT});
}

enum C_FUNCTION
{
    Cprintln
};

#endif