///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "middleware/communication/intra_process_pub_sub_factory.h"
#include "middleware/lifecycle/test/single_topic_subscriber.h"
#include "perception/communication/topics.h"
#include "perception/sensor/camera/calibration.h"
#include "perception/sensor/camera/node/camera_node.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <string>

namespace perception
{
namespace
{

using ::testing::AllOf;
using ::testing::Eq;
using ::testing::Field;
using ::testing::Property;

class CameraNodeTest : public ::testing::Test
{
  public:
    CameraNodeTest()
        : factory_{},
          unit_{factory_},
          test_subscriber_{"test_subscriber", factory_},
          calibration_params_{},
          test_image_path_{"data/camera_calibration/calibration1.jpg"},
          test_image_undistorted_path_{"data/undistorted_calibration1.jpg"},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)},
          test_image_undistorted_{cv::imread(test_image_undistorted_path_, cv::IMREAD_UNCHANGED)}
    {
    }

  protected:
    void SetUp() override
    {
        test_subscriber_.Init();
        unit_.Init();
    }

    void RunOnce()
    {
        unit_.SetSource(test_image_path_);

        unit_.Step();
        test_subscriber_.Step();
    }

    void TearDown() override
    {
        unit_.Shutdown();
        test_subscriber_.Shutdown();
    }

    const Image& GetTestImage() const { return test_image_; }
    const Image& GetTestImageUndistorted() const { return test_image_undistorted_; }
    const cv::Mat& GetTestIntrinsicParam() const { return calibration_params_.intrinsic; }
    const cv::Mat& GetTestExtrinsicParam() const { return calibration_params_.extrinsic; }

    CameraMessage GetResults() const { return test_subscriber_.GetSample(); }

  private:
    middleware::IntraProcessPubSubFactory factory_;
    CameraNode unit_;
    middleware::SingleTopicSubscriber<CameraTopic> test_subscriber_;

    const CalibrationParams calibration_params_;
    const std::string test_image_path_;
    const std::string test_image_undistorted_path_;
    cv::Mat test_image_;
    cv::Mat test_image_undistorted_;
};

TEST_F(CameraNodeTest, GivenTypicalSourceImage_ExpectValidImage)
{
    // When
    RunOnce();

    // Then
    const auto actual = GetResults();
    EXPECT_THAT(actual,
                AllOf(Field(&CameraMessage::image,
                            AllOf(Property(&Image::empty, false), Field(&Image::size, GetTestImage().size))),
                      Field(&CameraMessage::undistorted_image,
                            AllOf(Property(&Image::empty, false), Field(&Image::size, GetTestImageUndistorted().size))),
                      Field(&CameraMessage::calibration_params,
                            AllOf(Field(&CalibrationParams::intrinsic,
                                        AllOf(Property(&cv::Mat::empty, false),
                                              Field(&cv::Mat::size, GetTestIntrinsicParam().size))),
                                  Field(&CalibrationParams::extrinsic,
                                        AllOf(Property(&cv::Mat::empty, false),
                                              Field(&cv::Mat::size, GetTestExtrinsicParam().size)))))));
}

}  // namespace
}  // namespace perception
