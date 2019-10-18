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
        std::cout << std::endl << std::endl;
        std::cout << "=============================================================" << std::endl;
        std::cout << "Please select an option: " << std::endl;
        std::cout << "A: Add matrix to system." << std::endl;
        std::cout << "B: Perform computation." << std::endl;
        std::cout << "C: View matrices." << std::endl;
        std::cout << "D: Exit." << std::endl << std::endl;
        std::string option;
        std::cin >> option;;
        std::cout << "=============================================================" << std::endl;
        std::cout << std::endl << std::endl;

        std::cin.ignore(256, '\n');
        if (option == "A")
        {
            int m = 0;
            int n = 0;
            std::string name;
            std::cout << "Enter the matrix name: " << std::endl;
            std::cin >> name;
            std::cout << std::endl << "Enter the number of rows: " << std::endl;
            std::cin >> m;
            std::cout << std::endl << "Enter the number of columns: " << std::endl;
            std::cin >> n;
            std::cout << std::endl << std::endl;

            std::cin.ignore(256, '\n');

            system.addMatrix(name, m, n);
        }
        else if (option == "B")
        {
            std::cout << "Only addition is currently supported." << std::endl << std::endl;
            system.parseComputation();
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
