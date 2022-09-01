///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include "perception/object/datatype/test/support/operators.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace perception
{
namespace object
{
namespace
{
using ::testing::HasSubstr;

template <typename T>
class OperatorFixtureT : public ::testing::TestWithParam<T>
{
};

template <typename T>
struct TestStringParam
{
    // Given
    T value;

    // Then
    std::string name;
};

using OperatorsFixture_WithObjectId = OperatorFixtureT<TestStringParam<ObjectId>>;

INSTANTIATE_TEST_SUITE_P(Operators,
                         OperatorsFixture_WithObjectId,
                         ::testing::Values(TestStringParam<ObjectId>{ObjectId::kUnknown, "kUnknown"},
                                           TestStringParam<ObjectId>{ObjectId::kCar, "kCar"},
                                           TestStringParam<ObjectId>{ObjectId::kTruck, "kTruck"},
                                           TestStringParam<ObjectId>{ObjectId::kMotorBike, "kMotorBike"},
                                           TestStringParam<ObjectId>{ObjectId::kBicycle, "kBicycle"},
                                           TestStringParam<ObjectId>{ObjectId::kPedestrian, "kPedestrian"},
                                           TestStringParam<ObjectId>{ObjectId::kAnimal, "kAnimal"},
                                           TestStringParam<ObjectId>{ObjectId::kTrafficSign_Stop, "kTrafficSign_Stop"},
                                           TestStringParam<ObjectId>{ObjectId::kTrafficLight, "kTrafficLight"},
                                           TestStringParam<ObjectId>{ObjectId::kObstacle, "kObstacle"},
                                           TestStringParam<ObjectId>{ObjectId::kInvalid, "kInvalid"},
                                           TestStringParam<ObjectId>{static_cast<ObjectId>(25U), "ERROR"}));

TEST_P(OperatorsFixture_WithObjectId, to_string)
{
    // Given
    const auto param = GetParam();

    // When
    const std::string name = to_string(param.value);

    // Then
    EXPECT_THAT(name, HasSubstr(param.name));
}

TEST_P(OperatorsFixture_WithObjectId, stream_operator)
{
    // Given
    const auto param = GetParam();
    std::ostringstream stream;

    // When
    stream << param.value;

    // Then
    EXPECT_THAT(stream.str(), HasSubstr(param.name));
}

}  // namespace
}  // namespace object
}  // namespace perception
