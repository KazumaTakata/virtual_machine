#ifndef HMODEL
#define HMODEL

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
    CFUNTION,
};

enum C_FUNCTION
{
    Cprintln
};

#endif