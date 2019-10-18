/*
 * system.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "system.hpp"

#include <utility>
#include <iostream>
#include <cctype>
#include <vector>


System::System() {};
System::~System() {};

void System::addMatrix(const std::string& key, int rows, int columns)
{
   Matrix mat{rows, columns};
   mat.init(); 
   
   // mat.print();
   
   matrices.insert(std::make_pair(key, mat)); 
}

void System::parseComputation()
{
    std::string computation;
    std::getline(std::cin, computation, '\n');
    std::vector<std::string> keys;
    for (auto& c : computation)
    {
        std::string s(1, c);
        if (std::isalpha(c))
        {
            if (matrices.count(s) > 0)
            {
                keys.push_back(s);
            }
            else
            {
                std::cout << "Matrix " << c << " does not exist!" << std::endl;
                return;
            }
        }
        else if ((std::isdigit(c)) || (s == "+") || (s == "+") || (s == "*") || (s == "/"))
        {
            keys.push_back(s);
        }
        if (keys.size() == 3)
        {
            break;
        }
    }

    if (keys[1] == "+")
    {
        addMatrices(keys[0], keys[2]);
    }
    else if (keys[1] == "-")
    {
        std::cout << "Not supported." << std::endl;
    }
    else if (keys[1] == "*")
    {
        std::cout << "Not supported." << std::endl;
    }
    else if (keys[1] == "/")
    {
        std::cout << "Not supported." << std::endl;
    }
    else
    {
        std::cout << "Unsupported operation." << std::endl;
    }
}

void System::addMatrices(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = matrices.find(key_1)->second;
    Matrix matrix_2 = matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        std::cout << "The matrices entered do not have the same dimensions!" << std::endl;
        return;
    }

    Eigen::MatrixXd matrix_3 = matrix_1.getMatrix() + matrix_2.getMatrix();
    std::cout << std::endl << matrix_3 << std::endl << std::endl;
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

