///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_DRIVER_VISUAL_ATTENTION_H
#define PERCEPTION_DRIVER_VISUAL_ATTENTION_H

#include "perception/datatypes/driver.h"
#include "perception/driver/i_data_source.h"
#include "perception/driver/i_parameters.h"

namespace perception
{
class VisualAttention
{
  public:
    explicit VisualAttention(const IParameters& parameters, const IDataSource& data_source);

    void Init();
    void ExecuteStep();
    void Shutdown();

    const VisualAttentionMessage& GetVisualAttentionMessage();

  private:
    const IParameters& parameters_;
    const IDataSource& data_source_;

    VisualAttentionMessage visual_attention_message_;
};
}  // namespace perception
#endif  /// PERCEPTION_DRIVER_VISUAL_ATTENTION_H
