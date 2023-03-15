///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_LANE_LANE_H
#define PERCEPTION_LANE_LANE_H

#include "perception/datatypes/lane.h"
#include "perception/sensor/camera/datatype/camera.h"

namespace perception
{
/// @brief Lane Detection
class Lane
{
  public:
    /// @brief Constructor
    Lane();

    /// @brief Initialize Lane Detection
    void Init();

    /// @brief Execute Single Step (performs Lane detection and updates lane information)
    void Step();

    /// @brief Release resources used for Lane Detections
    void Shutdown();

    /// @brief Set Camera Message, containing captured images
    ///
    /// @param camera_message [in] - Camera captured image Message
    void SetCameraMessage(const CameraMessage& camera_message);

    /// @brief Provide Lane Message based on identified Lane Points from the given Camera image
    const LaneMessage& GetLaneMessage() const;

  private:
    /// @brief Update Outputs (aka Lane)
    void UpdateOutputs();

    /// @brief Received Camera Image message
    CameraMessage camera_message_;

    /// @brief Calculated lane points
    LaneMessage lane_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_LANE_LANE_H
