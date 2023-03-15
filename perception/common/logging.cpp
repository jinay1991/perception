///
/// @file
/// @copyright Copyright (C) 2023. MIT License.
///
#include "perception/common/logging.h"

namespace perception
{
LoggingWrapper::LoggingWrapper(const LogSeverity& severity) : LoggingWrapper{severity, true} {}

LoggingWrapper::LoggingWrapper(const LogSeverity& severity, const bool should_log)
    : severity_{severity}, should_log_{should_log}
{
}

std::stringstream& LoggingWrapper::Stream()
{
    return stream_;
}

LoggingWrapper::~LoggingWrapper()
{
    if (should_log_)
    {
        switch (severity_)
        {
            case LogSeverity::DEBUG:
            case LogSeverity::INFO:
            case LogSeverity::WARNING:
                std::cout << stream_.str() << std::endl;
                break;
            case LogSeverity::ERROR:
                std::cerr << stream_.str() << std::endl;
                break;
            case LogSeverity::FATAL:
                std::cerr << stream_.str() << std::endl;
                std::flush(std::cerr);
                std::abort();
                break;
            default:
                break;
        }
    }
}
}  // namespace perception
