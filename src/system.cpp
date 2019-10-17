/*
 * system.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "system.hpp"

#include <utility>
#include <iostream>

System::System() {};
System::~System() {};

void System::addMatrix(const std::string& key, int rows, int columns)
{
   Matrix mat{rows, columns};
   mat.init(); 
   
   // mat.print();
   
   matrices.insert(std::make_pair(key, mat)); 
}

void System::printSystem()
{
    for (auto& elem : matrices)
    {
        std::cout << elem.first << ": " << std::endl;
        elem.second.print();
        std::cout << std::endl;
    }
}

bool System::isRunning()
{
    return running;
}

void System::setRunning(bool value)
{
    running = value;
}

