///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/common/logging/logging.h"
#include "perception/sensor/camera/camera.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <string>

namespace perception
{
namespace
{
class CameraTest : public ::testing::Test
{
  public:
    CameraTest()
        : test_image_path_{"data/grace_hopper.jpg"},
          test_video_path_{"data/Megamind.avi"},
          test_invalid_source_{"invalid/path/to/source"},
          unit_{},
          test_capture_{test_video_path_},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)}
    {
    }

    Image GetTestImage() const { return test_image_; };
    Image GetTestVideoImage() const { return test_video_frame_; }

  protected:
    void SetUp() override { unit_.Init(); }

    void RunOnce()
    {
        unit_.Execute();
        test_capture_ >> test_video_frame_;
    }

    void TearDown() override { unit_.Shutdown(); }

    const std::string test_image_path_;
    const std::string test_video_path_;
    const std::string test_invalid_source_;
    Camera unit_;

  private:
    cv::VideoCapture test_capture_;
    cv::Mat test_image_;
    cv::Mat test_video_frame_;
};

TEST_F(CameraTest, GivenTypicalSourceImage_ExpectValidImage)
{
    unit_.SetSource(test_image_path_);

    RunOnce();

    const auto expected = GetTestImage();
    const auto actual = unit_.GetImage();
    ASSERT_FALSE(actual.empty());
    ASSERT_EQ(expected.size(), actual.size());
}

TEST_F(CameraTest, GivenTypicalSourceVideo_ExpectValidVideoFrame)
{
    unit_.SetSource(test_video_path_);

    RunOnce();

    const auto expected = GetTestVideoImage();
    const auto actual = unit_.GetImage();
    ASSERT_FALSE(actual.empty());
    ASSERT_EQ(expected.size(), actual.size());
}

TEST_F(CameraTest, GivenInvalidSource_ExpectException)
{
    EXPECT_EXIT(unit_.SetSource(test_invalid_source_), ::testing::KilledBySignal(SIGABRT), "");
}
}  // namespace
}  // namespace perception
