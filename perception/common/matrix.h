///
/// @file
/// @copyright Copyright (C) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_MATRIX_H
#define PERCEPTION_COMMON_MATRIX_H

#include <array>
#include <cassert>
#include <initializer_list>
#include <type_traits>

namespace perception
{
template <typename T,
          std::size_t kMaxRows,
          std::size_t kMaxColumns,
          std::enable_if_t<std::is_arithmetic<T>::value && (kMaxColumns != 0UL) && (kMaxRows != 0UL), bool> = true>
class GenericMatrix
{
  public:
    constexpr GenericMatrix() : GenericMatrix{static_cast<T>(0)} {}

    explicit constexpr GenericMatrix(const T& value) : GenericMatrix{value, kMaxRows, kMaxColumns} {}

    explicit constexpr GenericMatrix(const T& value, const std::size_t rows, const std::size_t cols)
        : rows_{rows}, cols_{cols}, matrix_{}
    {
        SetConstant(value);
    }

    explicit constexpr GenericMatrix(const std::initializer_list<T>& list,
                                     const std::size_t rows,
                                     const std::size_t cols)
        : rows_{rows}, cols_{cols}, matrix_{}
    {
        std::copy(list.begin(), list.end(), matrix_.begin());
    }

    constexpr bool Resize(const std::size_t rows, const std::size_t cols) noexcept
    {
        bool result = false;
        if ((rows > 0UL) && (rows <= kMaxRows) && (cols > 0UL) && (cols <= kMaxColumns))
        {
            rows_ = rows;
            cols_ = cols;
            result = true;
        }
        return result;
    }

    constexpr T operator()(const std::size_t row, const std::size_t col) const noexcept
    {
        return matrix_.at((row * GetCols()) + col);
    }

    constexpr T& operator()(const std::size_t row, const std::size_t col) noexcept
    {
        return matrix_.at((row * GetCols()) + col);
    }

    constexpr void SetConstant(const T& value) noexcept { matrix_.fill(value); }

    static constexpr GenericMatrix Zero() noexcept
    {
        const GenericMatrix<T, kMaxRows, kMaxColumns> zero_matrix{static_cast<T>(0)};
        return zero_matrix;
    }

    static constexpr GenericMatrix Identity() noexcept
    {
        GenericMatrix<T, kMaxRows, kMaxColumns> identity{static_cast<T>(0)};
        for (auto j = 0UL; j < identity.GetCols(); ++j)
        {
            identity(j, j) = static_cast<T>(1);
        }
        return identity;
    }

    constexpr GenericMatrix SubMatrix(const std::size_t row,
                                      const std::size_t col,
                                      const std::size_t rows,
                                      const std::size_t cols) const noexcept
    {
        GenericMatrix submatrix{0, rows, cols};
        for (auto i = row, r = 0UL; (i < GetRows()) && (r < rows); ++i, ++r)
        {
            for (auto j = col, c = 0UL; (j < GetCols()) && (c < cols); ++i, ++c)
            {
                submatrix(r, c) = static_cast<T>(operator()(i, j));
            }
        }
        return submatrix;
    }

    constexpr std::size_t GetSize() const noexcept { return matrix_.size(); }
    constexpr std::size_t GetRows() const noexcept { return rows_; }
    constexpr std::size_t GetCols() const noexcept { return cols_; }

  private:
    using ArrayType = std::array<T, kMaxRows * kMaxColumns>;

    std::size_t rows_;
    std::size_t cols_;
    ArrayType matrix_;
};

template <typename OtherT, std::size_t kRhsRows, std::size_t kRhsColumns>
constexpr GenericMatrix<OtherT, kRhsRows, kRhsColumns> operator*(
    const OtherT& lhs,
    const GenericMatrix<OtherT, kRhsRows, kRhsColumns>& rhs) noexcept
{
    GenericMatrix<OtherT, kRhsRows, kRhsColumns> result_matrix;
    for (auto i = 0UL; i < rhs.GetRows(); ++i)
    {
        for (auto j = 0UL; j < rhs.GetCols(); ++j)
        {
            result_matrix(i, j) = lhs * rhs(i, j);
        }
    }
    return result_matrix;
}

template <typename OtherT, std::size_t kLhsRows, std::size_t kLhsColumns>
constexpr GenericMatrix<OtherT, kLhsRows, kLhsColumns> operator*(
    const GenericMatrix<OtherT, kLhsRows, kLhsColumns>& lhs,
    const OtherT& rhs) noexcept
{
    GenericMatrix<OtherT, kLhsRows, kLhsColumns> result_matrix;
    for (auto i = 0UL; i < lhs.GetRows(); ++i)
    {
        for (auto j = 0UL; j < lhs.GetCols(); ++j)
        {
            result_matrix(i, j) = lhs(i, j) * rhs;
        }
    }
    return result_matrix;
}

template <typename OtherT,
          std::size_t kLhsRows,
          std::size_t kLhsColumns,
          std::size_t kRhsRows,
          std::size_t kRhsColumns,
          std::enable_if_t<(kLhsColumns == kRhsRows), bool> = true>
constexpr GenericMatrix<OtherT, kLhsRows, kRhsColumns> operator*(
    const GenericMatrix<OtherT, kLhsRows, kLhsColumns>& lhs,
    const GenericMatrix<OtherT, kRhsRows, kRhsColumns>& rhs) noexcept
{
    GenericMatrix<OtherT, kLhsRows, kRhsColumns> result_matrix;

    for (auto i = 0UL; i < lhs.GetRows(); ++i)
    {
        for (auto j = 0UL; j < rhs.GetCols(); ++j)
        {
            result_matrix(i, j) = static_cast<OtherT>(0);
            for (auto k = 0UL; k < rhs.GetRows(); ++k)
            {
                result_matrix(i, j) += (lhs(i, k) * rhs(k, j));
            }
        }
    }
    return result_matrix;
}
}  // namespace perception

#endif  /// PERCEPTION_COMMON_MATRIX_H
