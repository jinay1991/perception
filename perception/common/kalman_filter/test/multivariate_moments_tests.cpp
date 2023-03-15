///
/// @file
/// @copyright Copyright (C) 2023. MIT License.
///
#include "perception/common/kalman_filter/multivariate_moments.h"

#include <gtest/gtest.h>

namespace perception
{
namespace
{
constexpr std::int32_t kStateVectorDimension{2};

TEST(MultivariateMoment, DefaultConstructor_GivenTypicalDimension_ExpectMeanVectorAndCovarianceMatrixDimensions)
{
    // When
    const MultivariateMoments<double, kStateVectorDimension> unit;

    // Then
    EXPECT_EQ(unit.GetMean().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetMean().cols(), 1);
    EXPECT_EQ(unit.GetCovariance().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetCovariance().cols(), kStateVectorDimension);
}

TEST(MultivariateMoment, Constructor_GivenTypicalMeanAndCovarianceMatrix_ExpectSame)
{
    // Given
    const auto mean = MultivariateMoments<double, kStateVectorDimension>::MeanType::Identity();
    const auto covariance = MultivariateMoments<double, kStateVectorDimension>::CovarianceType::Identity();

    // When
    const MultivariateMoments<double, kStateVectorDimension> unit{mean, covariance};

    // Then
    EXPECT_EQ(unit.GetMean(), mean);
    EXPECT_EQ(unit.GetCovariance(), covariance);
}

TEST(MultivariateMoment, Equality)
{
    // Given
    const auto mean = MultivariateMoments<double, kStateVectorDimension>::MeanType::Identity();
    const auto covariance = MultivariateMoments<double, kStateVectorDimension>::CovarianceType::Identity();
    const MultivariateMoments<double, kStateVectorDimension> lhs;
    const MultivariateMoments<double, kStateVectorDimension> rhs{mean, covariance};

    // When/Then
    EXPECT_EQ(lhs, lhs);
    EXPECT_NE(lhs, rhs);
}
}  // namespace
}  // namespace perception
