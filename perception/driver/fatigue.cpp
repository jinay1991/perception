///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/fatigue.h"

namespace perception
{

Fatigue::Fatigue(const IParameters& parameters, const IDataSource& data_source)
    : parameters_{parameters}, data_source_{data_source}, fatigue_message_{}
{
}

void Fatigue::Init() {}

void Fatigue::ExecuteStep() {}

void Fatigue::Shutdown() {}

const FatigueMessage& Fatigue::GetFatigueMessage()
{
    return fatigue_message_;
}

}  // namespace perception
