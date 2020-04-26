/*
 * test.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "gtest/gtest.h"
#include "matrix.hpp"

/* Constructor */
TEST(ConstructorTest, testRowsColumns)
{
    Matrix test_matrix(3, 3);
    ASSERT_EQ(test_matrix.getRows(), 3);
    ASSERT_EQ(test_matrix.getColumns(), 3);
}

TEST(ConstructorTest, testRowsColumnsZero)
{
    Matrix test_matrix(0, 0);
    ASSERT_EQ(test_matrix.getRows(), 0);
    ASSERT_EQ(test_matrix.getColumns(), 0);
}

/* Copy Constructor */
TEST(CopyConstructorTest, testMatrixCopy)
{
    Eigen::MatrixXd test(2,2);
    test << 0, 0,
            1, 1;
    Matrix test_matrix(2, 2);
    test_matrix.setMatrix(test);

    Matrix copy_matrix(test_matrix);

    ASSERT_EQ(test_matrix, copy_matrix);
}

/* setMatrix */
TEST(SetMatrixTest, testMatrixValues)
{
    Eigen::MatrixXd test(2,2);
    test << 0, 0,
            1, 1;
    Matrix test_matrix(2, 2);
    test_matrix.setMatrix(test);

    ASSERT_EQ(test_matrix.getRows(), 2);
    ASSERT_EQ(test_matrix.getColumns(), 2);
    ASSERT_EQ(test_matrix.getMatrix(), test);
}

/* Matrix Operations (+, -, *, /) */
TEST(MatrixOperations, testMatrixAddition)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd test2(2, 2);
    test2 << 0, 1,
             2, 3;
    Eigen::MatrixXd result(2,2);
    result << 0, 2,
              4, 6;
    Matrix test_matrix1(2,2);
    Matrix test_matrix2(2,2);
    Matrix result_matrix(2,2);

    test_matrix1.setMatrix(test1);
    test_matrix2.setMatrix(test2);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 + test_matrix2, result_matrix);
}

TEST(MatrixOperations, testMatrixAdditionNegatives)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd test2(2, 2);
    test2 << -2, -1,
             -3, -4;
    Eigen::MatrixXd result(2,2);
    result << -2, 0,
              -1, -1;
    Matrix test_matrix1(2,2);
    Matrix test_matrix2(2,2);
    Matrix result_matrix(2,2);

    test_matrix1.setMatrix(test1);
    test_matrix2.setMatrix(test2);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 + test_matrix2, result_matrix);
}

TEST(MatrixOperations, testMatrixSubtraction)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd test2(2, 2);
    test2 << 0, 2,
             1, 1;
    Eigen::MatrixXd result(2,2);
    result << 0, -1,
              1, 2;
    Matrix test_matrix1(2,2);
    Matrix test_matrix2(2,2);
    Matrix result_matrix(2,2);

    test_matrix1.setMatrix(test1);
    test_matrix2.setMatrix(test2);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 - test_matrix2, result_matrix);
}

TEST(MatrixOperations, testMatrixSubtractionNegatives)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd test2(2, 2);
    test2 << 0, -2,
             -1, -1;
    Eigen::MatrixXd result(2,2);
    result << 0, 3,
              3, 4;
    Matrix test_matrix1(2,2);
    Matrix test_matrix2(2,2);
    Matrix result_matrix(2,2);

    test_matrix1.setMatrix(test1);
    test_matrix2.setMatrix(test2);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 - test_matrix2, result_matrix);
}

TEST(MatrixOperations, testMatrixMultiplication)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd test2(2, 2);
    test2 << 0, 2,
             3, 4;
    Eigen::MatrixXd result(2,2);
    result << 3, 4,
              9, 16;
    Matrix test_matrix1(2,2);
    Matrix test_matrix2(2,2);
    Matrix result_matrix(2,2);

    test_matrix1.setMatrix(test1);
    test_matrix2.setMatrix(test2);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 * test_matrix2, result_matrix);
}

TEST(MatrixOperations, testMatrixMultiplicationNegatives)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd test2(2, 2);
    test2 << 0, -2,
             -3, 4;
    Eigen::MatrixXd result(2,2);
    result << -3, 4,
              -9, 8;
    Matrix test_matrix1(2,2);
    Matrix test_matrix2(2,2);
    Matrix result_matrix(2,2);

    test_matrix1.setMatrix(test1);
    test_matrix2.setMatrix(test2);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 * test_matrix2, result_matrix);
}

TEST(MatrixOperations, testMatrixMultiplicationScalar)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd result(2,2);
    result << 0, 2,
              4, 6;
    Matrix test_matrix1(2,2);
    Matrix result_matrix(2,2);

    test_matrix1.setMatrix(test1);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 * 2, result_matrix);
}

TEST(MatrixOperations, testMatrixMultiplicationScalarNegative)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd result(2,2);
    result << 0, -2,
              -4, -6;
    Matrix test_matrix1(2,2);
    Matrix result_matrix(2,2);

    test_matrix1.setMatrix(test1);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 * (-2), result_matrix);
}

TEST(MatrixOperations, testMatrixDivision)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd result(2,2);
    result << 0, 0.5,
              1, 1.5;
    Matrix test_matrix1(2,2);
    Matrix result_matrix(2,2);
    test_matrix1.setMatrix(test1);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 / 2, result_matrix);
}

TEST(MatrixOperations, testMatrixDivisionNegatives)
{
    // Set up computation matrices
    Eigen::MatrixXd test1(2,2);
    test1 << 0, 1,
             2, 3;
    Eigen::MatrixXd result(2,2);
    result << 0, -0.5,
              -1, -1.5;
    Matrix test_matrix1(2,2);
    Matrix result_matrix(2,2);
    test_matrix1.setMatrix(test1);
    result_matrix.setMatrix(result);

    ASSERT_EQ(test_matrix1 / (-2), result_matrix);
}

