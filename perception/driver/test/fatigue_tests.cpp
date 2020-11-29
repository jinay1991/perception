///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/fatigue.h"
#include "perception/driver/parameter_handler.h"
#include "perception/driver/test/support/mocks/data_source_mock.h"
#include "perception/driver/test/support/mocks/parameter_handler_mock.h"
#include "perception/driver/test/support/operators.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <units.h>

namespace perception
{
namespace
{
using ::testing::Field;
using ::testing::Return;

class FatigueFixture : public ::testing::Test
{
  public:
    FatigueFixture()
        : mocked_data_source_{}, mocked_parameter_handler_{}, fatigue_{mocked_parameter_handler_, mocked_data_source_}
    {
    }

  protected:
    void SetUp() override
    {
        EXPECT_CALL(mocked_parameter_handler_, GetMaxEyeLidOpening()).WillRepeatedly(Return(kMaxEyeLidOpening));
        EXPECT_CALL(mocked_parameter_handler_, GetMinEyeLidOpening()).WillRepeatedly(Return(kMinEyeLidOpening));
        EXPECT_CALL(mocked_parameter_handler_, GetEyeBlinkRate()).WillRepeatedly(Return(kMaxEyeBlinkRate));

        fatigue_.Init();
    }

    void TearDown() override { fatigue_.Shutdown(); }
    void RunOnce() { fatigue_.ExecuteStep(); }

    const FatigueMessage& GetFatigueMessage() const { return fatigue_.GetFatigueMessage(); }

    ::testing::StrictMock<DataSourceMock> mocked_data_source_;

  private:
    ::testing::StrictMock<ParameterHandlerMock> mocked_parameter_handler_;
    Fatigue fatigue_;
};
template <typename T>
class FatigueFixtureT : public FatigueFixture, public ::testing::WithParamInterface<T>
{
};

struct TestEyeStateParam
{
    // Given
    FaceTracking face_tracking;

    // Then
    EyeState eye_state;
};

using FatigueFixture_WithEyeState = FatigueFixtureT<TestEyeStateParam>;

// clang-format off
INSTANTIATE_TEST_CASE_P(
    Fatigue, 
    FatigueFixture_WithEyeState, 
    ::testing::Values(
        //                  eye_visible, eye_lid_opening, eye_blink_rate, (expected) eye_state
        TestEyeStateParam{{       true,          1.1_mm,         1.0_Hz}, EyeState::kEyesOpen},
        TestEyeStateParam{{      false,          1.1_mm,         1.0_Hz}, EyeState::kEyesUnknown},
        TestEyeStateParam{{       true,          1.1_mm,        11.0_Hz}, EyeState::kEyesUnknown},
        TestEyeStateParam{{       true,          1.0_mm,         1.0_Hz}, EyeState::kEyesClosed},
        TestEyeStateParam{{       true,         10.0_mm,         1.0_Hz}, EyeState::kEyesClosed},
        TestEyeStateParam{{       true,          5.0_mm,         1.0_Hz}, EyeState::kEyesOpen}
));
// clang-format on

TEST_P(FatigueFixture_WithEyeState, Fatigue_GiveTypicalFaceTracking_ExpectUpdatedFatigue)
{
    // Given
    const auto param = GetParam();
    EXPECT_CALL(mocked_data_source_, IsEyeVisible()).WillRepeatedly(Return(param.face_tracking.eye_visibility));
    EXPECT_CALL(mocked_data_source_, GetEyeLidOpening()).WillRepeatedly(Return(param.face_tracking.eye_lid_opening));
    EXPECT_CALL(mocked_data_source_, GetEyeBlinkRate()).WillRepeatedly(Return(param.face_tracking.eye_blink_rate));

    // When
    RunOnce();

    // Then
    EXPECT_THAT(GetFatigueMessage(), Field(&FatigueMessage::eye_state, param.eye_state));
}

}  // namespace
}  // namespace perception