/*
 * main.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <string>

#include "system.hpp"


int main()
{
    System system{};
    while (system.isRunning())
    {
        std::cout << "Please select an option: " << std::endl;
        std::cout << "A: Add matrix to system." << std::endl;
        std::cout << "B: Perform computation." << std::endl;
        std::cout << "C: View matrices." << std::endl;
        std::cout << "D: Exit." << std::endl;
        std::string option;
        std::cin >> option;
        std::cout << std::endl << std::endl;

        if (option == "A")
        {
            // Plan:
            // Option 1) user wants to enter matrix
            // - enter number of rows, columns, name of matrix
            // - enter matrix row by row and store in Matrix object
            int m = 0;
            int n = 0;
            std::string name;
            std::cout << "Enter the matrix name: " << std::endl;
            std::cin >> name;
            std::cout << "Enter the number of rows: " << std::endl;
            std::cin >> m;
            std::cout << "Enter the number of columns: " << std::endl;
            std::cin >> n;
            std::cin.ignore(256, '\n');

            system.addMatrix(name, m, n);
        }
        else if (option == "B")
        {
            // Option 2) user wants to compute
            // - enter operation
            // - parse entered operation and display result/errors
            std::cout << "Not currently supported." << std::endl;
        }
        else if (option == "C")
        {
            system.printSystem();
        }
        else if (option == "D")
        {
            system.setRunning(false);
        }
    }
    exit(0);
}
