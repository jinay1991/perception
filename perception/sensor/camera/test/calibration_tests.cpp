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
    void SetUp() override {}
    void TearDown() override {}

    Calibration unit_;
};

TEST_F(CalibrationTest, GivenTypicalInput_ExpectedCalibrationMatrix) {}
}  // namespace camera
}  // namespace sensor
}  // namespace perception
