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

class Matrix 
{
    public:
        Matrix(int rows, int columns);

        void init();
        bool addRow(std::string row);

        Eigen::MatrixXd& getMatrix();
        void print();
        int getRows();
        int getColumns();
        void setMatrix(Eigen::MatrixXd& new_matrix);
        void setMatrix(Matrix& new_matrix);


        Matrix& operator + (Matrix& obj)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() + obj.getMatrix();
            return res;
        }

        Matrix& operator - (Matrix& obj)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() - obj.getMatrix();
            return res;
        }

        Matrix& operator * (Matrix& obj)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() * obj.getMatrix();
            return res;
        }

        Matrix& operator * (int& val)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() * val;
            return res;
        }

        Matrix& operator / (int& val)
        {
            Matrix& res = *this;
            res.matrix = this->getMatrix() / val;
            return res;
        }

    private:
        int rows;
        int columns;
        Eigen::MatrixXd matrix;

        int current_row = 0;
        
};


#endif /* !MATRIX_HPP */
