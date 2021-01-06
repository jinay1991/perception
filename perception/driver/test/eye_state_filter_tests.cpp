///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#include "perception/driver/eye_state_filter.h"
#include "perception/driver/test/support/mocks/data_source_mock.h"
#include "perception/driver/test/support/mocks/parameter_handler_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <cmath>

namespace perception
{
namespace
{
using namespace std::chrono_literals;
using ::testing::Return;

const std::chrono::milliseconds kEyeBlinkDuration{
    static_cast<std::uint32_t>(std::floor(1.0 / kMaxEyeBlinkRate.value()))};

class EyeStateFilterFixture : public ::testing::Test
{
  public:
    EyeStateFilterFixture()
        : mocked_data_source_{},
          mocked_parameter_handler_{},
          eye_state_filter_{mocked_parameter_handler_, mocked_data_source_},
          delta_duration_{40ms},
          eye_blink_duration_{kEyeBlinkDuration}
    {
    }

  protected:
    void SetUp() override
    {
        EXPECT_CALL(mocked_parameter_handler_, GetMinEyeBlinkRate()).WillRepeatedly(Return(kMinEyeBlinkRate));
        EXPECT_CALL(mocked_parameter_handler_, GetMaxEyeBlinkRate()).WillRepeatedly(Return(kMaxEyeBlinkRate));
        EXPECT_CALL(mocked_parameter_handler_, GetMinEyeLidOpening()).WillRepeatedly(Return(kMinEyeLidOpening));
        EXPECT_CALL(mocked_parameter_handler_, GetMaxEyeLidOpening()).WillRepeatedly(Return(kMaxEyeLidOpening));

        EXPECT_CALL(mocked_data_source_, IsFaceVisible()).WillRepeatedly(Return(true));
        EXPECT_CALL(mocked_data_source_, IsEyeVisible()).WillRepeatedly(Return(true));
        EXPECT_CALL(mocked_data_source_, GetEyeLidOpening()).WillRepeatedly(Return(kMaxEyeLidOpening));
        EXPECT_CALL(mocked_data_source_, GetEyeBlinkRate()).WillRepeatedly(Return(kMaxEyeBlinkRate));
        EXPECT_CALL(mocked_data_source_, GetEyeBlinkDuration()).WillRepeatedly(Return(eye_blink_duration_));
    }

    void RunOnce() { eye_state_filter_.Step(); }

    void RunForDuration(const EyeState eye_state, const std::chrono::milliseconds duration)
    {
        for (auto time_passed = 0ms; time_passed < duration; time_passed += delta_duration_)
        {
            RunOnce();
        }
    }

    EyeState GetFilteredEyeState() const { return eye_state_filter_.GetFilteredEyeState(); }

    ::testing::NiceMock<mock::DataSourceMock> mocked_data_source_;

  private:
    ::testing::NiceMock<mock::ParameterHandlerMock> mocked_parameter_handler_;
    EyeStateFilter eye_state_filter_;
    std::chrono::milliseconds delta_duration_;
    const std::chrono::milliseconds eye_blink_duration_;
};

template <typename T>
class EyeStateFilterFixtureT : public EyeStateFilterFixture, public ::testing::WithParamInterface<T>
{
};

TEST_F(EyeStateFilterFixture, EyeStateFilter_ExpectInitialValues)
{
    // Then
    EXPECT_THAT(GetFilteredEyeState(), EyeState::kInvalid);
}

struct TestEyeStateParam
{
    // Given
    bool face_visibility;
    bool eye_visibility;
    units::length::millimeter_t eye_lid_opening;
    units::frequency::hertz_t eye_blink_rate;

    // Then
    EyeState eye_state;
};

using EyeStateFilterFixture_WithEyeState = EyeStateFilterFixtureT<TestEyeStateParam>;

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    EyeStateFilter,
    EyeStateFilterFixture_WithEyeState,
    ::testing::Values(
        //                face_visible, eye_visible,         eye_lid_opening,            eye_blink_rate, (expected) eye_state
        TestEyeStateParam{        true,        true,       kMinEyeLidOpening,          kMaxEyeBlinkRate, EyeState::kEyesClosed },
        TestEyeStateParam{        true,       false,       kMinEyeLidOpening,          kMaxEyeBlinkRate, EyeState::kEyesUnknown},
        TestEyeStateParam{        true,        true,       kMinEyeLidOpening,  kMaxEyeBlinkRate + 10_Hz, EyeState::kEyesUnknown},
        TestEyeStateParam{        true,        true,       kMinEyeLidOpening,          kMaxEyeBlinkRate, EyeState::kEyesClosed },
        TestEyeStateParam{        true,        true,       kMaxEyeLidOpening,          kMaxEyeBlinkRate, EyeState::kEyesOpen   },
        TestEyeStateParam{        true,        true, kMaxEyeLidOpening / 2.0,          kMaxEyeBlinkRate, EyeState::kEyesClosed },
        TestEyeStateParam{       false,        true, kMaxEyeLidOpening / 2.0,          kMaxEyeBlinkRate, EyeState::kEyesUnknown}
));
// clang-format on

TEST_P(EyeStateFilterFixture_WithEyeState, EyeStateFilter_GiveTypicalFaceTrackingData_ExpectDeterminedEyeState)
{
    // Given
    const auto param = GetParam();
    const std::chrono::milliseconds eye_blink_duration =
        std::chrono::seconds{static_cast<std::uint32_t>(std::floor(1.0 / param.eye_blink_rate.value()))};
    EXPECT_CALL(mocked_data_source_, IsFaceVisible()).WillRepeatedly(Return(param.face_visibility));
    EXPECT_CALL(mocked_data_source_, IsEyeVisible()).WillRepeatedly(Return(param.eye_visibility));
    EXPECT_CALL(mocked_data_source_, GetEyeLidOpening()).WillRepeatedly(Return(param.eye_lid_opening));
    EXPECT_CALL(mocked_data_source_, GetEyeBlinkRate()).WillRepeatedly(Return(param.eye_blink_rate));
    EXPECT_CALL(mocked_data_source_, GetEyeBlinkDuration()).WillRepeatedly(Return(eye_blink_duration));

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetFilteredEyeState(), param.eye_state);
}
}  // namespace
}  // namespace perception
