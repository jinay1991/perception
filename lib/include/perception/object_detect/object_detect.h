///
/// @file
///
#ifndef PERCEPTION_OBJECT_DETECT_OBJECT_DETECT_H_
#define PERCEPTION_OBJECT_DETECT_OBJECT_DETECT_H_

// #include <opencv2/calib3d/calib3d.hpp>
// #include <opencv2/core/core.hpp>
// #include <opencv2/imgproc/imgproc.hpp>

#include "perception/object_detect/i_object_detect.h"

namespace perception
{
class ObjectDetect : public IObjectDetect
{
  public:
    virtual void Detect() const override;

  private:
};
}  // namespace perception

#endif  /// PERCEPTION_OBJECT_DETECT_OBJECT_DETECT_H_