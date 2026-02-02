//
// Created by Steven Roddan on 1/27/2026.
//

#include <warp/device/device_transformers.hpp>
#include <warp/device/device_transformers_kernels.cuh>

namespace warp::transformers::kernels {
    // template<typename T, typename U>
    // __global__ void _castArrayKernelRestrict(T* __restrict__ dst, const U* __restrict__ src, const size_t size) {
    //     for (size_t i = blockDim.x * blockIdx.x + threadIdx.x; i < size; i+= blockDim.x * gridDim.x) {
    //         dst[i] = static_cast<T>(src[i]);
    //     }
    // }
    //
    // template<typename T, typename U>
    // __global__ void _castArrayKernel(T* dst, const U* src, const size_t size) {
    //     for (size_t i = blockDim.x * blockIdx.x + threadIdx.x; i < size; i+= blockDim.x * gridDim.x) {
    //         dst[i] = static_cast<T>(src[i]);
    //     }
    // }

    template<typename T, typename U>
    WARP_DEVICE_API void launchCastDataOnCudaKernel(T* const dst, U* const src, const size_t size, const bool restrictPtrs) {
        int numOfSms = 0;
        int device;
        CUDA_CHECK(cudaGetDevice(&device));
        CUDA_CHECK(cudaDeviceGetAttribute(&numOfSms, cudaDevAttrMultiProcessorCount, device));

        dim3 threadBlock(WARP_CUDA_DEFAULT_THREAD_COUNT);

        const unsigned int potentialBlocks = (WARP_CUDA_DEFAULT_THREAD_COUNT + size - 1) / WARP_CUDA_DEFAULT_THREAD_COUNT;
        const unsigned int blocks = potentialBlocks < numOfSms ? potentialBlocks : numOfSms;

        std::cout << "Data Size: " << size << "\n";
        std::cout << "SMs Available: " << numOfSms << "\n";
        std::cout << "Threads Per Block: " << WARP_CUDA_DEFAULT_THREAD_COUNT << "\n";
        std::cout << "Blocks launching for this kernel: " << blocks << "\n";
        std::cout << "Total Strides for most blocks: " << static_cast<int>(std::ceil(size / (blocks * WARP_CUDA_DEFAULT_THREAD_COUNT))) << "\n" << std::flush;

        dim3 grid(blocks);
        if (restrictPtrs) {
            _castArrayKernelRestrict<<<grid, threadBlock>>>(dst, src, size);
        }
        else {
            _castArrayKernel<<<grid, threadBlock>>>(dst, src, size);
        }
        CUDA_CHECK(cudaDeviceSynchronize());
        CUDA_CHECK(cudaGetLastError());
    }

    //template WARP_DEVICE_API void launchCastDataOnCudaKernel(int*, float*, size_t, bool);
    //template WARP_DEVICE_API void launchCastDataOnCudaKernel(float*, int*, size_t, bool);
}