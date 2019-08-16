#ifndef HOBJECT
#define HOBJECT

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "./model.hpp"

using namespace std;

class Object
{
    VALUETYPE type;
    string strValue;
    int intValue;

public:
    void print()
    {
        if (type == STRING)
        {
            cout << intValue;
        }
        else if (type == INT)
        {
            cout << strValue;
        }
    }
    Object operator+(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            newobj.type = STRING;
            newobj.strValue = strValue + obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue + obj.intValue;
        }

        return newobj;
    }

    Object operator-(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            // newobj.type = STRING;
            // newobj.strValue = strValue - obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue - obj.intValue;
        }

        return newobj;
    }

    Object operator*(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            // newobj.type = STRING;
            // newobj.strValue = strValue + obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue * obj.intValue;
        }

        return newobj;
    }

    Object operator/(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            // newobj.type = STRING;
            // newobj.strValue = strValue + obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue / obj.intValue;
        }

        return newobj;
    }

    Object operator<(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            newobj.type = STRING;
            newobj.strValue = strValue < obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue < obj.intValue;
        }

        return newobj;
    }

    Object operator>(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            newobj.type = STRING;
            newobj.strValue = strValue > obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue > obj.intValue;
        }

        return newobj;
    }

    Object operator<=(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            newobj.type = STRING;
            newobj.strValue = strValue <= obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue <= obj.intValue;
        }

        return newobj;
    }

    Object operator>=(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            newobj.type = STRING;
            newobj.strValue = strValue >= obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue >= obj.intValue;
        }

        return newobj;
    }

    Object operator==(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            newobj.type = STRING;
            newobj.strValue = strValue == obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue == obj.intValue;
        }

        return newobj;
    }

    Object operator&&(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            // newobj.type = STRING;
            // newobj.strValue = strValue && obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue && obj.intValue;
        }

        return newobj;
    }

    Object operator||(Object obj)
    {
        Object newobj = Object();
        if (obj.type == STRING)
        {
            // newobj.type = STRING;
            // newobj.strValue = strValue + obj.strValue;
        }
        else if (obj.type == INT)
        {
            newobj.type = INT;
            newobj.strValue = intValue || obj.intValue;
        }

        return newobj;
    }
};

#endif