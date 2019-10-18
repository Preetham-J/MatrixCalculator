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
            std::cout << "Only addition is currently supported." << std::endl;
            std::string matrix_1;
            std::string matrix_2;
            std::cout << "Enter the first matrix to add: " << std::endl;
            std::cin >> matrix_1;
            std::cout << "Enter the second matrix to add: " << std::endl;
            std::cin >> matrix_2;
            std::cin.ignore(256, '\n');
            system.addMatrices(matrix_1, matrix_2);
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
