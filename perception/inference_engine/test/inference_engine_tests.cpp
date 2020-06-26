///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#include "perception/inference_engine/i_inference_engine.h"
#include "perception/inference_engine/inference_engine_strategy.h"
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
class InferenceEngineTest : public ::testing::Test
{
  public:
    InferenceEngineTest()
        : test_image_path_{"data/grace_hopper.jpg"}, test_image_{cv::imread(test_image_path_, cv::IMREAD_UNCHANGED)}
    {
    }

  protected:
    void SetUp() override
    {
        this->unit_ = std::make_unique<T>();
        this->unit_->Init();
    }

    void TearDown() override { unit_->Shutdown(); }

    const std::string test_image_path_;
    Image test_image_;

    InferenceEnginePtr unit_;
};
TYPED_TEST_SUITE_P(InferenceEngineTest);

TYPED_TEST_P(InferenceEngineTest, Sanity)
{
    this->unit_->Execute(this->test_image_);

    // auto actual = this->unit_->GetResults();
    // EXPECT_EQ(5U, actual.size());
}

REGISTER_TYPED_TEST_SUITE_P(InferenceEngineTest, Sanity);

typedef ::testing::Types</*TFInferenceEngine , TFLiteInferenceEngine ,*/ TorchInferenceEngine> InferenceEngineTestTypes;
INSTANTIATE_TYPED_TEST_SUITE_P(TypeTests, InferenceEngineTest, InferenceEngineTestTypes);

class InferenceEngineStrategyTest : public ::testing::TestWithParam<InferenceEngineType>
{
  public:
    InferenceEngineStrategyTest() : unit_{} {}

  protected:
    InferenceEngineStrategy unit_;
};
TEST_P(InferenceEngineStrategyTest, GivenInferenceEngine_ExpectSelectedEngine)
{
    unit_.SelectInferenceEngine(GetParam());

    EXPECT_EQ(GetParam(), unit_.GetInferenceEngineType());
}
INSTANTIATE_TEST_CASE_P(TypeTests,
                        InferenceEngineStrategyTest,
                        ::testing::Values(InferenceEngineType::kTensorFlow,
                                          InferenceEngineType::kTensorFlowLite,
                                          InferenceEngineType::kTorch));
}  // namespace
}  // namespace perception
