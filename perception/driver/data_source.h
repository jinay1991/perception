///
/// @file
/// @copyright Copyright (c) 2020. MIT License
///
#ifndef PERCEPTION_DRIVER_DATA_SOURCE_H
#define PERCEPTION_DRIVER_DATA_SOURCE_H

#include "perception/driver/i_data_source.h"

namespace perception
{
class DataSource final : public IDataSource
{
  public:
    DataSource() {}
    ~DataSource() = default;
};
}  // namespace perception

#endif  /// PERCEPTION_DRIVER_DATA_SOURCE_H