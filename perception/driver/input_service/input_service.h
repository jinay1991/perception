///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_INPUT_SERVICE_H
#define PERCEPTION_DRIVER_INPUT_SERVICE_H

#include "perception/datatypes/driver.h"
#include "perception/driver/common/i_parameters.h"
#include "perception/driver/input_service/i_input_service.h"

namespace perception
{
class InputService : public IInputService
{
  public:
    explicit InputService(const IParameters& parameters)
        : parameters_{parameters},
          eye_state_{EyeState::kInvalid},
          head_pose_{HeadPose::kInvalid},
          gaze_pose_{GazePose::kInvalid},
          dcs_data_{}
    {
    }

    EyeState GetEyeState() const override { return eye_state_; }
    HeadPose GetHeadPose() const override { return head_pose_; }
    GazePose GetGazePose() const override { return gaze_pose_; }

    void UpdateInputs()
    {
        UpdateEyeState();
        UpdateGazePose();
        UpdateHeadPose();
    }

    void UpdateHeadPose()
    {
        if ((parameters_.GetYaw() > dcs_data_.head_tracking.yaw) &&
            (parameters_.GetRoll() > dcs_data_.head_tracking.roll) &&
            (parameters_.GetPitch() > dcs_data_.head_tracking.pitch))
        {
            head_pose_ = HeadPose::kAttentive;
        }
    }

    void UpdateGazePose()
    {
        if ((parameters_.GetYaw() > dcs_data_.gaze_tracking.yaw) &&
            (parameters_.GetRoll() > dcs_data_.gaze_tracking.roll) &&
            (parameters_.GetPitch() > dcs_data_.gaze_tracking.pitch))
        {
            gaze_pose_ = GazePose::kFront;
        }
    }

    void UpdateEyeState()
    {
        if (dcs_data_.face_tracking.eye_visibility &&
            (parameters_.GetEyeLidOpening() > dcs_data_.face_tracking.eye_lid_opening) &&
            (parameters_.GetEyeBlinkRate() > dcs_data_.face_tracking.eye_blink_rate))
        {
            eye_state_ = EyeState::kOpenEyes;
        }
    }

    void SetDriverCameraSystemData(const DriverCameraSystem& dcs_data) { dcs_data_ = dcs_data; }

  private:
    const IParameters& parameters_;

    EyeState eye_state_;
    HeadPose head_pose_;
    GazePose gaze_pose_;

    DriverCameraSystem dcs_data_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_INPUT_SERVICE_H
