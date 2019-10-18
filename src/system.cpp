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


bool System::addMatrices(const std::string& key_1, const std::string& key_2)
{
    if ((matrices.count(key_1) < 1) || (matrices.count(key_2) < 1))
    {
        std::cout << "The matrices entered do not exist!" << std::endl;
        return false;
    }

    Matrix matrix_1 = matrices.find(key_1)->second;
    Matrix matrix_2 = matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        std::cout << "The matrices entered do not have the same dimensions!" << std::endl;
        return false;
    }

    Eigen::MatrixXd matrix_3 = matrix_1.getMatrix() + matrix_2.getMatrix();
    std::cout << matrix_3 << std::endl;
    return true;
}

bool System::isRunning()
{
    return running;
}

void System::setRunning(bool value)
{
    running = value;
}

