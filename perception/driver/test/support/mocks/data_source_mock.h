///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_DATA_SOURCE_MOCK_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_DATA_SOURCE_MOCK_H

#include "perception/driver/i_data_source.h"

#include <gmock/gmock.h>

namespace perception
{
namespace driver
{
namespace test
{
namespace support
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
}  // namespace support
}  // namespace test
}  // namespace driver
}  // namespace perception
#endif  // PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_DATA_SOURCE_MOCK_H
