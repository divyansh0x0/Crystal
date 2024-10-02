#include "crystal/geometry/Matrix.h" // Include the appropriate header for the Matrix class
#include <cmath>
#include <gtest/gtest.h>

using namespace crystal::geometry;

// Test the constructors
TEST(MatrixTest, EqualityTest)
{
    Matrix M1 = Matrix({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });
    Matrix M2 = Matrix({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });
    Matrix M3 = Matrix({
        {1, 2,  3},
        {4, 15, 6},
        {7, 8,  9}
    });

    ASSERT_EQ(M1 == M2, true) << "Expected M1 and M2 to be equal.";
    ASSERT_EQ(M1 == M3, false) << "Expected M1 and M3 to be unequal.";
    ASSERT_EQ(M1 != M3, true) << "Expected M1 and M3 to be unequal.";
    ASSERT_EQ(M1 != M2, false) << "Expected M1 and M2 to be equal.";
}

TEST(MatrixTest, AtFunctionTest)
{
    Matrix M1 = Matrix({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });

    // Test valid access
    ASSERT_EQ(M1.at(0, 0), 1) << "Expected M1.at(0, 0) to be 1.";
    ASSERT_EQ(M1.at(2, 2), 9) << "Expected M1.at(2, 2) to be 9.";

    // Test out-of-bounds access (graceful return)
    ASSERT_TRUE(std::isnan(M1.at(3, 3))) << "Expected M1.at(3, 3) to return NaN for out-of-bounds access.";
    ASSERT_TRUE(std::isnan(M1.at(100, 0))) << "Expected M1.at(100, 0) to return NaN for out-of-bounds access.";

    ASSERT_TRUE(std::isnan(M1.at(0, 100))) << "Expected M1.at(0, 100) to return NaN for out-of-bounds access.";
}

TEST(MatrixTest, ConstructorTest)
{
    // Valid initialization
    Matrix M1 = Matrix({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });
    EXPECT_EQ(M1.at(0, 0), 1) << "Expected M1.at(0, 0) to be 1.";
    EXPECT_EQ(M1.at(2, 2), 9) << "Expected M1.at(2, 2) to be 9.";

    // Invalid initialization with nullptr
    float** null_ptr = nullptr;
    Matrix  M3(null_ptr); // Constructor with nullptr
    EXPECT_TRUE(std::isnan(M3.at(0, 0))) << "Expected M3.at(0, 0) to be NaN for nullptr initialization.";
}

TEST(MatrixTest, AdditionTest)
{
    Matrix M1 = Matrix({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });
    Matrix M2 = Matrix({
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    });

    // Valid addition
    Matrix result = M1 + M2;
    EXPECT_EQ(result.at(0, 0), 10) << "Expected result.at(0, 0) to be 10 after addition.";
    EXPECT_EQ(result.at(1, 1), 10) << "Expected result.at(1, 1) to be 10 after addition.";
    EXPECT_EQ(result.at(2, 2), 10) << "Expected result.at(2, 2) to be 10 after addition.";

    // Adding matrices of different sizes (should return NaN)
    Matrix M3             = Matrix({
        {1, 2},
        {3, 4}
    });
    Matrix result_invalid = M1 + M3; // This should be handled in the operator
    EXPECT_TRUE(std::isnan(result_invalid.at(0, 0))) << "Expected result_invalid.at(0, 0) to be NaN for size mismatch.";

    Matrix A = Matrix({
        {1, 2},
        {3, 4}
    });
    Matrix B = Matrix({
        {5, 6},
        {7, 8}
    });
    EXPECT_EQ(A + B, B + A) << "Matrix addition should be commutative.";
}

TEST(MatrixTest, SubtractionTest)
{
    Matrix M1 = Matrix({
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    });
    Matrix M2 = Matrix({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });

    // Valid subtraction
    Matrix result = M1 - M2;
    EXPECT_EQ(result.at(0, 0), 8) << "Expected result.at(0, 0) to be 8 after subtraction.";
    EXPECT_EQ(result.at(1, 1), 0) << "Expected result.at(1, 1) to be 0 after subtraction.";
    EXPECT_EQ(result.at(2, 2), -8) << "Expected result.at(2, 2) to be -8 after subtraction.";

    // Subtracting matrices of different sizes (should return NaN)
    Matrix M3             = Matrix({
        {1, 2},
        {3, 4}
    });
    Matrix result_invalid = M1 - M3; // This should be handled in the operator
    EXPECT_TRUE(std::isnan(result_invalid.at(0, 0))) << "Expected result_invalid.at(0, 0) to be NaN for size mismatch.";


    Matrix A = Matrix({
        {1, 2},
        {3, 4}
    });
    Matrix B = Matrix({
        {5, 6},
        {7, 8}
    });
    EXPECT_EQ(A - B, B - A) << "Matrix subtraction should be commutative.";
}

