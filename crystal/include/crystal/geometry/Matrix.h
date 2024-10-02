#pragma once
#include <inttypes.h>
#include <string>
namespace crystal::geometry
{
class Matrix
{


    public:
        Matrix(const Matrix& other);
        Matrix(float** arr);
        Matrix(std::initializer_list<std::initializer_list<float>> arr);

        explicit Matrix(size_t row, size_t col, float val);

        Matrix  operator*(const Matrix& other) const;
        Matrix& operator*=(const Matrix& other);
        Matrix  operator*(const float& scalar) const;
        Matrix& operator*=(const float& scalar);
        Matrix  operator/(const float& scalar) const;
        Matrix& operator/=(const float& scalar);

        Matrix  operator+(const Matrix& other) const;
        Matrix& operator+=(const Matrix& other);

        Matrix  operator-(const Matrix& other) const;
        Matrix& operator-=(const Matrix& other);

        Matrix  operator^(const uint32_t& power) const;
        Matrix& operator^=(const uint32_t& power);

        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

        Matrix& operator=(const Matrix& other);

        void put(size_t row, size_t col, float val);

        Matrix getTranspose() const;
        Matrix getInverse() const;
        float  getDeterminant() const;
        Matrix getAdjoint() const;
        Matrix getCofactorMatrix() const;
        float  at(size_t row, size_t col) const;
        float  getCofactor(size_t i, size_t j) const;
        Matrix getSubMatrix(size_t row, size_t col) const;


        std::string toString() const;

        static Matrix identity(size_t rows, size_t cols);
        static Matrix null(size_t rows, size_t cols);
        const float** getRawArrPtr();
        ~Matrix();

    private:
        // m_arr representation of the matrix
        float** m_arr = nullptr;
        // Number of rows in the matrix
        size_t num_rows = 0;
        // Number of columns in the matrix
        size_t num_cols = 0;
        void   allocateMemory();
        Matrix() : num_rows(0), num_cols(0) {};
};
static Matrix invalid_matrix{0, 0, 0};

} // namespace crystal::geometry