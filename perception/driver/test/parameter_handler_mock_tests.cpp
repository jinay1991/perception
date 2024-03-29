///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/test/support/mocks/parameter_handler_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace test
{
namespace support
{
namespace
{
using ::testing::Return;
using namespace units::literals;

class ParameterHandlerMockFixture : public ::testing::Test
{
  public:
    ParameterHandlerMockFixture() : mocked_parameter_handler_{} {}

  protected:
    ::testing::NiceMock<ParameterHandlerMock> mocked_parameter_handler_;
};

TEST_F(ParameterHandlerMockFixture, GetMaxEyeLidOpening_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto eye_lid_opening = 10.0_mm;
    EXPECT_CALL(mocked_parameter_handler_, GetMaxEyeLidOpening()).WillRepeatedly(Return(eye_lid_opening));

    // When
    const auto result = mocked_parameter_handler_.GetMaxEyeLidOpening();

    // Then
    EXPECT_THAT(result, eye_lid_opening);
}

TEST_F(ParameterHandlerMockFixture, GetMinEyeLidOpening_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto eye_lid_opening = 1.0_mm;
    EXPECT_CALL(mocked_parameter_handler_, GetMinEyeLidOpening()).WillRepeatedly(Return(eye_lid_opening));

    // When
    const auto result = mocked_parameter_handler_.GetMinEyeLidOpening();

    // Then
    EXPECT_THAT(result, eye_lid_opening);
}

TEST_F(ParameterHandlerMockFixture, GetMaxEyeBlinkRate_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto eye_blink_rate = 10.0_Hz;
    EXPECT_CALL(mocked_parameter_handler_, GetMaxEyeBlinkRate()).WillRepeatedly(Return(eye_blink_rate));

    // When
    const auto result = mocked_parameter_handler_.GetMaxEyeBlinkRate();

    // Then
    EXPECT_THAT(result, eye_blink_rate);
}

TEST_F(ParameterHandlerMockFixture, GetMinEyeBlinkRate_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto eye_blink_rate = 1.0_Hz;
    EXPECT_CALL(mocked_parameter_handler_, GetMinEyeBlinkRate()).WillRepeatedly(Return(eye_blink_rate));

    // When
    const auto result = mocked_parameter_handler_.GetMinEyeBlinkRate();

    // Then
    EXPECT_THAT(result, eye_blink_rate);
}

TEST_F(ParameterHandlerMockFixture, GetMaxVelocity_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto velocity = 10.0_kph;
    EXPECT_CALL(mocked_parameter_handler_, GetMaxVelocity()).WillRepeatedly(Return(velocity));

    // When
    const auto result = mocked_parameter_handler_.GetMaxVelocity();

    // Then
    EXPECT_THAT(result, velocity);
}

TEST_F(ParameterHandlerMockFixture, GetMinVelocity_GivenTypicalValue_ExpectSame)
{
    // Given
    const auto velocity = 1.0_kph;
    EXPECT_CALL(mocked_parameter_handler_, GetMinVelocity()).WillRepeatedly(Return(velocity));

    // When
    const auto result = mocked_parameter_handler_.GetMinVelocity();

    // Then
    EXPECT_THAT(result, velocity);
}
}  // namespace
}  // namespace support
}  // namespace test
}  // namespace driver
}  // namespace perception
