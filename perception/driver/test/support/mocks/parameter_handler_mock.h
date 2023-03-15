///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_PARAMETER_HANDLER_MOCK_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_PARAMETER_HANDLER_MOCK_H

#include "perception/driver/i_parameter_handler.h"

#include <gmock/gmock.h>

namespace perception
{
namespace driver
{
namespace test
{
namespace support
{

class ParameterHandlerMock : public IParameterHandler
{
  public:
    ParameterHandlerMock() = default;

    MOCK_CONST_METHOD0(GetMaxEyeLidOpening, units::length::millimeter_t());
    MOCK_CONST_METHOD0(GetMinEyeLidOpening, units::length::millimeter_t());
    MOCK_CONST_METHOD0(GetMinEyeBlinkRate, units::frequency::hertz_t());
    MOCK_CONST_METHOD0(GetMaxEyeBlinkRate, units::frequency::hertz_t());
    MOCK_CONST_METHOD0(GetMinVelocity, units::velocity::meters_per_second_t());
    MOCK_CONST_METHOD0(GetMaxVelocity, units::velocity::meters_per_second_t());
};

}  // namespace support
}  // namespace test
}  // namespace driver
}  // namespace perception
#endif  // PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_PARAMETER_HANDLER_MOCK_H
