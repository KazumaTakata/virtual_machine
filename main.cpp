#include <iostream>

using namespace std;

typedef struct Registers
{
    int sp;
    int ip;
} Registers;

enum INSTRUCTIONSET
{
    PUSH,
    ADD,
    SUB,
    MUL,
    DIV,
    DEBUG,

};

int *stack = new int[1024];

int instructions[] = {
    PUSH,
    1,
    PUSH,
    3,
    ADD,
    DEBUG,
    PUSH,
    10,
    MUL,
    DEBUG,
};

Registers *registers = new Registers();

void binaryOp(INSTRUCTIONSET op)
{
    int pop1 = stack[registers->sp--];
    int pop2 = stack[registers->sp--];

    int result;
    switch (op)
    {
    case ADD:
        result = pop1 + pop2;
        break;
    case SUB:
        result = pop1 - pop2;
        break;
    case MUL:
        result = pop1 * pop2;
        break;
    case DIV:
        result = pop1 / pop2;
        break;

    default:
        break;
    }
    registers->sp++;
    stack[registers->sp] = result;
}

int main()
{
    registers->sp = -1;
    registers->ip = 0;

    size_t sizeOfInstruction = sizeof(instructions) / sizeof(instructions[0]);

    bool stop = false;
    while (!stop)
    {

        switch (instructions[registers->ip])
        {
        case PUSH:
            registers->ip++;
            registers->sp++;
            stack[registers->sp] = instructions[registers->ip];
            break;
        case ADD:
        {
            binaryOp(ADD);
            break;
        }
        case MUL:
        {
            binaryOp(MUL);
            break;
        }
        case SUB:
        {
            binaryOp(SUB);
            break;
        }
        case DIV:
        {
            binaryOp(DIV);
            break;
        }
        case DEBUG:
        {
            int topValue = stack[registers->sp];
            cout << topValue << "\n";
            break;
        }
        default:
            break;
        }

        registers->ip++;
        if (registers->ip > sizeOfInstruction)
        {
            stop = true;
        }
    }
    return 0;
}