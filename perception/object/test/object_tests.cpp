///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/object/object.h"

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
namespace object
{
namespace
{
using namespace units::literals;
using namespace std::chrono_literals;

using ::testing::AllOf;
using ::testing::DoubleEq;
using ::testing::DoubleNear;
using ::testing::Eq;
using ::testing::Field;
using ::testing::Property;

constexpr units::velocity::kilometers_per_hour_t kDefaultEgoVelocity{100.0};

class ObjectTest : public ::testing::Test
{
  public:
    ObjectTest() : test_image_path_{"data/messi5.jpg"}, unit_{}, camera_message_{}, ego_velocity_{kDefaultEgoVelocity}
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
        unit_.SetEgoVelocity(ego_velocity_);
    }
    void RunOnce() { unit_.Step(); }
    void TearDown() override { unit_.Shutdown(); }

    const ObjectListMessage& GetResults() const { return unit_.GetObjectListMessage(); }

  private:
    const std::string test_image_path_;
    Object unit_;
    CameraMessage camera_message_;
    units::velocity::meters_per_second_t ego_velocity_;
};

TEST_F(ObjectTest, GivenTypicalCameraMessage_ExpectObjectListMessageWithValidObjects)
{
    // When
    RunOnce();

    // Then
    const auto actual = GetResults();
    EXPECT_THAT(
        actual,
        AllOf(
            Field(&ObjectListMessage::number_of_valid_objects, 1),
            Field(&ObjectListMessage::time_point,
                  Property(&std::chrono::system_clock::time_point::time_since_epoch, 10ms)),
            Field(
                &ObjectListMessage::objects,
                Contains(AllOf(
                    Field(&ObjectMessage::id, ObjectId::kBicycle),
                    Field(&ObjectMessage::distance,
                          Property(&units::length::meter_t::value, DoubleNear(1.31339, 0.001))),
                    Field(&ObjectMessage::bounding_box,
                          AllOf(Field(&BoundingBox::x, DoubleNear(18.9724, 0.001)),
                                Field(&BoundingBox::y, DoubleNear(19.4001, 0.001)),
                                Field(&BoundingBox::width, DoubleNear(435.872, 0.01)),
                                Field(&BoundingBox::height, DoubleNear(309.97, 0.01)))),
                    Field(&ObjectMessage::position,
                          AllOf(Field(&Position::x,
                                      Property(&units::length::meter_t::value, DoubleNear(-1.23979, 0.0001))),
                                Field(&Position::y,
                                      Property(&units::length::meter_t::value, DoubleNear(-0.0486435, 0.00001))),
                                Field(&Position::z,
                                      Property(&units::length::meter_t::value, DoubleNear(0.430763, 0.00001))))),
                    Field(
                        &ObjectMessage::pose,
                        AllOf(
                            Field(&Pose::yaw, Property(&units::angle::radian_t::value, DoubleNear(-0.378735, 0.0001))),
                            Field(&Pose::pitch, Property(&units::angle::radian_t::value, DoubleNear(-1.15457, 0.0001))),
                            Field(&Pose::roll,
                                  Property(&units::angle::radian_t::value, DoubleNear(-0.604467, 0.00001))))))))));
}
}  // namespace
}  // namespace object
}  // namespace perception
