#ifndef HEVAL
#define HEVAL

#include <iostream>
#include "./model.hpp"
#include <vector>

using namespace std;

extern Registers *registers;
extern int *stack;
extern vector<int> instructions;

void evalCFunction(C_FUNCTION cfunctionID)
{
    switch (cfunctionID)
    {
    case Cprintln:
    {
        int popedValue = stack[registers->sp--];
        cout << popedValue;
        cout << "\n";

        break;
    }
    default:
        break;
    }
}

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

void eval()
{
    switch (instructions.at(registers->ip))
    {
    case PUSH:
        registers->ip++;
        registers->sp++;
        stack[registers->sp] = instructions.at(registers->ip);
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
    case DUP:
    {
        int topValue = stack[registers->sp++];
        stack[registers->sp] = topValue;
        break;
    }
    case CFUNCTION:
    {
        registers->ip++;
        C_FUNCTION cfunctionID = (C_FUNCTION)instructions.at(registers->ip);

        evalCFunction(cfunctionID);
    }
    break;
    default:
        break;
    }

    registers->ip++;
}

#endif