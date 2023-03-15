///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_COMMON_LOGGING_H
#define PERCEPTION_COMMON_LOGGING_H

#include <cstdint>
#include <iostream>
#include <sstream>

namespace perception
{
class LoggingWrapper
{
  public:
    /// @brief Log Severity Levels
    enum class LogSeverity : std::int32_t
    {
        INFO = 0,
        WARNING = 1,
        ERROR = 2,
        FATAL = 3,
        DEBUG = 4
    };

    /// @brief Constructor
    /// @param [in] severity - Logging Severity
    explicit LoggingWrapper(const LogSeverity& severity);

    /// @brief Constructor
    /// @param [in] severity - Logging Severity
    /// @param [in] should_log - Enable/Disable Logging
    explicit LoggingWrapper(const LogSeverity& severity, const bool should_log);

    /// @brief Destructor
    ~LoggingWrapper();

    /// @brief Provides Stream containing logged contents
    std::stringstream& Stream();

  private:
    /// @brief Logged String Stream
    std::stringstream stream_;

    /// @brief Severity Level for Logging
    LogSeverity severity_;

    /// @brief Enable/Disable Logging
    bool should_log_;
};
}  // namespace perception

/// @brief Log Stream with provided severity level
/// @param [in] severity - Severity Level (INFO, WARN, ERROR, FATAL)
#define LOG(severity) perception::LoggingWrapper(perception::LoggingWrapper::LogSeverity::severity).Stream()

/// @brief Checks for Assertion. If condition is false, Log FATAL Error and exit program.
/// @param [in] condition - condition to be evaluated
#define CHECK(condition) \
    perception::LoggingWrapper(perception::LoggingWrapper::LogSeverity::FATAL, (condition) ? false : true).Stream()

/// @brief Checks for Assertion for Comparision. If a and b are not same, Log FATAL Error and exit program.
/// @param [in] a - attribute a
/// @param [in] b - attribute b
#define CHECK_EQ(a, b) CHECK(a == b)

#endif  /// PERCEPTION_COMMON_LOGGING_H_
