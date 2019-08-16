#ifndef HSTACK
#define HSTACK

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "./object.hpp"

class Stack
{

public:
    Object *stack;
    int sp;
    Stack(int stacksize)
    {
        stack = new Object[stacksize];
        sp = 0;
    }

    void push(Object obj)
    {
        stack[++sp] = obj;
    }

    Object pop()
    {
        return stack[sp--];
    }
    Object top()
    {
        return stack[sp];
    }
};

#endif