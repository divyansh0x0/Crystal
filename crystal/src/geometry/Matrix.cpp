#include "crystal/geometry/Matrix.h"
#include "crystal/core/Logger.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

#define SIZE_OF_ARRAY(x) (*(&x + 1) - x)
namespace crystal::geometry
{
/////////////////////////////////////////////////////////////////////////////////////////
//                       Constructors
/////////////////////////////////////////////////////////////////////////////////////////
Matrix::Matrix(const Matrix& other) : num_rows(other.num_rows), num_cols(other.num_cols)
{
    if (other.m_arr == nullptr) return;
    allocateMemory();
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
            m_arr[i][j] = other.m_arr[i][j];
    }
}
Matrix::Matrix(float** arr)
{
    if (arr == nullptr)
    {
        return;
    }
    int row_len = SIZE_OF_ARRAY(arr);
    int col_len = SIZE_OF_ARRAY(arr[0]);
    if (row_len == 0 || col_len == 0)
    {
        return;
    }
    num_rows = row_len;
    num_cols = col_len;
    allocateMemory();
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
            m_arr[i][j] = arr[i][j];
    }
}
Matrix::Matrix(const std::initializer_list<std::initializer_list<float>> arr) : num_rows(arr.size()), num_cols(arr.begin()->size())
{
    if (num_cols == 0 || num_rows == 0)
    {
        return;
    }
    size_t i = 0;
    size_t j = 0;
    allocateMemory();
    for (auto& row : arr)
    {
        for (auto& col : row)
        {
            m_arr[i][j] = (col);
            j++;
        }
        i++;
        j = 0;
    }
}

Matrix::Matrix(size_t row, size_t col, float val) : num_rows(row), num_cols(col)
{
    if (num_rows == 0 || num_rows == 0)
    {
        return;
    }
    allocateMemory();
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
            m_arr[i][j] = val;
    }
}
/////////////////////////////////////////////////////////////////
//                       Destructors
/////////////////////////////////////////////////////////////////
Matrix::~Matrix()
{
    for (size_t i = 0; i < num_rows; i++)
    {
        delete[] m_arr[i];
    }
    delete[] m_arr;
}
/////////////////////////////////////////////////////////////////
//                       Private Methods
/////////////////////////////////////////////////////////////////

void Matrix::allocateMemory()
{
    m_arr = new float*[num_rows];
    for (size_t i = 0; i < num_rows; i++)
    {
        m_arr[i] = new float[num_cols];
    }
}
/////////////////////////////////////////////////////////////////
//                       Static Methods
/////////////////////////////////////////////////////////////////

Matrix Matrix::identity(size_t rows, size_t cols)
{
    if (rows != cols || rows == 0 || cols == 0)
    {
        return invalid_matrix;
    }
    Matrix result{rows, cols, 0};
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (i == j)
                result.m_arr[i][j] = 1;
            else
                result.m_arr[i][j] = 0;
        }
    }
    return result;
}


Matrix Matrix::null(size_t rows, size_t cols)
{
    if (rows != cols || rows == 0 || cols == 0)
    {
        return invalid_matrix;
    }
    return Matrix(rows, cols, 0);
}

/////////////////////////////////////////////////////////////////
//                       Public Methods
/////////////////////////////////////////////////////////////////

