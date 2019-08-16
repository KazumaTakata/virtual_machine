#ifndef HREADFILE
#define HREADFILE

#include <iostream>
#include "./model.hpp"
#include "./eval.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <regex>

inline bool isInteger(const std::string &s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

void readAssemblyFile(string filepath)
{
    instructions = {};
    std::ifstream file(filepath);
    regex labelRegex("([a-z]*):");
    map<string, int> labelToLineNumber;
    if (file.is_open())
    {
        std::string line;

        while (getline(file, line))
        {
            istringstream iss(line);
            int col = 0;
            for (string token; iss >> token;)
            {
                smatch m;
                if (col == 0 && regex_search(token, m, labelRegex))
                {
                    string label = m[1];
                    labelToLineNumber.insert({label, instructions.size()});
                }
                else
                {
                    if (instructionSetMap.find(token) != instructionSetMap.end())
                    {
                        InstructionObj obj = InstructionObj();
                        obj.type = INSTRUCTION;
                        obj.instruction = instructionSetMap[token];
                        // found
                        instructions.push_back(obj);
                    }
                    else if (labelToLineNumber.find(token) != labelToLineNumber.end())
                    {
                        int curIndex = instructions.size();
                        int labelIndex = labelToLineNumber[token];
                        int rel = labelIndex - curIndex;
                        InstructionObj obj = InstructionObj();
                        obj.type = GOTOADDRESS;
                        obj.intValue = rel;
                        instructions.push_back(obj);
                    }
                    else
                    {
                        // not found
                        if (isInteger(token))
                        {
                            int instruction = std::stoi(token);
                            InstructionObj obj = InstructionObj();
                            obj.type = INT;
                            obj.intValue = instruction;
                            instructions.push_back(obj);
                        }
                        else
                        {
                            InstructionObj obj = InstructionObj();
                            obj.type = STRING;
                            obj.strValue = token;
                            instructions.push_back(obj);
                        }
                    }
                }

                col++;

                // cout << s;
                // cout << "\n";
            }
            // using printf() in all tests for consistency
        }
        file.close();
    }
}

#endif