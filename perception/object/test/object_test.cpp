///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/object.h"

#include "perception/sensor/camera/calibration.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#include <string>

namespace perception
{
namespace
{
class ObjectTest : public ::testing::Test
{
  public:
    ObjectTest() : test_image_path_{"data/messi5.jpg"}, unit_{}, camera_message_{}
    {
        camera_message_.image = cv::imread(test_image_path_, cv::IMREAD_UNCHANGED);
        cv::undistort(camera_message_.image,
                      camera_message_.undistorted_image,
                      camera_message_.calibration_params.intrinsic,
                      camera_message_.calibration_params.extrinsic);
    }

  protected:
    void SetUp() override
    {
        unit_.Init();
        unit_.SetCameraMessage(camera_message_);
    }
    void RunOnce() { unit_.Step(); }
    void TearDown() override { unit_.Shutdown(); }

    virtual ObjectListMessage GetResults() const { return unit_.GetObjectListMessage(); }

  private:
    const std::string test_image_path_;
    Object unit_;
    CameraMessage camera_message_;
};

TEST_F(ObjectTest, GivenTypicalCameraMessage_ExpectObjects)
{
    // When
    RunOnce();

    // Then
}
}  // namespace
}  // namespace perception
