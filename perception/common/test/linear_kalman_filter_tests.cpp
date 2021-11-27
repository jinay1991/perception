///
/// @file
/// @copyright Copyright (C) 2021. MIT License.
///
#include "perception/common/linear_kalman_filter.h"

#include <gtest/gtest.h>

namespace perception
{
namespace
{
constexpr double kTolerance{1E-5};
constexpr std::int32_t kStateVectorDimension{2};
constexpr std::int32_t kMeasurementVectorDimension{1};
constexpr std::int32_t kControlVectorDimension{1};

class LinearKalmanFilterFixture : public ::testing::Test
{
  public:
    LinearKalmanFilterFixture()
        : control{},
          measurement{MeasurementVectorType::Zero()},
          previous_state{MeanType::Zero(), CovarianceType::Identity()},
          transition_model{(TransitionModelType() << 1., 0.5, 0., 1.).finished()},
          control_model{(ControlModelType() << 0.125, 0.5).finished()},
          process_noise{(ProcessNoiseType() << 3.125E-3, 1.25E-2, 1.25E-2, 5.E-2).finished()},
          measurement_model{MeasurementModelType::Identity()},
          measurement_noise{(MeasurementNoiseType() << 10.4).finished()},
          predict_model{transition_model, control_model, process_noise},
          update_model{measurement_model, measurement_noise}
    {
        control.setConstant(0.5);
    }

  protected:
    using MeasurementVectorType = Eigen::Matrix<double, kMeasurementVectorDimension, 1>;
    using ControlVectorType = Eigen::Matrix<double, kControlVectorDimension, 1>;

    using MeanType = Eigen::Matrix<double, kStateVectorDimension, 1>;
    using CovarianceType = Eigen::Matrix<double, kStateVectorDimension, kStateVectorDimension>;
    using TransitionModelType = Eigen::Matrix<double, kStateVectorDimension, kStateVectorDimension>;
    using ControlModelType = Eigen::Matrix<double, kStateVectorDimension, kControlVectorDimension>;
    using ProcessNoiseType = Eigen::Matrix<double, kStateVectorDimension, kStateVectorDimension>;
    using MeasurementModelType = Eigen::Matrix<double, kMeasurementVectorDimension, kStateVectorDimension>;
    using MeasurementNoiseType = Eigen::Matrix<double, kMeasurementVectorDimension, kMeasurementVectorDimension>;

    using GainType = Eigen::Matrix<double, kStateVectorDimension, kMeasurementVectorDimension>;
    using MeasurementType = Eigen::Matrix<double, kMeasurementVectorDimension, 1>;

    ControlVectorType control;
    MeasurementVectorType measurement;

    const MultivariateMoments<double, static_cast<std::size_t>(kStateVectorDimension)> previous_state;
    const TransitionModelType transition_model;
    const ControlModelType control_model;
    const ProcessNoiseType process_noise;
    const MeasurementModelType measurement_model;
    const MeasurementNoiseType measurement_noise;