TEST(MatrixTest, MultiplicationTest)
{
    Matrix M1 = Matrix({
        {1, 2},
        {3, 4}
    });
    Matrix M2 = Matrix({
        {2, 0},
        {1, 2}
    });

    // Valid multiplication
    Matrix result = M1 * M2;
    EXPECT_EQ(result.at(0, 0), 4) << "Expected result.at(0, 0) to be 4 after multiplication.";
    EXPECT_EQ(result.at(0, 1), 4) << "Expected result.at(0, 1) to be 4 after multiplication.";
    EXPECT_EQ(result.at(1, 0), 10) << "Expected result.at(1, 0) to be 10 after multiplication.";
    EXPECT_EQ(result.at(1, 1), 8) << "Expected result.at(1, 1) to be 8 after multiplication.";

    // Invalid multiplication (dimension mismatch)
    Matrix M3 = Matrix({
        {1, 2, 3},
        {4, 5, 6}
    });
    Matrix resultOfM1M3 = Matrix({
        {9,12,15},
        {19,26,33}
    }

    );
    EXPECT_EQ(M1*M3, resultOfM1M3) << "Expected M1*M3 to be resultOfM1M3.";
    // Multiplying matrices of different sizes (should return NaN)
    Matrix result_invalid = M3 * M1; // Should handle size mismatch
    EXPECT_TRUE(std::isnan(result_invalid.at(0, 0))) << "Expected result_invalid.at(0, 0) to be NaN for size mismatch.";

    
}

TEST(MatrixTest, ScalarMultiplicationTest)
{
    Matrix M1     = Matrix({
        {1, 2},
        {3, 4}
    });
    Matrix result = M1 * 2.0f;

    EXPECT_EQ(result.at(0, 0), 2) << "Expected result.at(0, 0) to be 2 after scalar multiplication.";
    EXPECT_EQ(result.at(0, 1), 4) << "Expected result.at(0, 1) to be 4 after scalar multiplication.";
    EXPECT_EQ(result.at(1, 0), 6) << "Expected result.at(1, 0) to be 6 after scalar multiplication.";
    EXPECT_EQ(result.at(1, 1), 8) << "Expected result.at(1, 1) to be 8 after scalar multiplication.";
}

TEST(MatrixTest, ScalarDivisionTest)
{
    Matrix M1 = Matrix({
        {2, 4},
        {6, 8}
    });

    // Valid division
    Matrix result = M1 / 2.0f;
    EXPECT_EQ(result.at(0, 0), 1) << "Expected result.at(0, 0) to be 1 after scalar division.";
    EXPECT_EQ(result.at(0, 1), 2) << "Expected result.at(0, 1) to be 2 after scalar division.";
    EXPECT_EQ(result.at(1, 0), 3) << "Expected result.at(1, 0) to be 3 after scalar division.";
    EXPECT_EQ(result.at(1, 1), 4) << "Expected result.at(1, 1) to be 4 after scalar division.";

    // Division by zero
    Matrix result_invalid = M1 / 0.0f; // Should return NaN
    EXPECT_TRUE(std::isnan(result_invalid.at(0, 0))) << "Expected result_invalid.at(0, 0) to be NaN for division by zero.";
}

TEST(MatrixTest, TransposeTest)
{
    Matrix M1     = Matrix({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });
    Matrix result = M1.getTranspose();
    Matrix expected = Matrix({
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    });

    Matrix M2 = Matrix({
        {4, 5, 6},
        {7, 8, 9}
    });
    Matrix I  = Matrix::identity(5, 5);
    EXPECT_EQ(result, expected) << "Expected result to be the transpose of M1.";
    EXPECT_EQ(M2.getTranspose(), invalid_matrix) << "Expected M2.getTranspose() to return an invalid matrix.";

    EXPECT_EQ(I.getTranspose(), I) << "Expected transpose of identity matrix to be identity matrix.";
}

TEST(MatrixTest, DeterminantTest)
{
    Matrix M1 = Matrix({
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    });
    EXPECT_EQ(M1.getDeterminant(), 1) << "Expected determinant to be 1";

    Matrix M2 = Matrix({
        {1, 2},
        {3, 4}
    });
    EXPECT_EQ(M2.getDeterminant(), -2) << "Expected determinant to be -2.";
}

TEST(MatrixTest, InverseTest)
{
    Matrix M1     = Matrix({
        {4, 7},
        {2, 6}
    });
    Matrix result = M1.getInverse();

    EXPECT_FLOAT_EQ(result.at(0, 0), 0.6) << "Expected result.at(0, 0) to be 0.6 after inversion.";
    EXPECT_FLOAT_EQ(result.at(0, 1), -0.7) << "Expected result.at(0, 1) to be -0.7 after inversion.";
    EXPECT_FLOAT_EQ(result.at(1, 0), -0.2) << "Expected result.at(1, 0) to be -0.2 after inversion.";
    EXPECT_FLOAT_EQ(result.at(1, 1), 0.4) << "Expected result.at(1, 1) to be 0.4 after inversion.";

    // Inverse of a singular matrix
    Matrix M2             = Matrix({
        {1, 2},
        {2, 4}
    });
    Matrix result_invalid = M2.getInverse(); // Should return NaN
    EXPECT_TRUE(std::isnan(result_invalid.at(0, 0))) << "Expected result_invalid.at(0, 0) to be NaN for singular matrix.";
}
TEST(MatrixTest, IdentityMatrixTest)
{
    Matrix identity = Matrix::identity(3, 3); // Assuming identity method is implemented
    EXPECT_EQ(identity.at(0, 0), 1);
    EXPECT_EQ(identity.at(1, 1), 1);
    EXPECT_EQ(identity.at(2, 2), 1);
    EXPECT_EQ(identity.at(0, 1), 0);
    EXPECT_EQ(identity.at(1, 0), 0);
    EXPECT_EQ(identity.at(1, 2), 0);
    EXPECT_EQ(identity.at(2, 1), 0);
}
// Main function to run all tests
