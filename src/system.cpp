/*
 * system.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "system.hpp"
#include "utility.hpp"

#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <stack>


System::System() {};
System::~System() {};

void System::addMatrix(const std::string& key, int rows, int columns)
{
   Matrix mat{rows, columns};
   mat.init(); 
   
   matrices.insert(std::make_pair(key, mat)); 
}

std::string System::addMatrix(const Matrix& matrix)
{
   std::string key = "computed_" + std::to_string(computation_matrices.size() + 1);
   computation_matrices.insert(std::make_pair(key, matrix));
   return key;
}

void System::performComputation()
{
    std::string computation;
    std::getline(std::cin, computation, '\n');
    std::vector<std::string> keys;

    std::string result;
    std::string parsed_computation;
    try
    {
        parsed_computation = parseComputation(computation);
        result = calculate(parsed_computation);
    }
    catch (const Utility::Exception& error)
    {
        std::cout << "Error in computation. Returning." << std::endl;
        return;
    }

    if (std::isdigit(*result.data()))
    {
        std::cout << "Result: " << result << std::endl;
    }
    else
    {
        Matrix matrix = computation_matrices.find(result)->second;
        matrix.print();
    }
}

std::string System::parseComputation(const std::string& infix)
{
    std::stringstream ss;
    std::stack<int> s;
    std::stringstream input(Utility::addSpaces(infix));
    std::string token;
    while (std::getline(input, token, ' '))
    {
        if (token.empty())
        {
            continue;
        }

        char c = token[0];
        size_t idx = Utility::ops.find(c);

        // Check for operator
        if (idx != std::string::npos)
        {
            while (!s.empty())
            {
                int prec2 = s.top() / 2;
                int prec1 = idx / 2;
                if ((prec2 > prec1) || ((prec2 == prec1) && (c != '^')))
                {
                    ss << Utility::ops[s.top()] << ' ';
                    s.pop();
                }
                else
                {
                    break;
                }
            }
            s.push(idx);
        }
        // Check for brackets
        else if (c == '(')
        {
            s.push(-2); // -2 stands for '('
        }
        else if (c == ')')
        {
            // until '(' on stack, pop operators.
            while (s.top() != -2)
            {
                ss << Utility::ops[s.top()] << ' ';
                s.pop();
            }
            s.pop();
        }
        else if (std::isdigit(c))
        {
            ss << token << ' ';
        }
        else
        {
            auto matrix = matrices.find(token);
            if (matrix == matrices.end())
            {
                std::cout << "The matrix entered does not exist." << std::endl;
                return "";
            }
            ss << token << ' ';
        }
    }

    while (!s.empty())
    {
        ss << Utility::ops[s.top()] << ' ';
        s.pop();
    }

    return ss.str();
}
std::string System::calculate(const std::string& expression)
{
    std::istringstream iss(expression);
    std::vector<std::string> stack;
    std::string token;
    computation_matrices = matrices;
    while (iss >> token)
    {
        size_t idx = Utility::ops.find(token);
        if (idx == std::string::npos)
        {
            stack.push_back(token);
        }
        else
        {
            std::string secondOperand = stack.back();
            stack.pop_back();
            std::string firstOperand = stack.back();
            stack.pop_back();
            if (token == "*")
            {
                if (std::isdigit(*firstOperand.data()))
                {
                    if (std::isdigit(*secondOperand.data()))
                    {
                        double result = std::stod(firstOperand) * std::stod(secondOperand);
                        stack.push_back(std::to_string(result));
                    }
                    else
                    {
                        try
                        {
                            stack.push_back(multiplyByScalar(firstOperand, secondOperand));
                        }
                        catch (const Utility::Exception& error)
                        {
                            std::cout << "Exception: " << error.what() << std::endl;
                            throw;
                        }
                    }
                }
                else if (std::isdigit(*secondOperand.data()))
                {
                    try
                    {
                        stack.push_back(multiplyByScalar(secondOperand, firstOperand));
                    }
                    catch (const Utility::Exception& error)
                    {
                        std::cout << "Exception: " << error.what() << std::endl;
                        throw;
                    }
                }
                else
                {
                    try
                    {
                        stack.push_back(multiplyMatrices(firstOperand, secondOperand));
                    }
                    catch (const Utility::Exception& error)
                    {
                        std::cout << "Exception: " << error.what() << std::endl;
                        throw;
                    }
                }
            }
            else if (token == "/")
            {
                if (std::isdigit(*firstOperand.data()) && (std::isdigit(*secondOperand.data())))
                {
                    double result = std::stod(firstOperand) / std::stod(secondOperand);
                    stack.push_back(std::to_string(result));
                }
                else if ((std::isdigit(*firstOperand.data()) && (!std::isdigit(*secondOperand.data()))))
                {
                    throw Utility::Exception("Can not divide scalar by matrix");
                }
                else if ((!std::isdigit(*firstOperand.data())) && (std::isdigit(*secondOperand.data())))
                {
                    throw Utility::Exception("Can not divide a matrix by matrix");
                }
                else
                {
                    throw Utility::Exception("Can not divide a matrix by matrix.");
                }
            }
            else if (token == "-")
            {
                if (std::isdigit(*firstOperand.data()) && (std::isdigit(*secondOperand.data())))
                {
                    double result = std::stod(firstOperand) - std::stod(secondOperand);
                    stack.push_back(std::to_string(result));
                }
                if (std::isdigit(*firstOperand.data()) || (std::isdigit(*secondOperand.data())))
                {
                    throw Utility::Exception("Can not subtract matrices and scalars.");
                }
                else
                {
                    try
                    {
                        stack.push_back(subtract(firstOperand, secondOperand));
                    }
                    catch (const Utility::Exception& error)
                    {
                        std::cout << "Exception: " << error.what() << std::endl;
                        throw;
                    }
                }
            }
            else if (token == "+")
            {
                if (std::isdigit(*firstOperand.data()) && (std::isdigit(*secondOperand.data())))
                {
                    double result = std::stod(firstOperand) + std::stod(secondOperand);
                    stack.push_back(std::to_string(result));
                }
                if (std::isdigit(*firstOperand.data()) || (std::isdigit(*secondOperand.data())))
                {
                    throw Utility::Exception("Can not add matrices and scalars.");
                }
                else
                {
                    try
                    {
                        stack.push_back(add(firstOperand, secondOperand));
                    }
                    catch (const Utility::Exception& error)
                    {
                        std::cout << "Exception: " << error.what() << std::endl;
                        throw;
                    }
                }
            }
            // else if (token == "^")
            // {
            //     stack.push_back(firstOperand + secondOperand);
            // }
            else
            {
                throw Utility::Exception("Unsupported operation or value provided.");
            }
        }
        std::cout << std::endl;
    }
    return stack.back();
}


std::string System::add(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = computation_matrices.find(key_1)->second;
    Matrix matrix_2 = computation_matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        throw Utility::Exception("The matrices entered do not have the same dimensions!");
    }

    return addMatrix(matrix_1 + matrix_2);
}

std::string System::subtract(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = computation_matrices.find(key_1)->second;
    Matrix matrix_2 = computation_matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        throw Utility::Exception("The matrices entered do not have the same dimensions!");
    }

    return addMatrix(matrix_1 - matrix_2);
}

std::string System::multiplyByScalar(const std::string& key_1, const std::string& key_2)
{
    int multiplier = std::stoi(key_1);
    Matrix matrix = computation_matrices.find(key_2)->second;

    return addMatrix(matrix * multiplier);
}

std::string System::multiplyMatrices(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = computation_matrices.find(key_1)->second;
    Matrix matrix_2 = computation_matrices.find(key_2)->second;

    if (matrix_1.getRows() != matrix_2.getColumns())
    {
        throw Utility::Exception("The matrices entered do not have matching row = column dimensions for multiplying!");
    }

    return addMatrix(matrix_1 * matrix_2);
}

std::string System::divideByScalar(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix = computation_matrices.find(key_1)->second;
    int divisor = std::stoi(key_2);

    return addMatrix(matrix / divisor);
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

