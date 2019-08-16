#ifndef HEVAL
#define HEVAL

#include <iostream>
#include "./model.hpp"
#include "./object.hpp"
#include <vector>

using namespace std;

extern Registers *registers;
extern Object *Stack;
extern vector<InstructionObj> instructions;
extern StackFramePool stackframepool;

void evalCFunction(C_FUNCTION cfunctionID)
{
    switch (cfunctionID)
    {
    case Cprintln:
    {
        Object popedValue = Stack[registers->sp--];
        popedValue.print();
        cout << "\n";

        break;
    }
    default:
        break;
    }
}

void binaryOp(INSTRUCTIONSET op)
{
    Object pop1 = Stack[registers->sp--];
    Object pop2 = Stack[registers->sp--];

    Object result;
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
    case LT:
        result = pop1 < pop2;
        break;
    case GT:
        result = pop1 > pop2;
        break;
    case LE:
        result = pop1 <= pop2;
        break;
    case GE:
        result = pop1 >= pop2;
        break;
    case EQ:
        result = pop1 == pop2;
        break;
    case AND:
        result = pop1 && pop2;
        break;
    case OR:
        result = pop1 || pop2;
        break;
    default:
        break;
    }
    registers->sp++;
    Stack[registers->sp] = result;
}

void eval(StackFrame *stackFrame)
{

    assert(instructions.at(registers->ip).type == INSTRUCTION);
    switch (instructions.at(registers->ip).instruction)
    {
    case PUSH:
        Stack[++registers->sp] = instructions.at(++registers->ip);
        break;

    case DUP:
    {
        int topValue = Stack[registers->sp++];
        Stack[registers->sp] = topValue;
        break;
    }

    case CFUNCTION:
    {
        C_FUNCTION cfunctionID = (C_FUNCTION)instructions.at(++registers->ip).intValue;
        evalCFunction(cfunctionID);
        break;
    }
    case STORE:
    {
        int offset = instructions.at(++registers->ip).intValue;
        stackFrame->localStack[offset] = Stack[registers->sp--];
        break;
    }
    case LOAD:
    {
        int offset = instructions.at(++registers->ip).intValue;
        Stack[++registers->sp] = stackFrame->localStack[offset];
        break;
    }
    case JUMP:
    {
        int rel = instructions.at(++registers->ip).intValue;
        registers->ip += rel;
    }
    case CJUMP:
    {
        int ifJump = Stack[registers->sp--];
        if (ifJump)
        {
            int rel = instructions.at(++registers->ip).intValue;
            registers->ip += rel;
        }
    }
    case DEF_FUNC:
    {
        string name = instructions.at(++registers->ip).strValue;
        int argNum = instructions.at(++registers->ip).intValue;
        int funcAddress = ++registers->ip;
        Function function = Function();
        function.Address = funcAddress;
        function.argNum = argNum;
        function.name = name;
        stackFrame->functions.insert({name, function});

        bool incre = true;
        while (incre)
        {

            if (instructions.at(registers->ip).type == INSTRUCTION && instructions.at(registers->ip).instruction == END)
            {
                incre = false;
            }
            else
            {
                registers->ip++;
            }
        }
    }

    case CALL:
    {
        string funcName = instructions.at(++registers->ip).strValue;
        Function function = stackFrame->functions[funcName];
        StackFrame *newStackFrame = new StackFrame();
        newStackFrame->parent = stackframepool.activeStackFrame;
        stackframepool.activeStackFrame = newStackFrame;
        int argNum = function.argNum;

        while (argNum)
        {
            Object obj = Stack[registers->sp--];
            newStackFrame->args.push_back(obj);
            argNum--;
        }
    }

    default:
    {
        INSTRUCTIONSET instruction = (INSTRUCTIONSET)instructions.at(registers->ip).instruction;
        binaryOp(instruction);
        break;
    }
    }

    registers->ip++;
}

#endif