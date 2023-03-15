///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#include "perception/common/logging.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace
{

TEST(LoggingTest, BasicLoggingMacro_INFO)
{
    const std::string test_log{"Sanity Test for LogSeverityLevel = INFO!!"};
    ::testing::internal::CaptureStdout();

    LOG(INFO) << test_log;

    const std::string result = ::testing::internal::GetCapturedStdout();
    EXPECT_THAT(result, ::testing::HasSubstr(test_log));
}

TEST(LoggingTest, BasicLoggingMacro_WARN)
{
    const std::string test_log{"Sanity Test for LogSeverityLevel = WARNING!!"};
    ::testing::internal::CaptureStdout();

    LOG(WARNING) << test_log;

    const std::string result = ::testing::internal::GetCapturedStdout();
    EXPECT_THAT(result, ::testing::HasSubstr(test_log));
}

TEST(LoggingTest, BasicLoggingMacro_ERROR)
{
    const std::string test_log{"Sanity Test for LogSeverityLevel = ERROR!!"};
    ::testing::internal::CaptureStderr();

    LOG(ERROR) << test_log;

    const std::string result = ::testing::internal::GetCapturedStderr();
    EXPECT_THAT(result, ::testing::HasSubstr(test_log));
}

}  // namespace
}  // namespace perception
