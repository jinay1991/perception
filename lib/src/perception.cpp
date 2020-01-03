///
/// @file
///
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "perception/logging/logging.h"
#include "perception/perception.h"

namespace perception
{
Perception::Perception() {}

void Perception::Run(const std::string& input_path)
{
    cv::Mat image = cv::imread(input_path, cv::IMREAD_COLOR);
    ASSERT_CHECK(!image.empty()) << "Failed to open " << input_path << "!!!";
    LOG(INFO) << "Successfully opened " << input_path << "!!!";
}
}  // namespace perception