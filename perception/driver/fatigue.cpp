///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/driver/fatigue.h"

namespace perception
{
constexpr units::frequency::hertz_t kMaxEyeBlinkRate{10.0};
constexpr units::length::millimeter_t kMaxEyeLidOpening{10.0};
constexpr units::length::millimeter_t kMinEyeLidOpening{1.0};

Fatigue::Fatigue(const IParameters& parameters, const IDataSource& data_source)
    : parameters_{parameters}, data_source_{data_source}, fatigue_message_{}
{
}

void Fatigue::Init() {}

void Fatigue::ExecuteStep()
{
    fatigue_message_.eye_state = GetEyeState();
}

void Fatigue::Shutdown() {}

const FatigueMessage& Fatigue::GetFatigueMessage() const
{
    return fatigue_message_;
}

EyeState Fatigue::GetEyeState() const
{
    EyeState eye_state{EyeState::kInvalid};
    const FaceTracking& face_tracking = data_source_.GetFaceTracking();
    if (face_tracking.eye_visibility && (face_tracking.eye_blink_rate < kMaxEyeBlinkRate))
    {
        if (face_tracking.eye_lid_opening > kMinEyeLidOpening && face_tracking.eye_lid_opening < kMaxEyeLidOpening)
        {
            eye_state = EyeState::kEyesOpen;
        }
        else
        {
            eye_state = EyeState::kEyesClosed;
        }
    }
    else
    {
        eye_state = EyeState::kEyesUnknown;
    }

    return eye_state;
}

}  // namespace perception
