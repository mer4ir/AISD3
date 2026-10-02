#pragma once
#include <iostream>
#include <stdexcept>
#include <random>
#include <cmath>
#include <complex>

template <typename T>
class Matrix
{
private:
    T *data_;
    size_t rows_;
    size_t cols_;

    size_t index(size_t row, size_t col) const
    {
        return row * cols_ + col;
    }

public:
    static constexpr double EPSILON = 1e-9;

    // Конструктор создаёт матрицу и заполняет все значения fillValue
    Matrix(size_t rows, size_t cols, const T &fillValue = T{})
        : rows_(rows), cols_(cols), data_(new T[rows * cols])
    {
        if (rows == 0 || cols == 0)
        {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }

        for (size_t i = 0; i < rows_ * cols_; ++i)
        {
            data_[i] = fillValue;
        }
    }

    // Конструктор создаёт матрицу и заполняет случайными значениями в диапазоне
    Matrix(size_t rows, size_t cols, T lower_bound, T upper_bound)
        : rows_(rows), cols_(cols), data_(new T[rows * cols])
    {
        if (rows == 0 || cols == 0)
        {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }

        std::random_device rd;
        std::mt19937 gen(rd());

        for (size_t i = 0; i < rows_ * cols_; ++i)
        {
            if constexpr (std::is_integral_v<T>)
            {
                std::uniform_int_distribution<T> dist(lower_bound, upper_bound);
                data_[i] = dist(gen);
            }
            else if constexpr (std::is_arithmetic_v<T>)
            {
                std::uniform_real_distribution<T> dist(lower_bound, upper_bound);
                data_[i] = dist(gen);
            }
            else
            {
                if (lower_bound.real() > upper_bound.real() ||
                    lower_bound.imag() > upper_bound.imag())
                {
                    throw std::invalid_argument("Invalid bounds for complex numbers");
                }
                using ValueType = typename T::value_type;
                std::uniform_real_distribution<ValueType> real_dist(lower_bound.real(), upper_bound.real());
                std::uniform_real_distribution<ValueType> imag_dist(lower_bound.imag(), upper_bound.imag());
                data_[i] = T(real_dist(gen), imag_dist(gen));
            }
        }
    }

    // Конструктор копирования
    Matrix(const Matrix &other)
        : rows_(other.rows_), cols_(other.cols_), data_(new T[rows_ * cols_])
    {
        for (size_t i = 0; i < rows_ * cols_; ++i)
        {
            data_[i] = other.data_[i];
        }
    }

    // Деструктор
    ~Matrix()
    {
        delete[] data_;
    }

    // Оператор присваивания
    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            delete[] data_;

            rows_ = other.rows_;
            cols_ = other.cols_;
            data_ = new T[rows_ * cols_];

