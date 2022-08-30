///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/driver/distraction.h"
#include "perception/driver/test/support/mocks/data_source_mock.h"
#include "perception/driver/test/support/mocks/parameter_handler_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <units.h>

#include <cmath>

namespace perception
{
namespace driver
{
namespace
{
using ::testing::DoubleNear;
using ::testing::Field;
using ::testing::Return;

class DistractionFixture : public ::testing::Test
{
  public:
    DistractionFixture()
        : mocked_data_source_{},
          mocked_parameter_handler_{},
          distraction_{mocked_parameter_handler_, mocked_data_source_}
    {
    }

  protected:
    void RunOnce() { distraction_.Step(); }

    const DistractionMessage& GetDistractionMessage() const { return distraction_.GetDistractionMessage(); }

  private:
    ::testing::StrictMock<test::support::DataSourceMock> mocked_data_source_;
    ::testing::NiceMock<test::support::ParameterHandlerMock> mocked_parameter_handler_;
    Distraction distraction_;
};

template <typename T>
class DistractionFixtureT : public DistractionFixture, public ::testing::WithParamInterface<T>
{
};

TEST_F(DistractionFixture, Step_GivenTypicalDriverCameraMessage_ExpectDistractionState)
{
    // When
    RunOnce();

    // Then
    const auto distraction_message = GetDistractionMessage();
    EXPECT_EQ(distraction_message.state, DistractionState::kNotDistracted);
}
}  // namespace
}  // namespace driver
}  // namespace perception
