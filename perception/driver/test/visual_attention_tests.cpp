///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/parameter_handler.h"
#include "perception/driver/test/support/mocks/data_source_mock.h"
#include "perception/driver/test/support/mocks/parameter_handler_mock.h"
#include "perception/driver/visual_attention.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <units.h>

namespace perception
{
namespace
{
using ::testing::Field;
using ::testing::Return;

class VisualAttentionFixture : public ::testing::Test
{
  public:
    VisualAttentionFixture()
        : mocked_data_source_{},
          mocked_parameter_handler_{},
          visual_attention_{mocked_parameter_handler_, mocked_data_source_}
    {
    }

  protected:
    void SetUp() override
    {
        EXPECT_CALL(mocked_parameter_handler_, GetMaxEyeLidOpening()).WillRepeatedly(Return(kMaxEyeLidOpening));
        EXPECT_CALL(mocked_parameter_handler_, GetMinEyeLidOpening()).WillRepeatedly(Return(kMinEyeLidOpening));
        EXPECT_CALL(mocked_parameter_handler_, GetEyeBlinkRate()).WillRepeatedly(Return(kMaxEyeBlinkRate));

        visual_attention_.Init();
    }
    void TearDown() override { visual_attention_.Shutdown(); }
    void RunOnce() { visual_attention_.ExecuteStep(); }

    const VisualAttentionMessage& GetVisualAttentionMessage() const
    {
        return visual_attention_.GetVisualAttentionMessage();
    }

    ::testing::StrictMock<mock::DataSourceMock> mocked_data_source_;

  private:
    ::testing::StrictMock<mock::ParameterHandlerMock> mocked_parameter_handler_;
    VisualAttention visual_attention_;
};

template <typename T>
class VisualAttentionFixtureT : public VisualAttentionFixture, public ::testing::WithParamInterface<T>
{
};

TEST_F(VisualAttentionFixture, VisualAttention_GivenTypicalHeadTracking_ExpectUpdatedVisualAttention)
{
    // Given
    // When
    // Then
}

}  // namespace
}  // namespace perception
