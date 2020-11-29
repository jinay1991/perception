///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/common/logging.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{

TEST(LoggingTest, LoggingMacro_Sanity)
{
    const std::string test_log{"Sanity Test!!"};
    ::testing::internal::CaptureStderr();

    LOG(INFO) << test_log;

    const std::string result = ::testing::internal::GetCapturedStderr();
    EXPECT_THAT(result, ::testing::HasSubstr(test_log));
}
}  // namespace
}  // namespace perception
