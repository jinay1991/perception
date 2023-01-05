///
/// @file
/// @copyright Copyright (C) 2021. MIT License.
///
#include "perception/common/matrix.h"

#include <gtest/gtest.h>

namespace perception
{
namespace
{
constexpr std::size_t kMaxRows = 2UL;
constexpr std::size_t kMaxColumns = 2UL;

template <typename T>
class GenericMatrixFixture : public ::testing::Test
{
};

using ArithmeticTypes = ::testing::Types<double, float>;
TYPED_TEST_SUITE(GenericMatrixFixture, ArithmeticTypes);

TYPED_TEST(GenericMatrixFixture, DefaultConstructor_GivenTypicalDimension_ExpectGenericMatrix)
{
    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit;

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
    EXPECT_EQ(unit.GetSize(), kMaxRows * kMaxColumns);
}

TYPED_TEST(GenericMatrixFixture, Constructor_GivenTypicalValue_ExpectGenericMatrixWithSameValue)
{
    // Given
    const TypeParam value{static_cast<TypeParam>(12)};

    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit{value};

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
    EXPECT_EQ(unit(0UL, 0UL), value);
    EXPECT_EQ(unit(0UL, 1UL), value);
    EXPECT_EQ(unit(1UL, 0UL), value);
    EXPECT_EQ(unit(1UL, 1UL), value);
}

TYPED_TEST(GenericMatrixFixture, Constructor_GivenTypicalDimensions_ExpectGenericMatrixWithSameDimensions)
{
    // Given
    const TypeParam value{static_cast<TypeParam>(12)};

    // When
    const std::size_t rows{1UL};
    const std::size_t cols{2UL};
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit{value, rows, cols};

    // Then
    EXPECT_EQ(unit.GetRows(), rows);
    EXPECT_EQ(unit.GetCols(), cols);
    EXPECT_EQ(unit(0UL, 0UL), value);
    EXPECT_EQ(unit(0UL, 1UL), value);
}

TYPED_TEST(GenericMatrixFixture, Constructor_GivenTypicalInitializerList_ExpectGenericMatrixWithSameValues)
{
    // Given
    const std::vector<TypeParam> test_values{static_cast<TypeParam>(1.0),
                                             static_cast<TypeParam>(2.0),
                                             static_cast<TypeParam>(3.0),
                                             static_cast<TypeParam>(4.0)};

    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit{
        {test_values.at(0UL), test_values.at(1UL), test_values.at(2UL), test_values.at(3UL)}, kMaxRows, kMaxColumns};

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
    EXPECT_EQ(unit(0UL, 0UL), test_values.at(0UL));
    EXPECT_EQ(unit(0UL, 1UL), test_values.at(1UL));
    EXPECT_EQ(unit(1UL, 0UL), test_values.at(2UL));
    EXPECT_EQ(unit(1UL, 1UL), test_values.at(3UL));
}

TYPED_TEST(GenericMatrixFixture, Resize_GivenTypicalDimensions_ExpectGenericMatrixWithSameDimensions)
{
    // Given
    const TypeParam value{static_cast<TypeParam>(12)};
    GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit{value};

    // When
    const std::size_t rows{1UL};
    const std::size_t cols{2UL};
    const auto result = unit.Resize(rows, cols);

    // Then
    EXPECT_TRUE(result);
    EXPECT_EQ(unit.GetRows(), rows);
    EXPECT_EQ(unit.GetCols(), cols);
}

TYPED_TEST(GenericMatrixFixture, Resize_GivenInvalidDimensions_ExpectGenericMatrixWithNoChangeInDimensions)
{
    // Given
    const TypeParam value{static_cast<TypeParam>(12)};
    GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit{value};

    // When
    const std::size_t rows{3UL};
    const std::size_t cols{2UL};
    const auto result = unit.Resize(rows, cols);

    // Then
    EXPECT_FALSE(result);
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
}

TYPED_TEST(GenericMatrixFixture, SetConstant_GivenTypicalValue_ExpectGenericMatrixWithSameValue)
{
    // Given
    const TypeParam value{static_cast<TypeParam>(12)};
    GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit{value};

    // When
    const TypeParam constant{static_cast<TypeParam>(13)};
    unit.SetConstant(constant);

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
    EXPECT_EQ(unit(0UL, 0UL), constant);
    EXPECT_EQ(unit(0UL, 1UL), constant);
    EXPECT_EQ(unit(1UL, 0UL), constant);
    EXPECT_EQ(unit(1UL, 1UL), constant);
}

TYPED_TEST(GenericMatrixFixture, OperatorBrackets_GivenTypicalRowColumnIndex_ExpectGenericMatrixElement)
{
    // Given
    const TypeParam value{static_cast<TypeParam>(12)};

    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit{value};

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
    EXPECT_EQ(unit(0UL, 0UL), value);
    EXPECT_EQ(unit(0UL, 1UL), value);
    EXPECT_EQ(unit(1UL, 0UL), value);
    EXPECT_EQ(unit(1UL, 1UL), value);
}

TYPED_TEST(GenericMatrixFixture, OperatorBrackets_GivenTypicalRowColumnIndex_ExpectUpdatedGenericMatrixElement)
{
    // Given
    const TypeParam value{static_cast<TypeParam>(12)};
    GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit{value};

    // When
    const TypeParam changed_value{static_cast<TypeParam>(10)};
    unit(0UL, 1UL) = changed_value;

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
    EXPECT_EQ(unit(0UL, 0UL), value);
    EXPECT_EQ(unit(0UL, 1UL), changed_value);
    EXPECT_EQ(unit(1UL, 0UL), value);
    EXPECT_EQ(unit(1UL, 1UL), value);
}

TYPED_TEST(GenericMatrixFixture, Zero_GivenGenericMatrix_ExpectZeroMatrix)
{
    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit =
        GenericMatrix<TypeParam, kMaxRows, kMaxColumns>::Zero();

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
    EXPECT_EQ(unit(0UL, 0UL), static_cast<TypeParam>(0));
    EXPECT_EQ(unit(0UL, 1UL), static_cast<TypeParam>(0));
    EXPECT_EQ(unit(1UL, 0UL), static_cast<TypeParam>(0));
    EXPECT_EQ(unit(1UL, 1UL), static_cast<TypeParam>(0));
}

TYPED_TEST(GenericMatrixFixture, Identity_GivenGenericMatrix_ExpectIdentityMatrix)
{
    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit =
        GenericMatrix<TypeParam, kMaxRows, kMaxColumns>::Identity();

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
    EXPECT_EQ(unit(0UL, 0UL), static_cast<TypeParam>(1));
    EXPECT_EQ(unit(0UL, 1UL), static_cast<TypeParam>(0));
    EXPECT_EQ(unit(1UL, 0UL), static_cast<TypeParam>(0));
    EXPECT_EQ(unit(1UL, 1UL), static_cast<TypeParam>(1));
}

TYPED_TEST(GenericMatrixFixture, GetSize_GivenGenericMatrix_ExpectMatrixSize)
{
    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit;

    // Then
    EXPECT_EQ(unit.GetSize(), kMaxRows * kMaxColumns);
}

TYPED_TEST(GenericMatrixFixture, GetRows_GivenGenericMatrix_ExpectRows)
{
    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit;

    // Then
    EXPECT_EQ(unit.GetRows(), kMaxRows);
}

TYPED_TEST(GenericMatrixFixture, GetCols_GivenGenericMatrix_ExpectColumns)
{
    // When
    const GenericMatrix<TypeParam, kMaxRows, kMaxColumns> unit;

    // Then
    EXPECT_EQ(unit.GetCols(), kMaxColumns);
}

TEST(GenericMatrix, OperatorMultiplication_GivenTypicalGenericMatrices_ExpectMultiplication)
{
    // Given
    const GenericMatrix<double, kMaxRows, kMaxColumns> lhs{{2.0, 2.0, 2.0, 2.0}, kMaxRows, kMaxColumns};
    const GenericMatrix<double, kMaxRows, kMaxColumns> rhs{{1.0, 2.0, 3.0, 4.0}, kMaxRows, kMaxColumns};

    // When
    const auto result = lhs * rhs;

    // Then
    EXPECT_EQ(result.GetRows(), kMaxRows);
    EXPECT_EQ(result.GetCols(), kMaxColumns);
    EXPECT_EQ(result(0UL, 0UL), 8.0);
    EXPECT_EQ(result(0UL, 1UL), 12.0);
    EXPECT_EQ(result(1UL, 0UL), 8.0);
    EXPECT_EQ(result(1UL, 1UL), 12.0);
}

TEST(GenericMatrix, OperatorMultiplication_GivenTypicalGenericMatrixAndScalar_ExpectMultiplication)
{
    // Given
    const GenericMatrix<double, kMaxRows, kMaxColumns> lhs{{2.0, 2.0, 2.0, 2.0}, kMaxRows, kMaxColumns};
    const double rhs{10.0};

    // When
    const auto result = lhs * rhs;

    // Then
    EXPECT_EQ(result.GetRows(), kMaxRows);
    EXPECT_EQ(result.GetCols(), kMaxColumns);
    EXPECT_EQ(result(0UL, 0UL), 20.0);
    EXPECT_EQ(result(0UL, 1UL), 20.0);
    EXPECT_EQ(result(1UL, 0UL), 20.0);
    EXPECT_EQ(result(1UL, 1UL), 20.0);
}

TEST(GenericMatrix, OperatorMultiplication_GivenTypicalScalarAndGenericMatrix_ExpectMultiplication)
{
    // Given
    const double lhs{10.0};
    const GenericMatrix<double, kMaxRows, kMaxColumns> rhs{{2.0, 2.0, 2.0, 2.0}, kMaxRows, kMaxColumns};

    // When
    const auto result = lhs * rhs;

    // Then
    EXPECT_EQ(result.GetRows(), kMaxRows);
    EXPECT_EQ(result.GetCols(), kMaxColumns);
    EXPECT_EQ(result(0UL, 0UL), 20.0);
    EXPECT_EQ(result(0UL, 1UL), 20.0);
    EXPECT_EQ(result(1UL, 0UL), 20.0);
    EXPECT_EQ(result(1UL, 1UL), 20.0);
}

TEST(GenericMatrix, SubMatrix_GivenTypicalGenericMatrix_ExpectSubMatrix)
{
    // Given
    const GenericMatrix<double, kMaxRows, kMaxColumns> unit{{1.0, 2.0, 3.0, 4.0}, kMaxRows, kMaxColumns};

    // When
    const auto result = unit.SubMatrix(0UL, 0UL, 1UL, 2UL);

    // Then
    EXPECT_EQ(result.GetRows(), 1UL);
    EXPECT_EQ(result.GetCols(), 2UL);
    EXPECT_EQ(result(0UL, 0UL), 1.0);
    EXPECT_EQ(result(0UL, 1UL), 3.0);
}
}  // namespace
}  // namespace perception
