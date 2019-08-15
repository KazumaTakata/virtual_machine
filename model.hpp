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

typedef struct StackFrame
{
    int *localStack;

} StackFrame;

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
    GT,
    EQ,
    AND,
    OR,
    LE,
    GE,
    LOAD,
    STORE,
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
    instructionSetMap.insert({"EQ", EQ});
    instructionSetMap.insert({"OR", OR});
    instructionSetMap.insert({"AND", AND});
    instructionSetMap.insert({"LE", LE});
    instructionSetMap.insert({"GE", GE});
    instructionSetMap.insert({"LOAD", LOAD});
    instructionSetMap.insert({"STORE", STORE});
}

enum C_FUNCTION
{
    Cprintln
};

#endif