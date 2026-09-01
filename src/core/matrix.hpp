#ifndef INCLUDE_TREELANG_CORE_MATRIX_HPP
#define INCLUDE_TREELANG_CORE_MATRIX_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

#include "helper.hpp"

namespace treelang
{

    template <typename T>
        requires(!std::is_reference_v<T> && !std::is_const_v<T>)
    class MatrixElement
    {
    private:
        T m_data;

    public:
        MatrixElement()
            requires(std::is_default_constructible_v<T>)
        = default;
        MatrixElement(const MatrixElement<T> &)
            requires(std::is_copy_constructible_v<T>)
        = default;
        MatrixElement(MatrixElement<T> &&) noexcept
            requires(std::is_move_constructible_v<T>)
        = default;

        MatrixElement(const T &val)
            requires(std::is_copy_constructible_v<T>)
            : m_data(val)
        {
        }
        MatrixElement(T &&val)
            requires(std::is_move_constructible_v<T>)
            : m_data(std::move(val))
        {
        }

    public:
        MatrixElement &operator=(const MatrixElement<T> &)
            requires(std::is_copy_assignable_v<T>)
        = default;
        MatrixElement &operator=(MatrixElement<T> &&) noexcept
            requires(std::is_move_assignable_v<T>)
        = default;

        T &data() { return m_data; }
        const T &data() const { return m_data; }
    };

    template <typename T, size_t M>
    class MatrixRow
    {
    private:
        std::array<MatrixElement<T>, M> m_data;

    public:
        MatrixRow()
            requires(std::is_default_constructible_v<T>)
        = default;
        MatrixRow(const MatrixRow<T, M> &)
            requires(std::is_copy_constructible_v<T>)
        = default;
        MatrixRow(MatrixRow<T, M> &&) noexcept
            requires(std::is_move_constructible_v<T>)
        = default;

        MatrixRow(const std::array<T, M> &arr)
            requires(std::is_copy_constructible_v<T>)
            : m_data(transform_array(arr, [](T val) { return MatrixElement<T>{val}; }))
        {
        }
        MatrixRow(std::array<T, M> &&arr)
            requires(std::is_move_constructible_v<T>)
            : m_data(transform_array(std::move(arr), [](T &val) {
                  return MatrixElement<T>{std::move(val)};
              }))
        {
        }

    public:
        MatrixRow &operator=(const MatrixRow<T, M> &)
            requires(std::is_copy_assignable_v<T>)
        = default;
        MatrixRow &operator=(MatrixRow<T, M> &&) noexcept
            requires(std::is_move_assignable_v<T>)
        = default;

        T &operator[](size_t idx) { return m_data[idx].data(); }
        const T &operator[](size_t idx) const { return m_data[idx].data(); }
    };

    template <typename T, size_t N, size_t M>
    class Matrix
    {
    private:
        std::array<MatrixRow<T, M>, N> m_rows;

    public:
        Matrix()
            requires(std::is_default_constructible_v<T>)
        = default;
        Matrix(const Matrix<T, N, M> &)
            requires(std::is_copy_constructible_v<T>)
        = default;
        Matrix(Matrix<T, N, M> &&) noexcept
            requires(std::is_move_constructible_v<T>)
        = default;

        Matrix(const std::array<std::array<T, M>, N> &arr)
            requires(std::is_copy_constructible_v<T>)
            : m_rows(transform_array(arr, [](const std::array<T, M> &row) {
                  return MatrixRow<T, M>{row};
              }))
        {
        }
        Matrix(std::array<std::array<T, M>, N> &&arr)
            requires(std::is_move_constructible_v<T>)
            : m_rows(transform_array(std::move(arr), [](std::array<T, M> &row) {
                  return MatrixRow<T, M>{std::move(row)};
              }))
        {
        }

    public:
        Matrix &operator=(const Matrix<T, N, M> &)
            requires(std::is_copy_assignable_v<T>)
        = default;
        Matrix &operator=(Matrix<T, N, M> &&) noexcept
            requires(std::is_move_assignable_v<T>)
        = default;

        MatrixRow<T, M> &operator[](size_t idx) { return m_rows[idx]; }
        const MatrixRow<T, M> &operator[](size_t idx) const { return m_rows[idx]; }
    };
}

#endif  // INCLUDE_TREELANG_CORE_MATRIX_HPP
