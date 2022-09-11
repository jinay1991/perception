///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#ifndef PERCEPTION_DRIVER_ACTIVITY_DETECTOR_H
#define PERCEPTION_DRIVER_ACTIVITY_DETECTOR_H

#include "perception/driver/i_activity_data_source.h"
#include "perception/driver/i_activity_detector.h"
#include "perception/driver/i_activity_parameter_handler.h"

namespace perception
{
namespace driver
{
/// @brief Definition class of Interface for Activity Detection
class ActivityDetector : public IActivityDetector
{
  public:
    /// @brief Default Constructor
    ///
    /// @param parameter_handler [in] - Instance of the Activity Parameter Handler
    /// @param data_source [in] - Instance of the Activity Data Source
    explicit ActivityDetector(const IActivityParameterHandler& parameter_handler,
                              const IActivityDataSource& data_source);

    /// @brief Calculate Driver's Activity based on the received data
    void Step() override;

    /// @brief Provides the Activity State, determined based on the received data
    ///
    /// @return state
    ActivityState GetActivityState() const override;

    /// @brief Provides the Activity State confidence, determined based on the received data
    ///
    /// @return confidence [Range: (0.0, 1.0)]
    double GetActivityConfidence() const override;

  private:
    /// @brief Determine Activity State
    void DetermineActivityState();

    /// @brief Determine Activity State confidence [Range: (0.0, 1.0)]
    void DetermineActivityConfidence();

    /// @brief Instance of the Parameter handler
    const IActivityParameterHandler& parameter_handler_;

    /// @brief Instance of Data Source
    const IActivityDataSource& data_source_;

    /// @brief Activity State
    ActivityState state_;

    /// @brief Activity state confidence [Range: (0.0, 1.0)]
    double confidence_;
};
}  // namespace driver
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_ACTIVITY_DETECTOR_H
