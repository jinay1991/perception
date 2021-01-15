///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/support/single_topic_publisher.h"
#include "middleware/lifecycle/test/support/single_topic_subscriber.h"
#include "perception/communication/topics.h"
#include "perception/object/node/object_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <units.h>

#include <string>

namespace perception
{
namespace
{
using namespace units::literals;
class ObjectNodeTest : public ::testing::Test
{
  public:
    ObjectNodeTest()
        : factory_{},
          test_image_path_{"data/messi5.jpg"},
          camera_message_{},
          vehicle_dynamics_message_{},
          unit_{factory_},
          test_camera_publisher_{"test_camera_publisher", factory_},
          test_vehicle_dynamics_publisher_{"test_vehicle_dynamics_publisher", factory_},
          test_subscriber_{"test_subscriber", factory_}
    {
        camera_message_.image = cv::imread(test_image_path_, cv::IMREAD_UNCHANGED);
        cv::undistort(camera_message_.image,
                      camera_message_.undistorted_image,
                      camera_message_.calibration_params.intrinsic,
                      camera_message_.calibration_params.extrinsic);

        vehicle_dynamics_message_.velocity = 10.0_mps;
    }

  protected:
    void SetUp() override
    {
        test_camera_publisher_.Init();
        test_vehicle_dynamics_publisher_.Init();
        unit_.Init();
        test_subscriber_.Init();
    }

    void RunOnce()
    {
        test_camera_publisher_.PublishInput(camera_message_);
        test_camera_publisher_.Step();
        test_vehicle_dynamics_publisher_.PublishInput(vehicle_dynamics_message_);
        test_vehicle_dynamics_publisher_.Step();
        unit_.Step();
        test_subscriber_.Step();
    }

    void TearDown() override
    {
        test_camera_publisher_.Shutdown();
        test_vehicle_dynamics_publisher_.Shutdown();
        unit_.Shutdown();
        test_subscriber_.Shutdown();
    }

    ObjectListMessage GetResults() const { return test_subscriber_.GetSample(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    const std::string test_image_path_;
    CameraMessage camera_message_;
    VehicleDynamicsMessage vehicle_dynamics_message_;
    ObjectNode unit_;
    middleware::SingleTopicPublisher<CameraTopic> test_camera_publisher_;
    middleware::SingleTopicPublisher<VehicleDynamicsTopic> test_vehicle_dynamics_publisher_;
    middleware::SingleTopicSubscriber<ObjectListTopic> test_subscriber_;
};

TEST_F(ObjectNodeTest, GivenTypicalInputs_ExpectDetectedObjects)
{
    // When
    RunOnce();

    // Then
    const auto& actual = GetResults();
    EXPECT_EQ(1, actual.number_of_valid_objects);
    EXPECT_EQ(ObjectId::kBicycle, actual.objects.at(0).id);
}

}  // namespace
}  // namespace perception
