///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/calibration.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace sensor
{
namespace camera
{
class CalibrationTest : public ::testing::Test
{
  public:
    CalibrationTest() : unit_{} {}

  protected:
    void SetUp() override { unit_.Init(); }
    void RunOnce() { unit_.Execute(); }
    void TearDown() override { unit_.Shutdown(); }

    Calibration unit_;
};

TEST_F(CalibrationTest, WhenInitialized_ExpectedEmptyCalibrationMatrix)
{
    ASSERT_TRUE(unit_.GetCameraMatrix().empty());
    ASSERT_TRUE(unit_.GetDistanceCoeffs().empty());
    ASSERT_TRUE(unit_.GetRotationMatrix().empty());
    ASSERT_TRUE(unit_.GetTranslationMatrix().empty());
}
TEST_F(CalibrationTest, GivenTypicalCalibrationInputs_ExpectedCalibrationMatrix)
{
    RunOnce();

    ASSERT_FALSE(unit_.GetCameraMatrix().empty());
    ASSERT_FALSE(unit_.GetDistanceCoeffs().empty());
    ASSERT_FALSE(unit_.GetRotationMatrix().empty());
    ASSERT_FALSE(unit_.GetTranslationMatrix().empty());
}
}  // namespace camera
}  // namespace sensor
}  // namespace perception
