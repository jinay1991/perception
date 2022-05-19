///
/// @file
/// @copyright Copyright (c) 2022. NVIDIA Corporation. All Rights Reserved.
///
#include <iostream>

__global__ void Kernel()
{
    printf("Hello CUDA!\n");
}

int main()
{
    Kernel<<<1, 1>>>();
    cudaDeviceSynchronize();
    return 0;
}
