///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_DRIVER_H
#define PERCEPTION_DRIVER_DRIVER_H

#include "perception/datatypes/driver.h"
#include "perception/driver/data_source.h"
#include "perception/driver/fatigue.h"
#include "perception/driver/parameters.h"
#include "perception/driver/visual_attention.h"

namespace perception
{
class Driver
{
  public:
    Driver();

    void Init();
    void ExecuteStep();
    void Shutdown();

    const VisualAttentionMessage& GetVisualAttentionMessage();
    const FatigueMessage& GetFatigueMessage();

  private:
    Parameters parameters_;
    DataSource data_source_;
    Fatigue fatigue_;
    VisualAttention visual_attention_;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DRIVER_H
