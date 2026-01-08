//
// Created by Steven Roddan on 12/21/2025.
//

#include <warp/device/CudaKernels.h>
#include <warp/device/Common.cuh>

namespace warp::device {
    template<typename T>
    __global__ void test_kernel() {
        kernels::hello_world();
    }

    template<typename T>
    void test_kernel_impl(T* x) {
        test_kernel<T><<<1,1,1>>>();
        cudaDeviceSynchronize();
    }

    void test(float* x) {
        test_kernel_impl<float>(x);
    }

    void test(double* x) {
        test_kernel_impl<double>(x);
    }
}