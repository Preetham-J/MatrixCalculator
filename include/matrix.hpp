/*
 * matrix.hpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <Eigen/Dense>


class Matrix 
{
    public:
        Matrix(int rows, int columns);
        void addRow(string row);

    private:
        Eigen::MatrixXd& matrix;
        
};


#endif /* !MATRIX_HPP */
