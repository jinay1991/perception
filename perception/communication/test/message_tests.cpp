///
///
/// @file
/// @copyright Copyright (c) 2021. MIT License.
///
#include "perception/communication/message.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace communication
{
namespace
{
struct TestMessageA
{
    std::int32_t x;
};
struct TestMessageB
{
    std::int32_t x;
};

struct TestMessageC
{
    std::int32_t x;
};

TEST(MessageTest, MessageId_GivenTypicalMessagePtr_ExpectMessageId)
{
    constexpr TestMessageA message_a{0};
    auto unit_a = CreateMessage<TestMessageA>(message_a);
    EXPECT_EQ(1, unit_a->GetMessageId());

    constexpr TestMessageB message_b{10};
    auto unit_b = CreateMessage<TestMessageB>(message_b);
    EXPECT_EQ(2, unit_b->GetMessageId());

    constexpr TestMessageC message_c{122};
    auto unit_c = CreateMessage<TestMessageC>(message_c);
    EXPECT_EQ(3, unit_c->GetMessageId());
}
}  // namespace
}  // namespace communication
}  // namespace perception
