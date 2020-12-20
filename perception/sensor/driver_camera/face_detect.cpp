///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/sensor/driver_camera/face_detect.h"

namespace perception
{
FaceDetect::FaceDetect() : faces_{} {}

void FaceDetect::Detect(const Image& image)
{
    Image gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);

    std::vector<cv::Rect> faces{};
    face_cascade_.detectMultiScale(gray, faces_);
}

const Faces& FaceDetect::GetFaces() const
{
    return face_list_;
}

}  // namespace perception
