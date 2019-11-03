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

        /* Parse user inputted computation. */
        void parseComputation();
        /* Add two matrices. */
        void addMatrices(const std::string& key_1, const std::string& key_2);
        /* Subtract two matrices. */
        void subtractMatrices(const std::string& key_1, const std::string& key_2);
        /* Multiply two matrices. */
        void multiplyMatrices(const std::string& key_1, const std::string& key_2);
        /* Multiply a matrix and scalar. */
        void multiplyByScalar(const std::string& key_1, const std::string& key_2);
        /* Divice a matrix by a scalar. */
        void divideByScalar(const std::string& key_1, const std::string& key_2);

        /* Check if the system is running. */
        bool isRunning();
        /* Set the system to running or not running. */
        void setRunning(bool value);
        /* Print all matrices in the system. */
        void printSystem();

    private:
        bool running = true;                                  // System running boolean
        std::unordered_map<std::string, Matrix> matrices;     // Stored system matrices
};


#endif /* !SYSTEM_HPP */
