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

Matrix::Matrix(const Matrix& obj)
{
    rows = obj.rows;
    columns = obj.columns;
    matrix = obj.matrix;
}

void Matrix::init()
{
    int current_row = 0;
    for(int i = 0; i < rows; i++)
    {
        std::string row;
        std::getline(std::cin, row, '\n');
        if (addRow(row, current_row))
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

bool Matrix::addRow(std::string row, int current_row)
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

void Matrix::setMatrix(Eigen::MatrixXd& new_matrix)
{
    matrix = new_matrix;
}

const Eigen::MatrixXd& Matrix::getMatrix() const
{
    return matrix;
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getColumns() const
{
    return columns;
}

void Matrix::print() const
{
    std::cout << matrix << std::endl;
}
