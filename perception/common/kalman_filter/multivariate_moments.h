///
/// @file
/// @copyright Copyright (C) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_KALMAN_FILTER_MULTIVARIATE_MOMENTS_H
#define PERCEPTION_COMMON_KALMAN_FILTER_MULTIVARIATE_MOMENTS_H

#include <cstdint>

#include <Eigen/Dense>

namespace perception
{
template <typename T,
          std::int32_t kStateVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class MultivariateMoments
{
  public:
    using MeanType = Eigen::Matrix<T, kStateVectorDimension, 1>;
    using CovarianceType = Eigen::Matrix<T, kStateVectorDimension, kStateVectorDimension>;

    constexpr MultivariateMoments() : mean_{MeanType::Zero()}, covariance_{CovarianceType::Zero()} {}

    explicit constexpr MultivariateMoments(const MeanType& mean, const CovarianceType& covariance)
        : mean_{mean}, covariance_{covariance}
    {
    }

    constexpr const MeanType& GetMean() const noexcept { return mean_; }
    constexpr const CovarianceType& GetCovariance() const noexcept { return covariance_; }

  private:
    MeanType mean_;
    CovarianceType covariance_;
};

template <typename T, std::int32_t kStateVectorDimension>
constexpr bool operator==(const MultivariateMoments<T, kStateVectorDimension>& lhs,
                          const MultivariateMoments<T, kStateVectorDimension>& rhs) noexcept
{
    return ((lhs.GetMean() == rhs.GetMean()) && (lhs.GetCovariance() == rhs.GetCovariance()));
}

template <typename T, std::int32_t kStateVectorDimension>
constexpr bool operator!=(const MultivariateMoments<T, kStateVectorDimension>& lhs,
                          const MultivariateMoments<T, kStateVectorDimension>& rhs) noexcept
{
    return (!(lhs == rhs));
}

}  // namespace perception

#endif  /// PERCEPTION_COMMON_KALMAN_FILTER_MULTIVARIATE_MOMENTS_H
