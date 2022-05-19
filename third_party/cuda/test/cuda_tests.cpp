///
/// @file
/// @copyright Copyright (c) 2022. MIT License.
///
#include <cuda_runtime.h>
#include <gtest/gtest.h>

#include <cstdint>

namespace
{

TEST(DeviceManagement, cudaGetDeviceProperties_ExpectDeviceCount)
{
    // Given
    std::int32_t device_count = 0;

    // When
    ASSERT_EQ(cudaGetDeviceCount(&device_count), cudaError::cudaSuccess);

    // Then
    EXPECT_EQ(device_count, 1);
}

TEST(DeviceManagement, cudaGetDeviceProperties_ExpectDeviceProperties)
{
    // Given
    std::int32_t device_id = 0;
    cudaDeviceProp device_properties;

    // When
    ASSERT_EQ(cudaGetDeviceProperties(&device_properties, device_id), cudaError::cudaSuccess);

    // Then
    EXPECT_EQ(device_properties.computeMode, cudaComputeMode::cudaComputeModeDefault);
    EXPECT_EQ(device_properties.major, 6);
    EXPECT_EQ(device_properties.minor, 1);
    EXPECT_EQ(device_properties.totalGlobalMem, 8512733184);
    EXPECT_EQ(device_properties.sharedMemPerBlock, 49152);
    EXPECT_EQ(device_properties.warpSize, 32);
}

TEST(MemoryManagement, cudaMalloc_ExpectDeviceProperties)
{
    // Given
    std::int32_t* buffer = nullptr;
    std::size_t buffer_size = 12001UL;

    // When
    ASSERT_EQ(cudaMalloc(&buffer, buffer_size), cudaError::cudaSuccess);

    // Then
    EXPECT_NE(buffer, nullptr);
    ASSERT_EQ(cudaFree(buffer), cudaError::cudaSuccess);
}

}  // namespace
