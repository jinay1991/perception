///
/// @file
/// @copyright Copyright (C) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_KALMAN_FILTER_EXTENDED_KALMAN_FILTER_H
#define PERCEPTION_COMMON_KALMAN_FILTER_EXTENDED_KALMAN_FILTER_H

#include "perception/common/kalman_filter/multivariate_moments.h"

#include <cstdint>

#include <Eigen/Dense>

namespace perception
{

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kControlVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class ExtendedPredictModel
{
};

template <typename T,
          std::int32_t kStateVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class ExtendedPredictResult
{
};

template <typename T,
          std::int32_t kMeasurementVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class ExtendedUpdateModel
{
  public:
    using MeasurementFunctorType = MeasurementFunctorT;
    using MeasurementNoiseType = Eigen::Matrix<T, kMeasurementVectorDimension, kMeasurementVectorDimension>;

    constexpr ExtendedUpdateModel()
        : measurement_model_{MeasurementModelType::Zero()}, measurement_noise_{MeasurementNoiseType::Zero()}
    {
    }

    explicit constexpr ExtendedUpdateModel(const MeasurementModelType& measurement_functor,
                                           const MeasurementNoiseType& measurement_noise)
        : measurement_model_{measurement_model}, measurement_noise_{measurement_noise}
    {
    }

    constexpr const MeasurementModelType& GetMeasurementModel() const { return measurement_model_; }
    constexpr const MeasurementNoiseType& GetMeasurementNoise() const { return measurement_noise_; }

  private:
    MeasurementModelType measurement_model_;
    MeasurementNoiseType measurement_noise_;
};

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kMeasurementVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class ExtendedUpdateResult
{
};

///
/// @brief Performs prediction step of Linear Kalman filter computation given by expression,
///        x_k = (F * x) + (B * u)
///        P_k = (F * P * F_T) + Q
///
///        where, x = previous state vector at (k - 1)
///               P = previous covariance matrix at (k - 1)
///               u = control vector
///               B = control model
///               F = transition model
///               F_T = transposed transition model
///               Q = process noise
///               x_k = predicted state vector
///               P_k = predicted covariance matrix
///
template <typename T, std::int32_t kStateVectorDimension, std::int32_t kControlVectorDimension>
constexpr ExtendedPredictResult<T, kStateVectorDimension> ExtendedPrediction(
    const Eigen::Matrix<T, kStateVectorDimension, 1>& previous_state_vector,
    const Eigen::Matrix<T, kStateVectorDimension, kStateVectorDimension>& previous_covariance_matrix,
    const Eigen::Matrix<T, kControlVectorDimension, 1>& control_vector,
    const LinearPredictModel<T, kStateVectorDimension, kControlVectorDimension>& predict_model) noexcept
{
    const auto& x = previous_state_vector;
    const auto& P = previous_covariance_matrix;
    const auto& u = control_vector;
    const auto& B = predict_model.GetControlModel();
    const auto& F = predict_model.GetTransitionModel();
    const auto& F_T = F.transpose();
    const auto& Q = predict_model.GetProcessNoise();

    const auto x_k = (F * x) + (B * u);
    const auto P_k = (F * P * F_T) + Q;

    const ExtendedPredictResult<T, kStateVectorDimension> priori_state{x_k, P_k};
    return priori_state;
}

template <typename T, std::int32_t kStateVectorDimension, std::int32_t kControlVectorDimension>
constexpr ExtendedPredictResult<T, kStateVectorDimension> ExtendedPrediction(
    const MultivariateMoments<T, kStateVectorDimension>& previous_state,
    const Eigen::Matrix<T, kControlVectorDimension, 1>& control_vector,
    const LinearPredictModel<T, kStateVectorDimension, kControlVectorDimension>& predict_model) noexcept
{

    return ExtendedPrediction(previous_state.GetMean(), previous_state.GetCovariance(), control_vector, predict_model);
}

template <typename T, std::int32_t kStateVectorDimension, std::int32_t kControlVectorDimension>
constexpr ExtendedPredictResult<T, kStateVectorDimension> ExtendedPrediction(
    const ExtendedPredictResult<T, kStateVectorDimension>& previous_state,
    const Eigen::Matrix<T, kControlVectorDimension, 1>& control_vector,
    const LinearPredictModel<T, kStateVectorDimension, kControlVectorDimension>& predict_model) noexcept
{
    return ExtendedPrediction(previous_state.GetPredictedState().GetMean(),
                              previous_state.GetPredictedState().GetCovariance(),
                              control_vector,
                              predict_model);
}

template <typename T, std::int32_t kStateVectorDimension, std::int32_t kControlVectorDimension>
constexpr ExtendedPredictResult<T, kStateVectorDimension> ExtendedPrediction(
    const ExtendedUpdateResult<T, kStateVectorDimension>& previous_state,
    const Eigen::Matrix<T, kControlVectorDimension, 1>& control_vector,
    const LinearPredictModel<T, kStateVectorDimension, kControlVectorDimension>& predict_model) noexcept
{
    return ExtendedPrediction(previous_state.GetUpdatedState().GetMean(),
                              previous_state.GetUpdatedState().GetCovariance(),
                              control_vector,
                              predict_model);
}

///
/// @brief Perform Update step of Linear Kalman filter computations given by expressions,
///        K = P * H_T * (R + H * P * H_T)^-1
///        x_k = x + (K * (z - H * x))
///        P_k = ((I - K * H) * P * (I - K * H)^T) + (K * R * K_T);
///        z_k = H * x
///
///        where, x = predicted state vector
///               P = predicted covariance matrix
///               H = measurement model
///               H_T = transpose of measurement model
///               R = measurement noise
///               z = measurement vector
///               K = kalman gain
///               x_k = updated state vector
///               P_k = updated covariance matrix
///               z_k = estimated measurement vector
///
template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kMeasurementVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr ExtendedUpdateResult<T, kStateVectorDimension, kMeasurementVectorDimension> ExtendedUpdate(
    const ExtendedPredictResult<T, kStateVectorDimension>& priori_state,
    const ExtendedUpdateModel<T, kStateVectorDimension, kMeasurementVectorDimension>& update_model,
    const Eigen::Matrix<T, kMeasurementVectorDimension, 1>& measurement_vector) noexcept
{
    const auto& x = priori_state.GetPredictedState().GetMean();
    const auto& P = priori_state.GetPredictedState().GetCovariance();
    const auto& H = update_model.GetMeasurementModel();
    const auto& H_T = H.transpose();
    const auto& R = update_model.GetMeasurementNoise();
    const auto& z = measurement_vector;
    const auto& I = Eigen::Matrix<T, kStateVectorDimension, kStateVectorDimension>::Identity();

    const auto K = P * H_T * (R + (H * P * H_T)).inverse();
    const auto x_k = x + (K * (z - (H * x)));
    const auto P_k = ((I - K * H) * P * (I - K * H).transpose()) + (K * R * K.transpose());
    const auto z_k = H * x;

    const ExtendedUpdateResult<T, kStateVectorDimension, kMeasurementVectorDimension> posteriori_state{
        x_k, P_k, K, z_k};
    return posteriori_state;
}

}  // namespace perception

#endif  /// PERCEPTION_COMMON_KALMAN_FILTER_EXTENDED_KALMAN_FILTER_H