const float** Matrix::getRawArrPtr()
{
    return (const float**) m_arr;
}
Matrix Matrix::operator*(const Matrix& other) const
{
    if (num_cols != other.num_rows|| m_arr == nullptr || other.m_arr == nullptr)
    {
        // throw std::runtime_error("Invalid matrix dimensions, cannot multiply matrices of dimensions " + std::to_string(num_rows) + "x"
        //                          + std::to_string(num_cols) + " and " + std::to_string(other.num_rows) + "x" + std::to_string(other.num_cols));
        return invalid_matrix;
    }
    Matrix result(num_rows, other.num_cols, 0);
    for (size_t i = 0; i < num_rows; ++i)
    {
        for (size_t j = 0; j < other.num_cols; ++j)
        {
            for (size_t k = 0; k < num_cols; ++k)
            {
                result.m_arr[i][j] += m_arr[i][k] * other.m_arr[k][j];
            }
        }
    }
    // logger::Success("Matrix: " + std::string(result.begin(), result.end()));
    return result;
}
Matrix& Matrix::operator*=(const Matrix& other)
{
    *this = *this * other;
    return *this;
}
// Scalar multiply
Matrix Matrix::operator*(const float& scalar) const
{
    Matrix result(num_rows, num_cols, 0);


    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            result.m_arr[i][j] = m_arr[i][j] * scalar;
        }
    }
    return Matrix(result);
}
Matrix& Matrix::operator*=(const float& scalar)
{
    *this = *this * scalar;
    return *this;
}
// Scalar divison
Matrix Matrix::operator/(const float& scalar) const
{
    if (scalar == 0) return Matrix(num_rows, num_cols, std::numeric_limits<float>::quiet_NaN());
    return *this * (1 / scalar);
}
Matrix& Matrix::operator/=(const float& scalar)
{
    *this = *this / scalar;
    return *this;
}
// Addition
Matrix Matrix::operator+(const Matrix& other) const
{
    if (num_rows != other.num_rows || num_cols != other.num_cols) return invalid_matrix;

    Matrix result(num_rows, num_cols, 0);
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            result.m_arr[i][j] = m_arr[i][j] + other.m_arr[i][j];
        }
    }
    return result;
}
Matrix& Matrix::operator+=(const Matrix& other)
{
    if (num_rows != other.num_rows || num_cols != other.num_cols) return invalid_matrix;
    *this = *this + other;
    return *this;
}
// Subtraction
Matrix Matrix::operator-(const Matrix& other) const
{

    if (num_rows != other.num_rows || num_cols != other.num_cols) return invalid_matrix;
    Matrix result(num_rows, num_cols, 0);
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            result.m_arr[i][j] = m_arr[i][j] - other.m_arr[i][j];
        }
    }
    return result;
}
Matrix& Matrix::operator-=(const Matrix& other)
{
    *this = *this - other;
    return *this;
}
// Power
Matrix Matrix::operator^(const uint32_t& power) const
{
    if (this->num_cols != this->num_rows) return invalid_matrix;
    if (power == 0)
    {
        return Matrix::identity(num_rows, num_cols);
    }

    Matrix        result = Matrix::identity(num_rows, num_cols);
    const Matrix& base   = *this;

    for (uint32_t i = 0; i < power; i++)
    {
        result = result * base;
    }

    return result;
}
Matrix& Matrix::operator^=(const uint32_t& power)
{
    *this = *this ^ power;
    return *this;
}
// Equality
bool Matrix::operator==(const Matrix& other) const
{
    if(m_arr == nullptr || other.m_arr == nullptr) return true;
    if (num_rows != other.num_rows || num_cols != other.num_cols)
    {
        return false;
    }
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            if (m_arr[i][j] != other.m_arr[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
// Inequality
bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}
// Copy assignment
Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other)
    {
        return *this; // Handle self-assignment
    }

    // Copy data from the other object
    num_rows = other.num_rows;
    num_cols = other.num_cols;
    m_arr    = other.m_arr;

    return *this;
}
void Matrix::put(size_t row, size_t col, float value)
{
    if (m_arr == nullptr || row >= num_rows || col >= num_cols || row < 0 || col < 0)
    {
        return;
    }
    m_arr[row][col] = value;
}
// at
float Matrix::at(size_t row, size_t col) const
{
    if (m_arr == nullptr || row >= num_rows || col >= num_cols || row < 0 || col < 0)
    {
        return std::numeric_limits<float>::quiet_NaN();
    }


    return m_arr[row][col];
}
// Transpose
Matrix Matrix::getTranspose() const
{
    if (m_arr == nullptr) return *this;
    Matrix result{num_cols, num_rows, 0};
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            result.m_arr[j][i] = m_arr[i][j];
        }
    }
    return result;
}
// Determinant
float Matrix::getDeterminant() const
{
    if (num_rows != num_cols || m_arr == nullptr)
    {
        return std::numeric_limits<float>::quiet_NaN();
    }
    if (num_rows == 1) return m_arr[0][0];
    if (num_rows == 2) return m_arr[0][0] * m_arr[1][1] - m_arr[0][1] * m_arr[1][0];

    float result = 0;
    for (size_t i = 0; i < num_cols; i++)
    {
        result += m_arr[0][i] * getCofactor(0, i);
    }
    return result;
}

// Submatrix
Matrix Matrix::getSubMatrix(size_t deleted_row, size_t deleted_col) const
{

    if (num_rows != num_cols)
    {
        return invalid_matrix;
    }
    Matrix result{num_rows - 1, num_cols - 1, 0};
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            if (i == deleted_row || j == deleted_col)
            {
                continue;
            }
            result.m_arr[i < deleted_row ? i : i - 1][j < deleted_col ? j : j - 1] = m_arr[i][j];
        }
    }
    return result;
}
// Cofactor
float Matrix::getCofactor(size_t i, size_t j) const
{
    if (m_arr == nullptr)
    {
        return std::numeric_limits<float>::quiet_NaN();
    }
    if (num_rows != num_cols)
    {
        return 0;
    };

    Matrix subMatrix = getSubMatrix(i, j);
    return subMatrix.getDeterminant() * ((i + j) % 2 == 0 ? 1 : -1);
}
// Cofactor
Matrix Matrix::getCofactorMatrix() const
{
    if (m_arr == nullptr || num_rows != num_cols) return *this;
    Matrix result{num_rows, num_cols, 0};
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            result.m_arr[i][j] = getCofactor(i, j);
        }
    }
    return result;
}

// Adjoint
Matrix Matrix::getAdjoint() const
{
    if (m_arr == nullptr) return *this;
    return getCofactorMatrix().getTranspose();
}
// Inverse
Matrix Matrix::getInverse() const
{
    if (m_arr == nullptr) return *this;

    float determinant = getDeterminant();
    if (determinant == 0) return invalid_matrix;

    return getAdjoint() / determinant;
}

std::string Matrix::toString() const
{
    std::string result = "";
    for (size_t i = 0; i < num_rows; i++)
    {
        for (size_t j = 0; j < num_cols; j++)
        {
            result += std::to_string(m_arr[i][j]) + ", ";
        }
        result += "\n";
    }
    return result;
}
} // namespace crystal::geometry