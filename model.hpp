#ifndef HMODEL
#define HMODEL

#include <map>
#include <string>
#include <vector>
using namespace std;

enum VALUETYPE
{
    INSTRUCTION,
    STRING,
    INT,
    GOTOADDRESS,
};

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
    JUMP,
    CJUMP,
    DEF_FUNC,
    END,
    CALL,
    RET,
};

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

typedef struct Function
{
    string name;
    int argNum;
    int Address;

} Function;

typedef struct StackFrame
{
    StackFrame *parent;
    Object localStack[1000];
    vector<Object> args;
    map<string, Function> functions;
} StackFrame;

typedef struct StackFramePool
{
    StackFrame *activeStackFrame;
    StackFrame *baseStackFrame;
} StackFramePool;

typedef struct InstructionObj
{
    VALUETYPE type;
    string strValue;
    int intValue;
    INSTRUCTIONSET instruction;

} InstructionObj;

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
    instructionSetMap.insert({"JUMP", JUMP});
    instructionSetMap.insert({"CJUMP", CJUMP});
    instructionSetMap.insert({"DEF_FUNC", DEF_FUNC});
    instructionSetMap.insert({"END", END});
    instructionSetMap.insert({"CALL", CALL});
    instructionSetMap.insert({"RET", RET});
}

enum C_FUNCTION
{
    Cprintln
};

#endif