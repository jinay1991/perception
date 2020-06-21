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
    Lane();

    void Init();
    void Step();
    void Shutdown();
};
}  // namespace perception
#endif  /// PERCEPTION_LANE_LANE_H
