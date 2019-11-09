/*
 * system.hpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <Eigen/Dense>
#include <unordered_map>
#include "matrix.hpp"


/* Store and perform computations on internal matrices.*/
class System
{
    public:
        /* Construct system. */
        System();
        /* Destruct system. */
        ~System();

        /* Add a matrix to the system. */
        void addMatrix(const std::string& key, int rows, int columns);
        /* Add a matrix to using a generated key (for intermediate matrices in calculations) */ 
        std::string addMatrix(const Matrix& matrix);
        /* Initialize computation parsing and calculating */
        void performComputation();
        /* Calculates end value based on Reverse Polish Notation */
        std::string parseComputation(const std::string& infix);
        /* Implements Shunting-Yard (Reverse Polish Notation) */
        std::string calculate(const std::string& expression);
        /* Add two matrices. */
        std::string add(const std::string& key_1, const std::string& key_2);
        /* Subtract two matrices. */
        std::string subtract(const std::string& key_1, const std::string& key_2);
        /* Multiply two matrices. */
        std::string multiplyMatrices(const std::string& key_1, const std::string& key_2);
        /* Multiply a matrix and scalar. */
        std::string multiplyByScalar(const std::string& key_1, const std::string& key_2);
        /* Divice a matrix by a scalar. */
        std::string divideByScalar(const std::string& key_1, const std::string& key_2);

        /* Check if the system is running. */
        bool isRunning();
        /* Set the system to running or not running. */
        void setRunning(bool value);
        /* Print all matrices in the system. */
        void printSystem();

    private:
        bool running = true;                                  // System running boolean
        std::unordered_map<std::string, Matrix> matrices;     // Stored system matrices
        std::unordered_map<std::string, Matrix> computation_matrices;
};


#endif /* !SYSTEM_HPP */
