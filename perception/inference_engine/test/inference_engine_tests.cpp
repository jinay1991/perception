///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/inference_engine/i_inference_engine.h"
#include "perception/inference_engine/inference_engine_strategy.h"
#include "perception/inference_engine/null_inference_engine.h"
#include "perception/inference_engine/opencv_inference_engine.h"
#include "perception/inference_engine/tf_inference_engine.h"
#include "perception/inference_engine/tflite_inference_engine.h"
#include "perception/inference_engine/torch_inference_engine.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace perception
{
namespace
{
template <typename T>
const InferenceEngineParameters GetInferenceEngineParameter()
{
    return InferenceEngineParameters{};
}

template <>
const InferenceEngineParameters GetInferenceEngineParameter<TFInferenceEngine>()
{
    return InferenceEngineParameters{"external/ssd_mobilenet_v2_coco/saved_model",
                                     "image_tensor",
                                     {"detection_classes", "detection_scores", "detection_boxes", "num_detections"},
                                     "no-config"};
}

template <>
const InferenceEngineParameters GetInferenceEngineParameter<TFLiteInferenceEngine>()
{
    return InferenceEngineParameters{"external/ssd_mobilenet_v2_coco/ssd_mobilenet_v2_coco_2018_03_29.tflite",
                                     "image_tensor",
                                     {"detection_classes", "detection_scores", "detection_boxes", "num_detections"},
                                     "no-config"};
}

template <>
const InferenceEngineParameters GetInferenceEngineParameter<OpenCVInferenceEngine>()
{
    return InferenceEngineParameters{"external/ssd_mobilenet_v2_coco/ssd_mobilenet_v2_coco_2018_03_29.pb",
                                     "image_tensor",
                                     {"detection_out"},
                                     "external/ssd_mobilenet_v2_coco/ssd_mobilenet_v2_coco_2018_03_29.pbtxt"};
}

template <>
const InferenceEngineParameters GetInferenceEngineParameter<TorchInferenceEngine>()
{
    return InferenceEngineParameters{
        "external/ssd_mobilenet_v2_coco/mobilenet_v2-b0353104_torchscript.pth", "input", {"outputs"}, "no-config"};
}

template <typename T>
class InferenceEngineFixture_WithInferenceEngineType : public ::testing::Test
{
  public:
    InferenceEngineFixture_WithInferenceEngineType()
        : test_image_path_{"data/messi5.jpg"},
          test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)},
          inference_engine_parameters_{GetInferenceEngineParameter<T>()},
          unit_{std::make_unique<T>(inference_engine_parameters_)}
    {
    }

  protected:
    void SetUp() override { unit_->Init(); }
    void RunOnce() { unit_->Execute(test_image_); }
    void TearDown() override { unit_->Shutdown(); }

    std::vector<cv::Mat> GetInferenceResults() const { return unit_->GetResults(); }
    InferenceEngineParameters GetInferenceParameters() const { return inference_engine_parameters_; }

  private:
    const std::string test_image_path_;
    const Image test_image_;
    const InferenceEngineParameters inference_engine_parameters_;
    InferenceEnginePtr unit_;
};
TYPED_TEST_SUITE_P(InferenceEngineFixture_WithInferenceEngineType);

TYPED_TEST_P(InferenceEngineFixture_WithInferenceEngineType, InferenceEngine_GivenTypicalInputs_ExpectInferenceResults)
{
    // When
    this->RunOnce();

    // Then
    const auto actual = this->GetInferenceResults();
    EXPECT_EQ(this->GetInferenceParameters().output_tensor_names.size(), actual.size());
}

REGISTER_TYPED_TEST_SUITE_P(InferenceEngineFixture_WithInferenceEngineType,
                            InferenceEngine_GivenTypicalInputs_ExpectInferenceResults);

typedef ::testing::
    Types<TFInferenceEngine, TFLiteInferenceEngine, OpenCVInferenceEngine, TorchInferenceEngine, NullInferenceEngine>
        InferenceEngineTestTypes;
INSTANTIATE_TYPED_TEST_SUITE_P(InferenceEngine,
                               InferenceEngineFixture_WithInferenceEngineType,
                               InferenceEngineTestTypes);

class InferenceEngineStrategyTest : public ::testing::TestWithParam<InferenceEngineType>
{
  public:
    InferenceEngineStrategyTest() : inference_engine_params_{}, unit_{} {}

  protected:
    InferenceEngineParameters inference_engine_params_;
    InferenceEngineStrategy unit_;
};
TEST_P(InferenceEngineStrategyTest, GivenInferenceEngine_ExpectSelectedEngine)
{
    unit_.SelectInferenceEngine(GetParam(), inference_engine_params_);

    EXPECT_EQ(GetParam(), unit_.GetInferenceEngineType());
}
INSTANTIATE_TEST_CASE_P(InferenceEngine,
                        InferenceEngineStrategyTest,
                        ::testing::Values(InferenceEngineType::kTensorFlow,
                                          InferenceEngineType::kTensorFlowLite,
                                          InferenceEngineType::kTorch,
                                          InferenceEngineType::kOpenCV));
}  // namespace
}  // namespace perception
