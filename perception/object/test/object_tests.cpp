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

#include <chrono>
#include <string>

namespace perception
{
namespace
{
using namespace units::literals;
using namespace std::chrono_literals;

using ::testing::DoubleEq;
using ::testing::DoubleNear;
using ::testing::Eq;

class ObjectTest : public ::testing::Test
{
  public:
    ObjectTest() : test_image_path_{"data/messi5.jpg"}, unit_{}, camera_message_{}
    {
        camera_message_.time_point = std::chrono::system_clock::time_point{10ms};
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
        unit_.SetEgoVelocity(100.0_kph);
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
    const auto actual = GetResults();
    EXPECT_THAT(actual.number_of_valid_objects, Eq(1));
    EXPECT_THAT(actual.time_point.time_since_epoch(), Eq(10ms));
    EXPECT_THAT(actual.objects.at(0).id, Eq(ObjectId::kBicycle));
    EXPECT_THAT(actual.objects.at(0).bounding_box.x, DoubleNear(18.9724, 0.0001));
    EXPECT_THAT(actual.objects.at(0).bounding_box.y, DoubleNear(19.4001, 0.0001));
    EXPECT_THAT(actual.objects.at(0).bounding_box.width, DoubleNear(435.872, 0.001));
    EXPECT_THAT(actual.objects.at(0).bounding_box.height, DoubleNear(309.97, 0.01));
    EXPECT_THAT(actual.objects.at(0).velocity.value(), DoubleEq(0.0));
    EXPECT_THAT(actual.objects.at(0).relative_velocity.value(), DoubleEq(0.0));
    EXPECT_THAT(actual.objects.at(0).position.x.value(), DoubleNear(-1.23979, 0.00001));
    EXPECT_THAT(actual.objects.at(0).position.y.value(), DoubleNear(-0.0486435, 0.000001));
    EXPECT_THAT(actual.objects.at(0).position.z.value(), DoubleNear(0.430763, 0.000001));
    EXPECT_THAT(actual.objects.at(0).pose.yaw.value(), DoubleNear(-0.378735, 0.00001));
    EXPECT_THAT(actual.objects.at(0).pose.pitch.value(), DoubleNear(-1.15457, 0.00001));
    EXPECT_THAT(actual.objects.at(0).pose.roll.value(), DoubleNear(-0.604467, 0.000001));
    EXPECT_THAT(actual.objects.at(0).distance.value(), DoubleNear(1.31339, 0.00001));
}
}  // namespace
}  // namespace perception
