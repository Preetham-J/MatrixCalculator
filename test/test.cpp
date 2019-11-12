/*
 * test.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "gtest/gtest.h"
#include "matrix.hpp"

TEST(MatrixConstructorTest, testRowsColumns)
{
    Matrix test_matrix(3, 3);
    ASSERT_EQ(test_matrix.getRows(), 3);
    ASSERT_EQ(test_matrix.getColumns(), 3);
}

TEST(MatrixConstructorTest, testRowsColumnsZero)
{
    Matrix test_matrix(0, 0);
    ASSERT_EQ(test_matrix.getRows(), 0);
    ASSERT_EQ(test_matrix.getColumns(), 0);
}
