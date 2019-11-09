/*
 * system.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "system.hpp"
#include "utility.hpp"

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

    std::string parsed_computation = parseComputation(computation);
    if (parsed_computation == "")
    {
        return;
    }
    std::string result = calculate(parsed_computation);
    if (result == "")
    {
        return;
    }
    else if (std::isdigit(*result.data()))
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
    std::cout << "Input\tOperation\tStack after" << std::endl;
    std::string token;
    computation_matrices = matrices;
    while (iss >> token)
    {
        std::cout << token << "\t";
        size_t idx = Utility::ops.find(token);
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
                if (std::isdigit(*firstOperand.data()))
                {
                    if (std::isdigit(*secondOperand.data()))
                    {
                        double result = std::stod(firstOperand) * std::stod(secondOperand);
                        stack.push_back(std::to_string(result));
                    }
                    else
                    {
                        stack.push_back(multiplyByScalar(firstOperand, secondOperand));
                    }
                }
                else if (std::isdigit(*secondOperand.data()))
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
                if (std::isdigit(*firstOperand.data()) && (std::isdigit(*secondOperand.data())))
                {
                    double result = std::stod(firstOperand) / std::stod(secondOperand);
                    stack.push_back(std::to_string(result));
                }
                else if ((std::isdigit(*firstOperand.data()) && (!std::isdigit(*secondOperand.data()))))
                {
                    std::cout << "Can not divide scalar by matrix" << std::endl;
                    return "";
                }
                else if ((!std::isdigit(*firstOperand.data())) && (std::isdigit(*secondOperand.data())))
                {
                    std::cout << "Can not divide a matrix by matrix" << std::endl;
                    return "";
                }
                else
                {
                    std::cout << "Can not divide a matrix by matrix." << std::endl;
                    return "";
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
                    std::cout << "Can not subtract matrices and scalars." << std::endl;
                    return "";
                }
                else
                {
                    stack.push_back(subtract(firstOperand, secondOperand));
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
                    std::cout << "Can not add matrices and scalars." << std::endl;
                    return "";
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


std::string System::add(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = computation_matrices.find(key_1)->second;
    Matrix matrix_2 = computation_matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        std::cout << "The matrices entered do not have the same dimensions!" << std::endl;
        return "";
    }

    return addMatrix(matrix_1 + matrix_2);
}

std::string System::subtract(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = computation_matrices.find(key_1)->second;
    Matrix matrix_2 = computation_matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        std::cout << "The matrices entered do not have the same dimensions!" << std::endl;
        return "";
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
        std::cout << "The matrices entered do not have matching row = column dimensions for multiplying!" << std::endl;
        return "";
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

