///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/sensor/camera/camera_node.h"

#include "perception/common/logging/logging.h"
#include "perception/communication/topics.h"

#include <opencv4/opencv2/calib3d.hpp>

namespace perception
{
CameraNode::CameraNode(middleware::IPubSubFactory& factory)
    : Node{"camera_node", factory},
      source_{"data/Megamind.avi"},
      capture_device_{source_},
      camera_message_{},
      calibration_{"data/camera_calibration", 9, 6}
{
}

void CameraNode::Init()
{
    Calibrate();
    AddPublisher<CameraTopic>([this]() { return camera_message_; });
}

void CameraNode::Calibrate()
{
    calibration_.Init();
    calibration_.Execute();
}

void CameraNode::ExecuteStep()
{
    Image image{};
    capture_device_ >> image;

    Image undistorted_image{};
    cv::undistort(image, undistorted_image, calibration_.GetCameraMatrix(), calibration_.GetDistanceCoeffs());

    camera_message_.calibration_params.intrinsic = calibration_.GetCameraMatrix();
    camera_message_.calibration_params.extrinsic = calibration_.GetDistanceCoeffs();
    camera_message_.image = image;
    camera_message_.undistorted_image = undistorted_image;
}

void CameraNode::Shutdown()
{
    calibration_.Shutdown();
    capture_device_.release();
}

void CameraNode::SetSource(const std::string source)
{
    capture_device_.open(source);
    ASSERT_CHECK(capture_device_.isOpened());

    LOG(INFO) << "Reading " << source << " source.";
}

}  // namespace perception
