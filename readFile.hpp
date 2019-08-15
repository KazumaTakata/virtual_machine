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
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            for (string token; iss >> token;)
            {

                if (instructionSetMap.find(token) == instructionSetMap.end())
                {
                    // not found
                    if (isInteger(token))
                    {
                        int instruction = std::stoi(token);
                        instructions.push_back(instruction);
                    }
                    else
                    {
                        cout << "contain string input";
                    }
                }
                else
                {
                    // found
                    instructions.push_back(instructionSetMap[token]);
                }

                // cout << s;
                // cout << "\n";
            }
            // using printf() in all tests for consistency
        }
        file.close();
    }
}

#endif