            for (size_t i = 0; i < rows_ * cols_; ++i)
            {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    // Оператор доступа к элементам
    T &operator()(size_t row, size_t col)
    {
        if (row >= rows_ || col >= cols_)
        {
            throw std::out_of_range("Matrix index out of range");
        }
        return data_[index(row, col)];
    }

    const T &operator()(size_t row, size_t col) const
    {
        if (row >= rows_ || col >= cols_)
        {
            throw std::out_of_range("Matrix index out of range");
        }
        return data_[index(row, col)];
    }

    // Оператор поэлементоного сложения
    Matrix operator+(const Matrix &other) const
    {
        if (rows_ != other.rows_ || cols_ != other.cols_)
        {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_ * cols_; ++i)
        {
            result.data_[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    // Оператор поэлементоного вычитания
    Matrix operator-(const Matrix &other) const
    {
        if (rows_ != other.rows_ || cols_ != other.cols_)
        {
            throw std::invalid_argument("Matrix dimensions must match for subtraction");
        }

        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_ * cols_; ++i)
        {
            result.data_[i] = data_[i] - other.data_[i];
        }
        return result;
    }

    // Оператор умножения матриц
    Matrix operator*(const Matrix &other) const
    {
        if (cols_ != other.rows_)
        {
            throw std::invalid_argument("Matrix dimensions are incompatible for multiplication");
        }

        Matrix result(rows_, other.cols_);
        for (size_t i = 0; i < rows_; ++i)
        {
            for (size_t j = 0; j < other.cols_; ++j)
            {
                T sum{};
                for (size_t k = 0; k < cols_; ++k)
                {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    // Оператор умножения на скаляр
    template <typename U>
    Matrix operator*(const U &scalar) const
    {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_ * cols_; ++i)
        {
            result.data_[i] = data_[i] * scalar;
        }
        return result;
    }
    // Оператор деления на скаляр
    template <typename U>
    Matrix operator/(const U &scalar) const
    {
        if (std::abs(scalar) < EPSILON)
        {
            throw std::invalid_argument("Division by zero");
        }

        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_ * cols_; ++i)
        {
            result.data_[i] = data_[i] / scalar;
        }
        return result;
    }

    // Вычисление следа матрицы
    T trace() const
    {
        if (rows_ != cols_)
        {
            throw std::invalid_argument("Trace is defined only for square matrices");
        }

        T result{};
        for (size_t i = 0; i < rows_; ++i)
        {
            result += (*this)(i, i);
        }
        return result;
    }

    //Доступ к размерам матрицы
    size_t getRows() const { return rows_; }
    size_t getCols() const { return cols_; }

    // Операторы сравнения
    bool operator==(const Matrix &other) const
    {
        if (rows_ != other.rows_ || cols_ != other.cols_)
        {
            return false;
        }

        for (size_t i = 0; i < rows_ * cols_; ++i)
        {
            if (std::abs(data_[i] - other.data_[i]) > EPSILON)
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix &other) const
    {
        return !(*this == other);
    }
};

// Операторы вывода Ostream
template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
{
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (size_t j = 0; j < matrix.getCols(); ++j)
        {
            if constexpr (std::is_same_v<T, std::complex<float>> ||
                          std::is_same_v<T, std::complex<double>> ||
                          std::is_same_v<T, std::complex<long double>>)
            {
                const auto &c = matrix(i, j);
                os << c.real();
                if (c.imag() >= 0)
                {
                    os << "+" << c.imag() << "i";
                }
                else
                {
                    os << c.imag() << "i";
                }
            }
            else
            {
                os << matrix(i, j);
            }

            if (j < matrix.getCols() - 1)
            {
                os << " ";
            }
        }
        if (i < matrix.getRows() - 1)
        {
            os << "\n";
        }
    }
    return os;
}

// Свободный оператор умножения скаляра на матрицу
template <typename T, typename U>
Matrix<T> operator*(const U &scalar, const Matrix<T> &matrix)
{
    return matrix * scalar;
}

// Функция для вычисления обратной матрицы 3x3
template <typename T>
Matrix<T> inverse3x3(const Matrix<T> &matrix)
{
    if (matrix.getRows() != 3 || matrix.getCols() != 3)
    {
        throw std::invalid_argument("Matrix must be 3x3 for inverse calculation");
    }
    T det = matrix(0, 0) * (matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1)) - matrix(0, 1) * (matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0)) + matrix(0, 2) * (matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0));

    if (std::abs(det) < Matrix<T>::EPSILON)
    {
        throw std::invalid_argument("Matrix is singular, cannot compute inverse");
    }
    Matrix<T> cofactor(3, 3);
    cofactor(0, 0) = (matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1));
    cofactor(0, 1) = -(matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0));
    cofactor(0, 2) = (matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0));
    cofactor(1, 0) = -(matrix(0, 1) * matrix(2, 2) - matrix(0, 2) * matrix(2, 1));
    cofactor(1, 1) = (matrix(0, 0) * matrix(2, 2) - matrix(0, 2) * matrix(2, 0));
    cofactor(1, 2) = -(matrix(0, 0) * matrix(2, 1) - matrix(0, 1) * matrix(2, 0));
    cofactor(2, 0) = (matrix(0, 1) * matrix(1, 2) - matrix(0, 2) * matrix(1, 1));
    cofactor(2, 1) = -(matrix(0, 0) * matrix(1, 2) - matrix(0, 2) * matrix(1, 0));
    cofactor(2, 2) = (matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0));
    Matrix<T> inverse(3, 3);
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            inverse(i, j) = cofactor(j, i) / det;
        }
    }

    return inverse;
}