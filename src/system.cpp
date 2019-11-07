/*
 * system.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "system.hpp"
#include "parser.hpp"

#include <string>
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
   
   matrices.insert(std::make_pair(key, mat)); 
}

void System::parseComputation()
{
    std::string computation;
    std::getline(std::cin, computation, '\n');
    std::vector<std::string> keys;

    std::string parsed_computation = Parser::parseComputation(computation);
    calculate(parsed_computation);
}

std::string System::calculate(const std::string& expression)
{
    std::istringstream iss(expression);
    std::vector<std::string> stack;
    std::cout << "Input\tOperation\tStack after" << std::endl;
    std::string token;
    while (iss >> token)
    {
        std::cout << token << "\t";
        size_t idx = ops.find(token);
        if (idx == std::string::npos)
        {
            std::cout << "Push\t\t";
            stack.push_back(token);
        }
        else
        {
            std::cout << "Operate\t\t";
            if (stack.empty())
            {
                std::cout << "Empty" << std::endl;
            }
            std::string secondOperand = stack.back();
            stack.pop_back();
            std::string firstOperand = stack.back();
            stack.pop_back();
            if (token == "*")
            {
                if (std::isdigit(firstOperand.data()))
                {
                    if (std::isdigit(secondOperand.data()))
                    {
                        double result = std::stod(firstOperand) * std::stod(secondOperand);
                        stack.push_back(std::to_string(result));
                    }
                    else
                    {
                        stack.push_back(multiplyByScalar(firstOperand, secondOperand));
                    }
                }
                else if (std::isdigit(secondOperand.data()))
                {
                    stack.push_back(multiplyByScalar(secondOperand, firstOperand));
                }
                else
                {
                    stack.push_back(multiplyMatrices(firstOperand, secondOperand));
                }
            }
            else if (token == "/")
            {
                if (std::isdigit(firstOperand.data()) && (std::isdigit(secondOperand.data())))
                {
                    double result = std::stod(firstOperand) / std::stod(secondOperand);
                    stack.push_back(std::to_string(result));
                }
                else
                {
                    stack.push_back(divide(firstOperand, secondOperand));
                }
            }
            else if (token == "-")
            {
                if (std::isdigit(firstOperand.data()) && (std::isdigit(secondOperand.data())))
                {
                    double result = std::stod(firstOperand) - std::stod(secondOperand);
                    stack.push_back(std::to_string(result));
                }
                else
                {
                    stack.push_back(subtract(firstOperand, secondOperand));
                }
            }
            else if (token == "+")
            {
                if (std::isdigit(firstOperand.data()) && (std::isdigit(secondOperand.data())))
                {
                    double result = std::stod(firstOperand) + std::stod(secondOperand);
                    stack.push_back(std::to_string(result));
                }
                else
                {
                    stack.push_back(add(firstOperand, secondOperand));
                }
            }
            // else if (token == "^")
            // {
            //     stack.push_back(firstOperand + secondOperand);
            // }
            else
            {
                std::cerr << "Error" << std::endl;
                std::exit(1);
            }
        }
        std::copy(stack.begin(), stack.end(), std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;
    }
    return stack.back();
}


void System::add(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = matrices.find(key_1)->second;
    Matrix matrix_2 = matrices.find(key_2)->second;

    if ((std::isdigit(*key_1.data())) || (std::isdigit(*key_2.data())))
    {
        std::cout << "Can not add matrices and scalars." << std::endl;
        return;
    }

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        std::cout << "The matrices entered do not have the same dimensions!" << std::endl;
        return;
    }

    Matrix result = matrix_1 + matrix_2;
    result.print();
}

void System::subtract(const std::string& key_1, const std::string& key_2)
{
    if ((std::isdigit(*key_1.data())) || (std::isdigit(*key_2.data())))
    {
        std::cout << "Can not subtract matrices and scalars." << std::endl;
        return;
    }

    Matrix matrix_1 = matrices.find(key_1)->second;
    Matrix matrix_2 = matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        std::cout << "The matrices entered do not have the same dimensions!" << std::endl;
        return;
    }

    Matrix result = matrix_1 + matrix_2;
    result.print();
}

void System::multiplyByScalar(const std::string& key_1, const std::string& key_2)
{
    int multiplier = std::stoi(key_1);
    Matrix matrix = matrices.find(key_2)->second;

    Matrix result = matrix * multiplier;
    result.print();
}

void System::multiplyMatrices(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = matrices.find(key_1)->second;
    Matrix matrix_2 = matrices.find(key_2)->second;

    Matrix result = matrix_1 * matrix_2;
    result.print();
}

void System::divideByScalar(const std::string& key_1, const std::string& key_2)
{
    if ((std::isdigit(*key_1.data())) && (!std::isdigit(*key_2.data())))
    {
        std::cout << "Can not divide scalar by matrix" << std::endl;
        return;
    }
    else if ((!std::isdigit(*key_1.data())) && (!std::isdigit(*key_2.data())))
    {
        std::cout << "Can not divide a matrix by matrix" << std::endl;
        return;
    }
    Matrix matrix = matrices.find(key_1)->second;
    int divisor = std::stoi(key_2);

    Matrix result = matrix / divisor;
    result.print();
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

