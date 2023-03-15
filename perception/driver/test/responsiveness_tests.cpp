///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/driver/responsiveness.h"
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
class ResponsivenessFixture : public ::testing::Test
{
  public:
    ResponsivenessFixture()
        : mocked_data_source_{},
          mocked_parameter_handler_{},
          responsiveness_{mocked_parameter_handler_, mocked_data_source_}
    {
    }

  protected:
    void RunOnce() { responsiveness_.Step(); }

    const ResponsivenessMessage& GetResponsivenessMessage() const { return responsiveness_.GetResponsivenessMessage(); }

  private:
    ::testing::StrictMock<test::support::DataSourceMock> mocked_data_source_;
    ::testing::NiceMock<test::support::ParameterHandlerMock> mocked_parameter_handler_;
    Responsiveness responsiveness_;
};

template <typename T>
class ResponsivenessFixtureT : public ResponsivenessFixture, public ::testing::WithParamInterface<T>
{
};

TEST_F(ResponsivenessFixture, Step_GivenTypicalDriverCameraMessage_ExpectResponsivenessState)
{
    // When
    RunOnce();

    // Then
    const auto responsiveness_message = GetResponsivenessMessage();
    EXPECT_EQ(responsiveness_message.state, ResponsivenessState::kResponsive);
}
}  // namespace
}  // namespace driver
}  // namespace perception
