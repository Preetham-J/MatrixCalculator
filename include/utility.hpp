/*
 * parser.hpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <exception>
#include <string>

/* Parsing related utility functions.*/
namespace Utility
{
    const std::string ops = "-+/*^";
   
    // Adds spaces to for infix string
    std::string addSpaces(const std::string& infix)
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


    struct Exception : public std::exception
    {
        std::string error;

        Exception(std::string ss) : error(ss) {}

        ~Exception() throw () {}

        const char* what() const throw()
        {
            return error.c_str();
        }
    };
}

#endif /* !PARSER_HPP */
