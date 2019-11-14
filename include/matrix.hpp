/*
 * matrix.hpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <Eigen/Dense>
#include <string>
#include <iostream>


/* Matrix wrapper class for Eigen Matrices */
class Matrix 
{
    public:
        /* Construct matrix with n rows, m columns. */
        Matrix(int rows, int columns);
        /* Copy constructor. */
        Matrix(const Matrix& obj);

        /* Initialize Eigen Matrix member given user. */
        void init();

        /* Get reference to internal matrix. */
        Eigen::MatrixXd& getMatrix();
        /* Print matrix. */
        void print();
        /* Get number of rows in matrix. */
        int getRows();
        /* Get number of columns in matrix. */
        int getColumns();
        /* Set internal matrix to new Eigen matrix. */
        void setMatrix(Eigen::MatrixXd& new_matrix);

        /* Operator Overloads*/
        /* Matrix + Matrix*/
        Matrix& operator + (Matrix& obj)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() + obj.getMatrix();
            return res;
        }

        /* Matrix - Matrix*/
        Matrix& operator - (Matrix& obj)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() - obj.getMatrix();
            return res;
        }

        /* Matrix * Matrix*/
        Matrix& operator * (Matrix& obj)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() * obj.getMatrix();
            return res;
        }

        /* Matrix * Scalar*/
        Matrix& operator * (int& val)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() * val;
            return res;
        }

        /* Matrix / Scalar*/
        Matrix& operator / (int& val)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() / val;
            return res;
        }

        /* Matrix Copy*/
        Matrix& operator = (Matrix& obj)
        {
            this->matrix = obj.matrix;
            this->rows = obj.rows;
            this->columns = obj.columns;
            return *this;
        }

    private:
        /* Add row to internal matrix. */
        bool addRow(std::string row, int current_row);

        int rows;                      // Matrix rows
        int columns;                   // Matrix columns
        Eigen::MatrixXd matrix;        // Internal Eigen Matrix
};


#endif /* !MATRIX_HPP */
