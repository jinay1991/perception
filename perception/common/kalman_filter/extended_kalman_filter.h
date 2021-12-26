///
/// @file
/// @copyright Copyright (C) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_KALMAN_FILTER_EXTENDED_KALMAN_FILTER_H
#define PERCEPTION_COMMON_KALMAN_FILTER_EXTENDED_KALMAN_FILTER_H

#include "perception/common/kalman_filter/multivariate_moments.h"

#include <cstdint>
#include <functional>

#include <Eigen/Dense>

namespace perception
{

template <typename T,
          std::int32_t kStateVectorDimension,
          typename TransitionFunctorT,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class ExtendedPredictModel
{
  public:
    using TransitionFunctorType = TransitionFunctorT;
    using ProcessNoiseType = Eigen::Matrix<T, kStateVectorDimension, kStateVectorDimension>;

    constexpr ExtendedPredictModel() : transition_functor_{}, process_noise_{ProcessNoiseType::Zero()} {}

    explicit constexpr ExtendedPredictModel(const TransitionFunctorType& transition_functor,
                                            const ProcessNoiseType& process_noise)
        : transition_functor_{transition_functor}, process_noise_{process_noise}
    {
    }

    constexpr const TransitionFunctorType& GetTransitionFunctor() const noexcept { return transition_functor_; }
    constexpr const ProcessNoiseType& GetProcessNoise() const noexcept { return process_noise_; }

  private:
    TransitionFunctorType transition_functor_;
    ProcessNoiseType process_noise_;
};

template <typename T,
          std::int32_t kStateVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class ExtendedPredictResult
{
  public:
    using PredictedStateType = MultivariateMoments<T, kStateVectorDimension>;

    constexpr ExtendedPredictResult() : predicted_state_{} {}

    constexpr const PredictedStateType& PredictedStateType() const noexcept { return predicted_state_; }

  private:
    PredictedStateType predicted_state_;
};

template <typename T,
          std::int32_t kMeasurementVectorDimension,
          typename MeasurementFunctorT,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class ExtendedUpdateModel
{
  public:
    using MeasurementFunctorType = MeasurementFunctorT;
    using MeasurementNoiseType = Eigen::Matrix<T, kMeasurementVectorDimension, kMeasurementVectorDimension>;

    explicit constexpr ExtendedUpdateModel(const MeasurementFunctorType& measurement_functor,
                                           const MeasurementNoiseType& measurement_noise)
        : measurement_functor_{measurement_functor}, measurement_noise_{measurement_noise}
    {
    }

    constexpr const MeasurementFunctorType& GetMeasurementFunctor() const { return measurement_functor_; }
    constexpr const MeasurementNoiseType& GetMeasurementNoise() const { return measurement_noise_; }

  private:
    MeasurementFunctorType measurement_functor_;
    MeasurementNoiseType measurement_noise_;
};

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kMeasurementVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class ExtendedUpdateResult
{
  public:
    using UpdatedStateType = MultivariateMoments<T, kStateVectorDimension>;
    using GainType = Eigen::Matrix<T, kStateVectorDimension, kMeasurementVectorDimension>;
    using MeasurementType = Eigen::Matrix<T, kMeasurementVectorDimension, 1>;
    using CrossCovarianceType = Eigen::Matrix<T, kMeasurementVectorDimension, kMeasurementVectorDimension>;

    constexpr ExtendedUpdateResult()
        : updated_state_{},
          kalman_gain_{GainType::Zero()},
          estimated_measurement_{MeasurementType::Zero()},
          cross_covariance_{CrossCovarianceType::Zero()}
    {
    }

    explicit constexpr ExtendedUpdateResult(const UpdatedStateType& updated_state,
                                            const GainType& kalman_gain,
                                            const MeasurementType& estimated_measurement,
                                            const CrossCovarianceType& cross_covariance)
        : updated_state_{updated_state},
          kalman_gain_{kalman_gain},
          estimated_measurement_{estimated_measurement},
          cross_covariance_{cross_covariance}
    {
    }
    constexpr const UpdatedStateType& GetUpdatedState() const noexcept { return updated_state_; }
    constexpr const GainType& GetKalmanGain() const noexcept { return kalman_gain_; }
    constexpr const MeasurementType& GetEstimatedMeasurement() const noexcept { return estimated_measurement_; }
    constexpr const CrossCovarianceType& GetCrossCovariance() const noexcept { return cross_covariance_; }

  private:
    UpdatedStateType updated_state_;
    GainType kalman_gain_;
    MeasurementType estimated_measurement_;
    CrossCovarianceType cross_covariance_;
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
///        K = P * H_T * S^-1
///        x_k = x + (K * y)
///        P_k = ((I - K * H) * P * (I - K * H)^T) + (K * R * K_T);
///        z_k = H * x
///
///        where, x = predicted state vector
///               P = predicted covariance matrix
///               H = measurement model
///               H_T = transpose of measurement model
///               R = measurement noise
///               z = measurement vector
///               y = measurement residual (z - (H * x))
///               S = measurement residual covariance (R + (H * P * H_T))
///               I = identity covariance matrix
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
    const auto& y = z - (H * x);
    const auto& S = R + (H * P * H_T);
    const auto& I = Eigen::Matrix<T, kStateVectorDimension, kStateVectorDimension>::Identity();

    const auto K = P * H_T * S.inverse();
    const auto x_k = x + (K * y);
    const auto P_k = ((I - K * H) * P * (I - K * H).transpose()) + (K * R * K.transpose());
    const auto z_k = H * x;

    const ExtendedUpdateResult<T, kStateVectorDimension, kMeasurementVectorDimension> posteriori_state{
        x_k, P_k, K, z_k};
    return posteriori_state;
}

}  // namespace perception

#endif  /// PERCEPTION_COMMON_KALMAN_FILTER_EXTENDED_KALMAN_FILTER_H
