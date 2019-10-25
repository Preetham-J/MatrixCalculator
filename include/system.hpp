/*
 * system.hpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "matrix.hpp"

#include <Eigen/Dense>
#include <unordered_map>

class System
{
    public:
        System();
        ~System();
        void addMatrix(const std::string& key, int rows, int columns);

        void parseComputation();
        void addMatrices(const std::string& key_1, const std::string& key_2);
        void subtractMatrices(const std::string& key_1, const std::string& key_2);
        void multiplyMatrices(const std::string& key_1, const std::string& key_2);
        void divideByScalar(const std::string& key_1, const std::string& key_2);

        bool isRunning();
        void setRunning(bool value);
        void printSystem();

    private:
        bool running = true;
        std::unordered_map<std::string, Matrix> matrices;


};

#endif /* !SYSTEM_HPP */
