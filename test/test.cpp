/*
 * test.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "gtest/gtest.h"
#include "matrix.hpp"

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

TEST(CopyConstructorTest, testMatrixCopy)
{
    Matrix test_matrix(2, 2);
    Matrix copy_matrix(test_matrix);
    ASSERT_EQ(test_matrix.getRows(), 2);
    ASSERT_EQ(test_matrix.getColumns(), 2);
}

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

TEST(MatrixOperations, testMatrixAddition)
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







// + Matrix
// - Matrix
// * Matrix
// * Int
// / Int
// = Matrix
