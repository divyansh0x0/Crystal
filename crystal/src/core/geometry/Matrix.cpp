#include "core/geometry/Matrix.h"
#include "core/Logger.h"
#include <stdexcept>
using namespace crystal::geometry;

Matrix::Matrix(const Matrix &other) : array(other.array), num_rows(other.num_rows), num_cols(other.num_cols) {}
Matrix::Matrix(const std::vector<std::vector<double>> &arr) : array(arr), num_rows(arr.size()), num_cols(arr[0].size())
{

    if (num_rows == 0 || num_cols == 0)
    {
        throw std::runtime_error("Invalid matrix dimensions, cannot create matrix of dimensions " + std::to_string(num_rows) + "x" + std::to_string(num_cols));
    }
    for (size_t i = 0; i < arr.size(); i++)
    {
        if (arr[i].size() != this->num_cols)
        {
            throw std::runtime_error("Invalid number of items in row, found " + std::to_string(arr[i].size()) + " elements expected " + std::to_string(this->num_cols) + "elements");
        }
    }
}
Matrix::Matrix(size_t row, size_t col, double val) : array(row, std::vector<double>(col)), num_rows(row), num_cols(col)
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            if (i == j)
                array[i][j] = val;
            else
                array[i][j] = 0;
        }
    }
    if (num_rows == 0 || num_cols == 0)
    {
        throw std::runtime_error("Invalid matrix dimensions, cannot create matrix of dimensions " + std::to_string(num_rows) + "x" + std::to_string(num_cols));
    }
}
Matrix::~Matrix()
{
    array.clear();
}
Matrix Matrix::identity(size_t rows, size_t cols)
{
    std::vector<std::vector<double>> arr(rows, std::vector<double>(cols));
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (i == j)
                arr[i][j] = 1;
            else
                arr[i][j] = 0;
        }
    }
    return Matrix(arr);
}
Matrix Matrix::null(size_t rows, size_t cols)
{
    std::vector<std::vector<double>> arr(rows, std::vector<double>(cols, 0));
    return Matrix(arr);
}
Matrix Matrix::operator*(const Matrix &other) const
{
    if (this->num_cols != other.num_rows)
    {
        throw std::runtime_error("Invalid matrix dimensions, cannot multiply matrices of dimensions " + std::to_string(this->num_rows) + "x" + std::to_string(this->num_cols) + " and " + std::to_string(other.num_rows) + "x" + std::to_string(other.num_cols));
    }
    std::vector<std::vector<double>> result(num_rows, std::vector<double>(other.num_cols));
    for (size_t i = 0; i < num_rows; ++i)
    {
        for (size_t j = 0; j < other.num_cols; ++j)
        {
            for (size_t k = 0; k < other.num_cols; ++k)
            {
                result[i][j] += this->array[i][k] * other.array[k][j];
            }
        }
    }
    // logger::success("Matrix: " + std::string(result.begin(), result.end()));
    return Matrix(result);
}
Matrix &Matrix::operator*=(const Matrix &other)
{
    *this = *this * other;
    return *this;
}
// Scalar multiply
Matrix Matrix::operator*(const double &scalar) const
{
    std::vector<std::vector<double>> result(this->num_rows, std::vector<double>(this->num_cols, 0));

    for (size_t i = 0; i < this->num_rows; i++)
    {
        for (size_t j = 0; j < this->num_cols; j++)
        {
            result[i][j] = this->array[i][j] * scalar;
        }
    }
    return Matrix(result);
}
Matrix &Matrix::operator*=(const double &scalar)
{
    *this = *this * scalar;
    return *this;
}
// Scalar divison
Matrix Matrix::operator/(const double &scalar) const
{
    return *this * (1 / scalar);
}
Matrix &Matrix::operator/=(const double &scalar)
{
    *this = *this / scalar;
    return *this;
}
// Addition
Matrix Matrix::operator+(const Matrix &other) const
{
    std::vector<std::vector<double>> result;
    for (size_t i = 0; i < this->num_rows; i++)
    {
        std::vector<double> row;
        for (size_t j = 0; j < this->num_cols; j++)
        {
            row.push_back(this->array[i][j] + other.array[i][j]);
        }
        result.push_back(row);
    }
    return Matrix(result);
}
Matrix &Matrix::operator+=(const Matrix &other)
{
    *this = *this + other;
    return *this;
}
// Subtraction
Matrix Matrix::operator-(const Matrix &other) const
{
    std::vector<std::vector<double>> result;
    for (size_t i = 0; i < this->num_rows; i++)
    {
        std::vector<double> row;
        for (size_t j = 0; j < this->num_cols; j++)
        {
            row.push_back(this->array[i][j] - other.array[i][j]);
        }
        result.push_back(row);
    }
    return Matrix(result);
}
Matrix &Matrix::operator-=(const Matrix &other)
{
    *this = *this - other;
    return *this;
}
// Power
Matrix Matrix::operator^(const uint32_t &power) const
{
    if (power == 0)
    {
        return Matrix::identity(num_rows, num_cols);
    }

    Matrix result = Matrix::identity(num_rows, num_cols);
    const Matrix &base = *this;

    for (uint32_t i = 0; i < power; i++)
    {
        result = result * base;
    }

    return result;
}
Matrix &Matrix::operator^=(const uint32_t &power)
{
    *this = *this ^ power;
    return *this;
}
// Equality
bool Matrix::operator==(const Matrix &other) const
{
    if (this->num_rows != other.num_rows || this->num_cols != other.num_cols)
    {
        return false;
    }
    for (size_t i = 0; i < this->num_rows; i++)
    {
        for (size_t j = 0; j < this->num_cols; j++)
        {
            if (this->array[i][j] != other.array[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
// Inequality
bool Matrix::operator!=(const Matrix &other) const
{
    return !(*this == other);
}
// Copy assignment
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this == &other)
    {
        return *this; // Handle self-assignment
    }

    // Copy data from the other object
    this->num_rows = other.num_rows;
    this->num_cols = other.num_cols;
    this->array = other.array;

    return *this;
}
// at
double Matrix::at(size_t row, size_t col) const
{
    return this->array[row][col];
}
// Transpose
Matrix Matrix::getTranspose() const
{
    std::vector<std::vector<double>> result(this->num_cols, std::vector<double>(this->num_rows, 0));
    for (size_t i = 0; i < this->num_rows; i++)
    {
        for (size_t j = 0; j < this->num_cols; j++)
        {
            result[j][i] = this->array[i][j];
        }
    }
    return Matrix(result);
}
// Determinant
double Matrix::getDeterminant() const
{
    if (this->num_rows != this->num_cols)
        throw std::runtime_error("Determinant can only be calculated for square matrices");
    if (this->num_rows == 1)
        return this->array[0][0];
    if (this->num_rows == 2)
        return this->array[0][0] * this->array[1][1] - this->array[0][1] * this->array[1][0];

    double result = 0;
    for (size_t i = 0; i < this->num_cols; i++)
    {
        result += this->array[0][i] * this->getCofactor(0, i);
    }
    return result;
}

// Submatrix
Matrix Matrix::getSubMatrix(size_t row, size_t col) const
{

    if (this->num_rows != this->num_cols)
        throw std::runtime_error("Submatrix can only be calculated for square matrices");
    std::vector<std::vector<double>> result(this->num_rows - 1, std::vector<double>(this->num_cols - 1, 0));
    for (size_t i = 0; i < this->num_rows; i++)
    {
        for (size_t j = 0; j < this->num_cols; j++)
        {
            if (i == row || j == col)
            {
                continue;
            }
            result[i < row ? i : i - 1][j < col ? j : j - 1] = this->array[i][j];
        }
    }
    return Matrix(result);
}
// Cofactor
double Matrix::getCofactor(size_t row, size_t col) const
{
    if (this->num_rows != this->num_cols)
        throw std::runtime_error("Cofactor can only be calculated for square matrices");

    Matrix subMatrix = this->getSubMatrix(row, col);
    return subMatrix.getDeterminant() * ((row + col) % 2 == 0 ? 1 : -1);
}
// Cofactor
Matrix Matrix::getCofactorMatrix() const
{
    std::vector<std::vector<double>> result(this->num_rows, std::vector<double>(this->num_cols, 0));
    for (size_t i = 0; i < this->num_rows; i++)
    {
        for (size_t j = 0; j < this->num_cols; j++)
        {
            result[i][j] = this->getCofactor(i, j);
        }
    }
    return Matrix(result);
}

// Adjoint
Matrix Matrix::getAdjoint() const
{
    return getCofactorMatrix().getTranspose();
}
// Inverse
Matrix Matrix::getInverse() const
{
    double determinant = this->getDeterminant();
    if (determinant == 0)
    {
        throw std::runtime_error("Inverse can only be calculated for non-singular matrices (determinant of matrix should be non zero)");
    }
    return this->getAdjoint() / determinant;
}

std::string Matrix::toString() const
{
    std::string result = "";
    for (size_t i = 0; i < this->num_rows; i++)
    {
        for (size_t j = 0; j < this->num_cols; j++)
        {
            result += std::to_string(this->array[i][j]) + ", ";
        }
        result += "\n";
    }
    return result;
}