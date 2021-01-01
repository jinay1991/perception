///
/// @file
/// @copyright Copyright (c) 2020-2021. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_DATA_SOURCE_MOCK_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_DATA_SOURCE_MOCK_H

#include "perception/driver/i_data_source.h"

#include <gmock/gmock.h>

namespace perception
{
namespace mock
{
class DataSourceMock : public IDataSource
{
  public:
    DataSourceMock() = default;

    MOCK_CONST_METHOD0(IsFaceVisible, bool());
    MOCK_CONST_METHOD0(IsEyeVisible, bool());
    MOCK_CONST_METHOD0(GetEyeLidOpening, units::length::millimeter_t());
    MOCK_CONST_METHOD0(GetEyeBlinkRate, units::frequency::hertz_t());
    MOCK_CONST_METHOD0(GetEyeBlinkDuration, std::chrono::milliseconds());
    MOCK_CONST_METHOD0(GetTimePoint, std::chrono::system_clock::time_point());
    MOCK_CONST_METHOD0(GetHeadTracking, const HeadTracking&());
    MOCK_CONST_METHOD0(GetGazeTracking, const GazeTracking&());
};
}  // namespace mock
}  // namespace perception
#endif  // PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_DATA_SOURCE_MOCK_H
