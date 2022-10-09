///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/activity.h"
#include "perception/driver/test/support/mocks/data_source_mock.h"
#include "perception/driver/test/support/mocks/parameter_handler_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace driver
{
namespace
{
class ActivityFixture : public ::testing::Test
{
  public:
    ActivityFixture()
        : mocked_data_source_{}, mocked_parameter_handler_{}, activity_{mocked_parameter_handler_, mocked_data_source_}
    {
    }

  protected:
    void RunOnce() { activity_.Step(); }

    const ActivityMessage& GetActivityMessage() const { return activity_.GetActivityMessage(); }

  private:
    ::testing::StrictMock<test::support::DataSourceMock> mocked_data_source_;
    ::testing::NiceMock<test::support::ParameterHandlerMock> mocked_parameter_handler_;
    Activity activity_;
};

template <typename T>
class ActivityFixtureT : public ActivityFixture, public ::testing::WithParamInterface<T>
{
};

TEST_F(ActivityFixture, Step_GivenTypicalDriverCameraMessage_ExpectActivityState)
{
    // When
    RunOnce();

    // Then
    const auto activity_message = GetActivityMessage();
    EXPECT_EQ(activity_message.state, ActivityState::kHandsOnWheel);
}
}  // namespace
}  // namespace driver
}  // namespace perception
