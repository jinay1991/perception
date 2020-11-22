///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_LANE_LANE_H
#define PERCEPTION_LANE_LANE_H

namespace perception
{
/// @brief Lane Detection
class Lane
{
  public:
    /// @brief Lane Detection
    Lane();

    /// @brief Initialize Lane Detection
    void Init();

    /// @brief Execute Single Step (performs Lane detection and updates lane information)
    void Step();

    /// @brief Release resources used for Lane Detections
    void Shutdown();
};
}  // namespace perception
#endif  /// PERCEPTION_LANE_LANE_H
