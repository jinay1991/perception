///
/// @file
///
#ifndef PERCEPTION_OBJECT_DETECT_I_OBJECT_DETECT_H_
#define PERCEPTION_OBJECT_DETECT_I_OBJECT_DETECT_H_

namespace perception
{
class IObjectDetect
{
  public:
    virtual void Detect() const = 0;
};
}  // namespace perception

#endif  /// PERCEPTION_OBJECT_DETECT_I_OBJECT_DETECT_H_