#ifndef HEVAL
#define HEVAL

#include <iostream>
#include "./model.hpp"
#include "./object.hpp"
#include "Stack.hpp"
#include <vector>

using namespace std;

extern Registers *registers;
extern Stack *OPstack;
extern vector<InstructionObj> instructions;
extern StackFramePool stackframepool;

void evalCFunction(C_FUNCTION cfunctionID)
{
    switch (cfunctionID)
    {
    case Cprintln:
    {
        Object popedValue = OPstack->pop();
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
    Object pop1 = OPstack->pop();
    Object pop2 = OPstack->pop();

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
    OPstack->push(result);
}

void eval(StackFrame *stackFrame)
{

    assert(instructions.at(registers->ip).type == INSTRUCTION);
    switch (instructions.at(registers->ip).instruction)
    {
    case PUSH:
    {
        InstructionObj instobj = instructions.at(++registers->ip);
        Object obj = Object();
        if (instobj.type == STRING)
        {
            obj.type = STRING;
            obj.strValue = instobj.strValue;
        }
        else if (instobj.type == INT)
        {
            obj.type = INT;
            obj.strValue = instobj.intValue;
        }

        break;
    }
    case DUP:
    {
        Object topValue = OPstack->top();
        OPstack->push(topValue);
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
        stackFrame->localStack[offset] = OPstack->pop();
        break;
    }
    case LOAD:
    {
        int offset = instructions.at(++registers->ip).intValue;
        OPstack->push(stackFrame->localStack[offset]);
        break;
    }
    case JUMP:
    {
        int rel = instructions.at(++registers->ip).intValue;
        registers->ip += rel;
    }
    case CJUMP:
    {
        Object ifJump = OPstack->pop();
        if (ifJump.intValue)
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
            Object obj = OPstack->pop();
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