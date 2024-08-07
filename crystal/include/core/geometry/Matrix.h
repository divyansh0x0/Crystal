#pragma once
#include<vector>
#include<optional>
#include<inttypes.h>
#include<string>
namespace crystal::geometry
{
    /**
     * @class Matrix
     * @brief A class representing a matrix for linear algebra operations.
     */
    class Matrix
    {
        private:
            // Array representation of the matrix
            std::vector<std::vector<double>> array;
            // Number of rows in the matrix
            size_t num_rows;
            // Number of columns in the matrix
            size_t num_cols;
            /**
             * @brief Default constructor for zero matrix of size (0, 0).
             */
            Matrix():num_rows(0),num_cols(0){};
  
        public:
            /**
             * @brief Copy constructor for Matrix.
             * @param other Matrix to copy from.
             */
            Matrix(const Matrix& other);
            
            /**
             * @brief Constructor for Matrix.
             * @param arr Array representation of the matrix.
             */
            Matrix(const std::vector<std::vector<double>>& arr);
            /**
             * @brief Constructor for Matrix.
             * @param row Number of rows in the matrix.
             * @param col Number of columns in the matrix.
             * @param val Value to fill the matrix with.
             */
            Matrix(size_t row,size_t col, double val);

            /**
             * @brief Matrix multiplication.
             * @param other Matrix to multiply with.
             * @return New matrix after multiplication.
             */
            Matrix operator *(const Matrix& other) const;
            /**
             * @brief Matrix multiplication assignment.
             * @param other Matrix to multiply with.
             * @return Reference to the current matrix.
             */
            Matrix& operator *=(const Matrix& other);
            /**
             * @brief Scalar matrix multiplication.
             * @param scalar Value to multiply the matrix with.
             * @return New matrix after multiplication.
             */
            Matrix operator *(const double& scalar) const;
            /**
             * @brief Scalar matrix multiplication assignment.
             * @param scalar Value to multiply the matrix with.
             * @return Reference to the current matrix.
             */
            Matrix& operator *=(const double& scalar);
            /**
             * @brief Scalar matrix division.
             * @param scalar Value to divide the matrix with.
             * @return New matrix after multiplication.
             */
            Matrix operator /(const double& scalar) const;
            /**
             * @brief Scalar matrix division assignment.
             * @param scalar Value to divide the matrix with.
             * @return Reference to the current matrix.
             */
            Matrix& operator /=(const double& scalar);

            /**
             * @brief Matrix addition.
             * @param other Matrix to add with.
             * @return New matrix after addition.
             */
            Matrix operator +(const Matrix& other) const;
            /**
             * @brief Matrix addition assignment.
             * @param other Matrix to add with.
             * @return Reference to the current matrix.
             */
            Matrix& operator +=(const Matrix& other);

            /**
             * @brief Matrix subtraction.
             * @param other Matrix to subtract with.
             * @return New matrix after subtraction.
             */
            Matrix operator -(const Matrix& other) const;
            /**
             * @brief Matrix subtraction assignment.
             * @param other Matrix to subtract with.
             * @return Reference to the current matrix.
             */
            Matrix& operator -=(const Matrix& other);

            /**
             * @brief Matrix exponentiation.
             * @param power Power to raise the matrix to.
             * @return New matrix after exponentiation.
             */
            Matrix operator ^(const uint32_t& power) const;
            /**
             * @brief Matrix exponentiation assignment.
             * @param power Power to raise the matrix to.
             * @return Reference to the current matrix.
             */
            Matrix& operator ^=(const uint32_t& power);

            /**
             * @brief Matrix equality comparison.
             * @param other Matrix to compare with.
             * @return True if the matrices are equal, false otherwise.
             */
            bool operator ==(const Matrix& other) const;
            /**
             * @brief Matrix inequality comparison.
             * @param other Matrix to compare with.
             * @return True if the matrices are not equal, false otherwise.
             */
            bool operator !=(const Matrix& other) const;

            /**
             * @brief Matrix assignment.
             * @param other Matrix to assign from.
             * @return Reference to the current matrix.
             */
            Matrix& operator =(const Matrix& other);


            /**
             * @brief Get the array representation of the matrix.
             * @return Array representation of the matrix.
             */
            std::vector<std::vector<double>> getMatrixArray();

            /**
             * @brief Get the transpose of the matrix.
             * @return Transpose of the matrix.
             */
            Matrix getTranspose() const;
            /**
             * @brief Get the inverse of the matrix.
             * @return Inverse of the matrix.
             */
            Matrix getInverse() const;
            /**
             * @brief Get the determinant of the matrix.
             * @return Determinant of the matrix.
             */
            double getDeterminant() const;
            /**
             * @brief Get the adjoint of the matrix.
             * @return Adjoint of the matrix.
             */
            Matrix getAdjoint() const;
            /**
             * @brief Get the cofactor matrix of the matrix.
             * @return Cofactor matrix of the matrix.
             */
            Matrix getCofactorMatrix() const;
            /**
             * @brief Get the number of rows in the matrix.
             * @return Number of rows in the matrix.
             */
            double at(size_t row, size_t col) const;
            /**
             * @brief Get the number of columns in the matrix.
             * @return Number of columns in the matrix.
             */
            double getCofactor(size_t row, size_t col) const;
            /**
             * @brief Get the submatrix of the matrix.
             * @param row Row to remove from the matrix.
             * @param col Column to remove from the matrix.
             * @return Submatrix of the matrix.
             */
            Matrix getSubMatrix(size_t row, size_t col) const;

            /**
             * @brief Convert the matrix to string representation.
             * @return String representation of the matrix.
             */

            std::string toString() const;

            /**
             * @brief Get an identity matrix of given size.
             * @param rows Number of rows in the matrix.
             * @param cols Number of columns in the matrix.
             * @return Identity matrix of given size.
             */
            static Matrix identity(size_t rows, size_t cols);
            /**
             * @brief Get a null matrix of given size.
             * @param rows Number of rows in the matrix.
             * @param cols Number of columns in the matrix.
             * @return Null matrix of given size.
             */
            static Matrix null(size_t rows, size_t cols);

            /**
             * @brief Destructor for Matrix.
             */
            ~Matrix();
    };
}