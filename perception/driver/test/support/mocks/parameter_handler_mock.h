///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_PARAMETER_HANDLER_MOCK_H
#define PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_PARAMETER_HANDLER_MOCK_H

#include "perception/driver/i_parameter_handler.h"

#include <gmock/gmock.h>

namespace perception
{
namespace mock
{
class ParameterHandlerMock : public IParameterHandler
{
  public:
    ParameterHandlerMock() = default;

    MOCK_CONST_METHOD0(GetMaxEyeLidOpening, units::length::millimeter_t());
    MOCK_CONST_METHOD0(GetMinEyeLidOpening, units::length::millimeter_t());
    MOCK_CONST_METHOD0(GetEyeBlinkRate, units::frequency::hertz_t());
    MOCK_CONST_METHOD0(GetEyeBlinkDuration, std::chrono::milliseconds());
};
}  // namespace mock
}  // namespace perception
#endif  // PERCEPTION_DRIVER_TEST_SUPPORT_MOCKS_PARAMETER_HANDLER_MOCK_H
