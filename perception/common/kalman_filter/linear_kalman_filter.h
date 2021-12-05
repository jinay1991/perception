///
/// @file
/// @copyright Copyright (C) 2021. MIT License.
///
#ifndef PERCEPTION_COMMON_KALMAN_FILTER_LINEAR_KALMAN_FILTER_H
#define PERCEPTION_COMMON_KALMAN_FILTER_LINEAR_KALMAN_FILTER_H

#include "perception/common/kalman_filter/multivariate_moments.h"

#include <cstdint>

#include <Eigen/Dense>

namespace perception
{

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kControlVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class LinearPredictModel
{
  public:
    using TransitionModelType = Eigen::Matrix<T, kStateVectorDimension, kStateVectorDimension>;
    using ControlModelType = Eigen::Matrix<T, kStateVectorDimension, kControlVectorDimension>;
    using ProcessNoiseType = Eigen::Matrix<T, kStateVectorDimension, kStateVectorDimension>;

    constexpr LinearPredictModel()
        : transition_model_{TransitionModelType::Zero()},
          control_model_{ControlModelType::Zero()},
          process_noise_{ProcessNoiseType::Zero()}
    {
    }

    explicit constexpr LinearPredictModel(const TransitionModelType& transition_model,
                                          const ControlModelType& control_model,
                                          const ProcessNoiseType& process_noise)
        : transition_model_{transition_model}, control_model_{control_model}, process_noise_{process_noise}
    {
    }

    constexpr const TransitionModelType& GetTransitionModel() const { return transition_model_; }
    constexpr const ControlModelType& GetControlModel() const { return control_model_; }
    constexpr const ProcessNoiseType& GetProcessNoise() const { return process_noise_; }

  private:
    TransitionModelType transition_model_;
    ControlModelType control_model_;
    ProcessNoiseType process_noise_;
};

template <typename T,
          std::int32_t kStateVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class LinearPredictResult
{
  public:
    using PredictedStateType = MultivariateMoments<T, kStateVectorDimension>;

    constexpr LinearPredictResult() : predicted_state_{} {}

    explicit constexpr LinearPredictResult(const typename PredictedStateType::MeanType& mean,
                                           const typename PredictedStateType::CovarianceType& covariance)
        : predicted_state_{mean, covariance}
    {
    }

    constexpr const PredictedStateType& GetPredictedState() const noexcept { return predicted_state_; }

  private:
    PredictedStateType predicted_state_;
};

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kMeasurementVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class LinearUpdateModel
{
  public:
    using MeasurementModelType = Eigen::Matrix<T, kMeasurementVectorDimension, kStateVectorDimension>;
    using MeasurementNoiseType = Eigen::Matrix<T, kMeasurementVectorDimension, kMeasurementVectorDimension>;

    constexpr LinearUpdateModel()
        : measurement_model_{MeasurementModelType::Zero()}, measurement_noise_{MeasurementNoiseType::Zero()}
    {
    }

    explicit constexpr LinearUpdateModel(const MeasurementModelType& measurement_model,
                                         const MeasurementNoiseType& measurement_noise)
        : measurement_model_{measurement_model}, measurement_noise_{measurement_noise}
    {
    }

    constexpr const MeasurementModelType& GetMeasurementModel() const noexcept { return measurement_model_; }
    constexpr const MeasurementNoiseType& GetMeasurementNoise() const noexcept { return measurement_noise_; }

  private:
    MeasurementModelType measurement_model_;
    MeasurementNoiseType measurement_noise_;
};

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kMeasurementVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
class LinearUpdateResult
{
  public:
    using UpdatedStateType = MultivariateMoments<T, kStateVectorDimension>;
    using GainType = Eigen::Matrix<T, kStateVectorDimension, kMeasurementVectorDimension>;
    using MeasurementType = Eigen::Matrix<T, kMeasurementVectorDimension, 1>;

    constexpr LinearUpdateResult()
        : updated_state_{}, kalman_gain_{GainType::Zero()}, estimated_measurement_{MeasurementType::Zero()}
    {
    }

    explicit constexpr LinearUpdateResult(const typename UpdatedStateType::MeanType& mean,
                                          const typename UpdatedStateType::CovarianceType& covariance,
                                          const GainType& kalman_gain,
                                          const MeasurementType& estimated_measurement)
        : updated_state_{mean, covariance}, kalman_gain_{kalman_gain}, estimated_measurement_{estimated_measurement}
    {
    }

    constexpr const UpdatedStateType& GetUpdatedState() const noexcept { return updated_state_; }
    constexpr const GainType& GetKalmanGain() const noexcept { return kalman_gain_; }
    constexpr const MeasurementType& GetEstimatedMeasurement() const noexcept { return estimated_measurement_; }

  private:
    UpdatedStateType updated_state_;
    GainType kalman_gain_;
    MeasurementType estimated_measurement_;
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
template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kControlVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr LinearPredictResult<T, kStateVectorDimension> LinearPrediction(
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

    const LinearPredictResult<T, kStateVectorDimension> priori_state{x_k, P_k};
    return priori_state;
}

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kControlVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr LinearPredictResult<T, kStateVectorDimension> LinearPrediction(
    const MultivariateMoments<T, kStateVectorDimension>& previous_state,
    const Eigen::Matrix<T, kControlVectorDimension, 1>& control_vector,
    const LinearPredictModel<T, kStateVectorDimension, kControlVectorDimension>& predict_model) noexcept
{
    return LinearPrediction(previous_state.GetMean(), previous_state.GetCovariance(), control_vector, predict_model);
}

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kControlVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr LinearPredictResult<T, kStateVectorDimension> LinearPrediction(
    const LinearPredictResult<T, kStateVectorDimension>& previous_state,
    const Eigen::Matrix<T, kControlVectorDimension, 1>& control_vector,
    const LinearPredictModel<T, kStateVectorDimension, kControlVectorDimension>& predict_model) noexcept
{
    return LinearPrediction(previous_state.GetPredictedState().GetMean(),
                            previous_state.GetPredictedState().GetCovariance(),
                            control_vector,
                            predict_model);
}

template <typename T,
          std::int32_t kStateVectorDimension,
          std::int32_t kMeasurementVectorDimension,
          std::int32_t kControlVectorDimension,
          std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr LinearPredictResult<T, kStateVectorDimension> LinearPrediction(
    const LinearUpdateResult<T, kStateVectorDimension, kMeasurementVectorDimension>& previous_state,
    const Eigen::Matrix<T, kControlVectorDimension, 1>& control_vector,
    const LinearPredictModel<T, kStateVectorDimension, kControlVectorDimension>& predict_model) noexcept
{
    return LinearPrediction(previous_state.GetUpdatedState().GetMean(),
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
constexpr LinearUpdateResult<T, kStateVectorDimension, kMeasurementVectorDimension> LinearUpdate(
    const LinearPredictResult<T, kStateVectorDimension>& priori_state,
    const LinearUpdateModel<T, kStateVectorDimension, kMeasurementVectorDimension>& update_model,
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

    const LinearUpdateResult<T, kStateVectorDimension, kMeasurementVectorDimension> posteriori_state{x_k, P_k, K, z_k};
    return posteriori_state;
}

}  // namespace perception

#endif  /// PERCEPTION_COMMON_KALMAN_FILTER_LINEAR_KALMAN_FILTER_H
