///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/object.h"

#include "perception/common/logging/logging.h"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>

namespace perception
{
Object::Object()
    : inference_engine_params_{"external/ssd_mobilenet_v2_coco/saved_model",
                               "image_tensor",
                               {"detection_classes", "detection_scores", "detection_boxes", "num_detections"}},
      inference_engine_{},
      camera_message_{},
      object_list_message_{}
{
}

void Object::Init()
{
    inference_engine_.SelectInferenceEngine(InferenceEngineType::kTensorFlow, inference_engine_params_);
    inference_engine_.Init();
}

void Object::Step()
{
    inference_engine_.Execute(camera_message_.undistorted_image);

    UpdateOutputs();
}

void Object::Shutdown()
{
    inference_engine_.Shutdown();
}

void Object::SetCameraMessage(const CameraMessage& camera_message)
{
    camera_message_ = camera_message;
}

ObjectListMessage Object::GetObjectListMessage() const
{
    return object_list_message_;
}

void Object::UpdateOutputs()
{
    const auto results = inference_engine_.GetResults();
    const cv::Mat detection_classes = results.at(0);
    const cv::Mat detection_scores = results.at(1);
    const cv::Mat detection_boxes = results.at(2);
    const cv::Mat num_detections = results.at(3);

    ASSERT_CHECK(!num_detections.empty()) << "No detections received!!";
    for (auto idx = 0; idx < static_cast<std::int32_t>(num_detections.at<float>(0, 0)); ++idx)
    {
        const auto score = detection_scores.at<float>(idx, 0);
        const auto label = detection_classes.at<float>(idx, 0);
        const auto ymin = detection_boxes.at<float>(idx, 0);
        const auto xmin = detection_boxes.at<float>(idx, 1);
        const auto ymax = detection_boxes.at<float>(idx, 2);
        const auto xmax = detection_boxes.at<float>(idx, 3);
        const auto bounding_box = BoundingBox{xmin * static_cast<float>(camera_message_.image.cols),
                                              ymin * static_cast<float>(camera_message_.image.rows),
                                              (xmax - xmin) * static_cast<float>(camera_message_.image.cols),
                                              (ymax - ymin) * static_cast<float>(camera_message_.image.rows)};

        object_list_message_.at(idx).bounding_box = bounding_box;
        object_list_message_.at(idx).id = ObjectId::kPedestrian;
    }
}
}  // namespace perception