    const LinearPredictModel<double, kStateVectorDimension, kControlVectorDimension> predict_model;
    const LinearUpdateModel<double, kStateVectorDimension, kMeasurementVectorDimension> update_model;
};

TEST(LinearPredictModel, DefaultConstructor_GivenTypicalDimensions_ExpectSame)
{
    // When
    const LinearPredictModel<double, kStateVectorDimension, kControlVectorDimension> unit;

    // Then
    EXPECT_EQ(unit.GetTransitionModel().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetTransitionModel().cols(), kStateVectorDimension);
    EXPECT_EQ(unit.GetControlModel().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetControlModel().cols(), kControlVectorDimension);
    EXPECT_EQ(unit.GetProcessNoise().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetProcessNoise().cols(), kStateVectorDimension);
}

TEST(LinearPredictModel, DefaultConstructor_GivenTypicalDimensions_ExpectInitialValues)
{
    // When
    using ModelType = LinearPredictModel<double, kStateVectorDimension, kControlVectorDimension>;
    const ModelType unit;

    // Then
    EXPECT_EQ(unit.GetTransitionModel(), ModelType::TransitionModelType::Zero());
    EXPECT_EQ(unit.GetControlModel(), ModelType::ControlModelType::Zero());
    EXPECT_EQ(unit.GetProcessNoise(), ModelType::ProcessNoiseType::Zero());
}

TEST(LinearPredictModel, Constructor_GivenTypicalInputs_ExpectSame)
{
    // Given
    using ModelType = LinearPredictModel<double, kStateVectorDimension, kControlVectorDimension>;
    const auto transition_model = ModelType::TransitionModelType::Identity();
    const auto control_model = ModelType::ControlModelType::Identity();
    const auto process_noise = ModelType::ProcessNoiseType::Identity();

    // When
    const ModelType unit{transition_model, control_model, process_noise};

    // Then
    EXPECT_EQ(unit.GetTransitionModel(), transition_model);
    EXPECT_EQ(unit.GetControlModel(), control_model);
    EXPECT_EQ(unit.GetProcessNoise(), process_noise);
}

TEST(LinearUpdateModel, DefaultConstructor_GivenTypicalDimensions_ExpectSame)
{
    // When
    const LinearUpdateModel<double, kStateVectorDimension, kMeasurementVectorDimension> unit;

    // Then
    EXPECT_EQ(unit.GetMeasurementModel().rows(), kMeasurementVectorDimension);
    EXPECT_EQ(unit.GetMeasurementModel().cols(), kStateVectorDimension);
    EXPECT_EQ(unit.GetMeasurementNoise().rows(), kMeasurementVectorDimension);
    EXPECT_EQ(unit.GetMeasurementNoise().cols(), kMeasurementVectorDimension);
}

TEST(LinearUpdateModel, DefaultConstructor_GivenTypicalDimensions_ExpectInitialValues)
{
    // When
    using ModelType = LinearUpdateModel<double, kStateVectorDimension, kMeasurementVectorDimension>;
    const ModelType unit;

    // Then
    EXPECT_EQ(unit.GetMeasurementModel(), ModelType::MeasurementModelType::Zero());
    EXPECT_EQ(unit.GetMeasurementModel(), ModelType::MeasurementModelType::Zero());
    EXPECT_EQ(unit.GetMeasurementNoise(), ModelType::MeasurementNoiseType::Zero());
    EXPECT_EQ(unit.GetMeasurementNoise(), ModelType::MeasurementNoiseType::Zero());
}

TEST(LinearUpdateModel, Constructor_GivenTypicalInputs_ExpectSame)
{
    // Given
    using ModelType = LinearUpdateModel<double, kStateVectorDimension, kMeasurementVectorDimension>;
    const auto measurement_model = ModelType::MeasurementModelType::Identity();
    const auto measurement_noise = ModelType::MeasurementNoiseType::Identity();

    // When
    const ModelType unit{measurement_model, measurement_noise};

    // Then
    EXPECT_EQ(unit.GetMeasurementModel(), measurement_model);
    EXPECT_EQ(unit.GetMeasurementNoise(), measurement_noise);
}

TEST(LinearPredictResult, DefaultConstructor_GivenTypicalDimensions_ExpectSame)
{
    // When
    const LinearPredictResult<double, kStateVectorDimension> unit;

    // Then
    EXPECT_EQ(unit.GetPrioriState().GetMean().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetPrioriState().GetMean().cols(), 1);
    EXPECT_EQ(unit.GetPrioriState().GetCovariance().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetPrioriState().GetCovariance().cols(), kStateVectorDimension);
}

TEST(LinearPredictResult, DefaultConstructor_GivenTypicalDimensions_ExpectInitialValues)
{
    // When
    using ResultType = LinearPredictResult<double, kStateVectorDimension>;
    const ResultType unit;

    // Then
    EXPECT_EQ(unit.GetPrioriState().GetMean(), ResultType::PrioriState::MeanType::Zero());
    EXPECT_EQ(unit.GetPrioriState().GetCovariance(), ResultType::PrioriState::CovarianceType::Zero());
}

TEST(LinearPredictResult, Constructor_GivenTypicalInputs_ExpectSame)
{
    // Given
    using ResultType = LinearPredictResult<double, kStateVectorDimension>;
    const auto mean = ResultType::PrioriState::MeanType::Identity();
    const auto covariance = ResultType::PrioriState::CovarianceType::Identity();

    // When
    const ResultType unit{mean, covariance};

    // Then
    EXPECT_EQ(unit.GetPrioriState().GetMean(), mean);
    EXPECT_EQ(unit.GetPrioriState().GetCovariance(), covariance);
}

TEST(LinearUpdateResult, DefaultConstructor_GivenTypicalDimensions_ExpectSame)
{
    // When
    const LinearUpdateResult<double, kStateVectorDimension, kMeasurementVectorDimension> unit;

    // Then
    EXPECT_EQ(unit.GetPosterioriState().GetMean().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetPosterioriState().GetMean().cols(), 1);
    EXPECT_EQ(unit.GetPosterioriState().GetCovariance().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetPosterioriState().GetCovariance().cols(), kStateVectorDimension);
    EXPECT_EQ(unit.GetKalmanGain().rows(), kStateVectorDimension);
    EXPECT_EQ(unit.GetKalmanGain().cols(), kMeasurementVectorDimension);
    EXPECT_EQ(unit.GetEstimatedMeasurement().rows(), kMeasurementVectorDimension);
    EXPECT_EQ(unit.GetEstimatedMeasurement().cols(), 1);
}

TEST(LinearUpdateResult, DefaultConstructor_GivenTypicalDimensions_ExpectInitialValues)
{
    // When
    using ResultType = LinearUpdateResult<double, kStateVectorDimension, kMeasurementVectorDimension>;
    const ResultType unit;

    // Then
    EXPECT_EQ(unit.GetPosterioriState().GetMean(), ResultType::PosterioriState::MeanType::Zero());
    EXPECT_EQ(unit.GetPosterioriState().GetCovariance(), ResultType::PosterioriState::CovarianceType::Zero());
    EXPECT_EQ(unit.GetKalmanGain(), ResultType::GainType::Zero());
    EXPECT_EQ(unit.GetEstimatedMeasurement(), ResultType::MeasurementType::Zero());
}

TEST(LinearUpdateResult, Constructor_GivenTypicalInputs_ExpectSame)
{
    // Given
    using ResultType = LinearUpdateResult<double, kStateVectorDimension, kMeasurementVectorDimension>;
    const auto mean = ResultType::PosterioriState::MeanType::Identity();
    const auto covariance = ResultType::PosterioriState::CovarianceType::Identity();
    const auto kalman_gain = ResultType::GainType::Identity();
    const auto measurement = ResultType::MeasurementType::Identity();

    // When
    const ResultType unit{mean, covariance, kalman_gain, measurement};

    // Then
    EXPECT_EQ(unit.GetPosterioriState().GetMean(), mean);
    EXPECT_EQ(unit.GetPosterioriState().GetCovariance(), covariance);
    EXPECT_EQ(unit.GetKalmanGain(), kalman_gain);
    EXPECT_EQ(unit.GetEstimatedMeasurement(), measurement);
}

TEST_F(LinearKalmanFilterFixture, LinearPrediction_GivenTypicalPredictModel_ExpectPrioriState)
{
    // When
    const LinearPredictResult<double, kStateVectorDimension> priori_state =
        LinearPrediction(previous_state, control, predict_model);

    // Then
    const auto mean = priori_state.GetPrioriState().GetMean();
    const auto covariance = priori_state.GetPrioriState().GetCovariance();
    EXPECT_EQ(mean.rows(), 2UL);
    EXPECT_EQ(mean.cols(), 1UL);
    EXPECT_EQ(covariance.rows(), 2UL);
    EXPECT_EQ(covariance.cols(), 2UL);
    EXPECT_NEAR(mean(0, 0), 0.0625, kTolerance);
    EXPECT_NEAR(mean(1, 0), 0.25, kTolerance);
    EXPECT_NEAR(covariance(0, 0), 1.25313, kTolerance);
    EXPECT_NEAR(covariance(0, 1), 0.5125, kTolerance);
    EXPECT_NEAR(covariance(1, 0), 0.5125, kTolerance);
    EXPECT_NEAR(covariance(1, 1), 1.05, kTolerance);
}

TEST_F(LinearKalmanFilterFixture, LinearPrediction_GivenTypicalPreviousPrioriState_ExpectPrioriState)
{
    // Given
    const LinearPredictResult<double, kStateVectorDimension> previous_priori_state{
        (MeanType() << 0.0625, 0.25).finished(), (CovarianceType() << 1.25313, 0.5125, 0.5125, 1.05).finished()};

    // When
    const auto priori_state = LinearPrediction(previous_priori_state, control, predict_model);

    // Then
    const auto mean = priori_state.GetPrioriState().GetMean();
    const auto covariance = priori_state.GetPrioriState().GetCovariance();
    EXPECT_EQ(mean.rows(), 2UL);
    EXPECT_EQ(mean.cols(), 1UL);
    EXPECT_EQ(covariance.rows(), 2UL);
    EXPECT_EQ(covariance.cols(), 2UL);
    EXPECT_NEAR(mean(0, 0), 0.25, kTolerance);
    EXPECT_NEAR(mean(1, 0), 0.5, kTolerance);
    EXPECT_NEAR(covariance(0, 0), 2.03125, kTolerance);
    EXPECT_NEAR(covariance(0, 1), 1.05, kTolerance);
    EXPECT_NEAR(covariance(1, 0), 1.05, kTolerance);
    EXPECT_NEAR(covariance(1, 1), 1.10, kTolerance);
}

TEST_F(LinearKalmanFilterFixture, LinearPrediction_GivenTypicalPreviousPosterioriState_ExpectPrioriState)
{
    // Given
    const LinearUpdateResult<double, kStateVectorDimension, kMeasurementVectorDimension> previous_posteriori_state{
        (MeanType() << 0.055779, 0.247251).finished(),
        (CovarianceType() << 1.11837, 0.457388, 0.457388, 1.02746).finished(),
        (GainType() << 0.107536, 0.0439796).finished(),
        (MeasurementType() << 0.0635).finished()};

    // When
    const auto priori_state = LinearPrediction(previous_posteriori_state, control, predict_model);

    // Then
    const auto mean = priori_state.GetPrioriState().GetMean();
    const auto covariance = priori_state.GetPrioriState().GetCovariance();
    EXPECT_EQ(mean.rows(), 2UL);
    EXPECT_EQ(mean.cols(), 1UL);
    EXPECT_EQ(covariance.rows(), 2UL);
    EXPECT_EQ(covariance.cols(), 2UL);
    EXPECT_NEAR(mean(0, 0), 0.24190449999999999, kTolerance);
    EXPECT_NEAR(mean(1, 0), 0.497251, kTolerance);
    EXPECT_NEAR(covariance(0, 0), 1.8357480000000002, kTolerance);
    EXPECT_NEAR(covariance(0, 1), 0.98361799999999999, kTolerance);
    EXPECT_NEAR(covariance(1, 0), 0.98361799999999999, kTolerance);
    EXPECT_NEAR(covariance(1, 1), 1.0774600000000001, kTolerance);
}

TEST_F(LinearKalmanFilterFixture, LinearUpdate_GivenTypicalPrioriState_ExpectPosterioriState)
{
    // Given
    const LinearPredictResult<double, kStateVectorDimension> priori_state =
        LinearPrediction(previous_state, control, predict_model);

    // When
    const LinearUpdateResult<double, kStateVectorDimension, kMeasurementVectorDimension> posteriori_state =
        LinearUpdate(priori_state, update_model, measurement);

    // Then
    const auto mean = posteriori_state.GetPosterioriState().GetMean();
    const auto covariance = posteriori_state.GetPosterioriState().GetCovariance();
    const auto gain = posteriori_state.GetKalmanGain();
    const auto estimated_measurement = posteriori_state.GetEstimatedMeasurement();
    EXPECT_EQ(mean.rows(), 2UL);
    EXPECT_EQ(mean.cols(), 1UL);
    EXPECT_EQ(covariance.rows(), 2UL);
    EXPECT_EQ(covariance.cols(), 2UL);
    EXPECT_EQ(gain.rows(), 2UL);
    EXPECT_EQ(gain.cols(), 1UL);
    EXPECT_EQ(estimated_measurement.rows(), 1UL);
    EXPECT_EQ(estimated_measurement.cols(), 1UL);
    EXPECT_NEAR(mean(0, 0), 0.055779, kTolerance);
    EXPECT_NEAR(mean(1, 0), 0.247251, kTolerance);
    EXPECT_NEAR(covariance(0, 0), 1.11837, kTolerance);
    EXPECT_NEAR(covariance(0, 1), 0.457388, kTolerance);
    EXPECT_NEAR(covariance(1, 0), 0.457388, kTolerance);
    EXPECT_NEAR(covariance(1, 1), 1.02746, kTolerance);
    EXPECT_NEAR(gain(0, 0), 0.107536, kTolerance);
    EXPECT_NEAR(gain(1, 0), 0.0439796, kTolerance);
    EXPECT_NEAR(estimated_measurement(0, 0), 0.0625, kTolerance);
}

TEST_F(LinearKalmanFilterFixture,
       LinearUpdate_GivenTypicalPrioriStateAfterSeveralPredictUpdateCycles_ExpectPosterioriState)
{
    // Given
    auto priori_state = LinearPrediction(previous_state, control, predict_model);
    auto posteriori_state = LinearUpdate(priori_state, update_model, measurement);
    priori_state = LinearPrediction(posteriori_state, control, predict_model);

    // When
    posteriori_state = LinearUpdate(priori_state, update_model, measurement);

    // Then
    const auto mean = posteriori_state.GetPosterioriState().GetMean();
    const auto covariance = posteriori_state.GetPosterioriState().GetCovariance();
    const auto gain = posteriori_state.GetKalmanGain();
    const auto estimated_measurement = posteriori_state.GetEstimatedMeasurement();
    EXPECT_EQ(mean.rows(), 2UL);
    EXPECT_EQ(mean.cols(), 1UL);
    EXPECT_EQ(covariance.rows(), 2UL);
    EXPECT_EQ(covariance.cols(), 2UL);
    EXPECT_EQ(gain.rows(), 2UL);
    EXPECT_EQ(gain.cols(), 1UL);
    EXPECT_EQ(estimated_measurement.rows(), 1UL);
    EXPECT_EQ(estimated_measurement.cols(), 1UL);
    EXPECT_NEAR(mean(0, 0), 0.20561134407982429, kTolerance);
    EXPECT_NEAR(mean(1, 0), 0.47780482447624162, kTolerance);
    EXPECT_NEAR(covariance(0, 0), 1.5603276917440725, kTolerance);
    EXPECT_NEAR(covariance(0, 1), 0.83604453027610437, kTolerance);
    EXPECT_NEAR(covariance(1, 0), 0.83604453027610437, kTolerance);
    EXPECT_NEAR(covariance(1, 1), 0.9983884578471145, kTolerance);
    EXPECT_NEAR(gain(0, 0), 0.1500315088215454, kTolerance);
    EXPECT_NEAR(gain(1, 0), 0.080388897141933105, kTolerance);
    EXPECT_NEAR(estimated_measurement(0, 0), 0.24190466613032985, kTolerance);
}

}  // namespace
}  // namespace perception
