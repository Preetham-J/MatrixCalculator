/*
 * matrix.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "matrix.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

Matrix::Matrix(int rows, int columns)
    : rows(rows),
      columns(columns),
      matrix(rows, columns)
{}

void Matrix::init()
{
    for(int i = 0; i < rows; i++)
    {
        std::string row;
        std::getline(std::cin, row, '\n');
        if (addRow(row))
        {
            current_row++;
        }
        else
        {
            i = i - 1;
            std::cout << "Please enter the correct number of items per row!" << std::endl;
        }
    }
}


bool Matrix::addRow(std::string row)
{
    std::istringstream iss(row);
    std::vector<int> tokens;
    int val;
    while (iss >> val)
    {
        tokens.push_back(val);
    }

    if (tokens.size() != columns)
    {
        return false;
    }

    for (int i = 0; i < columns; i++)
    {
        matrix(current_row, i) = tokens[i];
    }

    return true;
}

Eigen::MatrixXd& Matrix::getMatrix()
{
    return matrix;
}

int Matrix::getRows()
{
    return rows;
}

int Matrix::getColumns()
{
    return columns;
}

void Matrix::print()
{
    std::cout << matrix << std::endl;
}
