///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRA_PROCESS_SUBCRIBER_H_
#define PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRA_PROCESS_SUBCRIBER_H_

#include "perception/middleware/communication/i_subscriber.h"
#include "perception/middleware/communication/intra_process_pub_sub_factory.h"

#include <memory>

namespace perception
{
class IntraProcessSubscriber : public ISubscriber
{
  public:
    IntraProcessSubscriber(IntraProcessPubSubFactory* factory) : factory_{factory} {}
    virtual ~IntraProcessSubscriber() = default;

    virtual void Update() override { factory_->Update(); }

  private:
    IntraProcessPubSubFactory* factory_;
};

}  // namespace perception

#endif  /// PERCEPTION_MIDDLEWARE_COMMUNICATION_INTRA_PROCESS_SUBCRIBER_H_