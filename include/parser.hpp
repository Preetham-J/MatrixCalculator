/*
 * parser.hpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <stack>

/* Parsing related utility functions.*/
namespace Parser
{
    const std::string ops = "-+/*^";
   
    // Adds spaces to for infix string
    std::string Parser::addSpaces(const std::string& infix)
    {
        std::string output;
        bool add_space = false;
        for (auto& c : infix)
        {
            if (!add_space)
            {
                output += c;
                add_space = true;
            }
            else if (c == ' ')
            {
                output += c;
                add_space = false;
            }
            else
            {
                output += ' ';
                output += c;
            }
        }
        return output;
    }
    
    // Calculates end value based on Reverse Polish Notation
    std::string Parser::parseComputation(const std::string& infix)
    {
        std::stringstream ss;
        std::stack<int> s;
        std::stringstream input(addSpaces(infix));
        std::string token;
        while (std::getline(input, token, ' '))
        {
            if (token.empty())
            {
                continue;
            }
     
            char c = token[0];
            size_t idx = ops.find(c);
     
            // Check for operator
            if (idx != std::string::npos)
            {
                while (!s.empty())
                {
                    int prec2 = s.top() / 2;
                    int prec1 = idx / 2;
                    if ((prec2 > prec1) || ((prec2 == prec1) && (c != '^')))
                    {
                        ss << ops[s.top()] << ' ';
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
                    ss << ops[s.top()] << ' ';
                    s.pop();
                }
                s.pop();
            }
            else
            {
                ss << token << ' ';
            }
        }
     
        while (!s.empty())
        {
            ss << ops[s.top()] << ' ';
            s.pop();
        }
     
        return ss.str();
    }
    
    // Implements Shunting-Yard (Reverse Polish Notation)
    std::string calculate(const std::string& expr)
    {
        std::istringstream iss(expr);
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
                  stack.push_back(firstOperand + secondOperand);
              }
              else if (token == "/")
              {
                  stack.push_back(firstOperand + secondOperand);
              }
              else if (token == "-")
              { 
                  stack.push_back(firstOperand + secondOperand);
              }
              else if (token == "+")
              { 
                  stack.push_back(firstOperand + secondOperand);
              }
              else if (token == "^")
              { 
                  stack.push_back(firstOperand + secondOperand);
              }
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
}

#endif /* !PARSER_HPP */
