//
// Created by Steven Roddan on 1/27/2026.
//

#include <warp/device/device_transformers.hpp>
#include <warp/device/device_transformers_kernels.cuh>

namespace warp::transformers::kernels {
    template<typename DstType, typename SrcType, typename DstLayout, typename SrcLayout>
    WARP_DEVICE_API void launchCopyOnCudaKernel(DstType* dst, SrcType* src, const size_t rows, const size_t cols,
                                                const size_t actualRows, const size_t actualCols, const size_t tileSize) {
        WARP_CUDA_CHECK_FOR_IMPLICIT_HOST_MEMORY(src);
        WARP_CUDA_CHECK_FOR_IMPLICIT_HOST_MEMORY(dst);

        _copyMatrixAcrossLayouts<DstType, SrcType, DstLayout, SrcLayout><<<1,1>>>(dst, src, rows, cols, actualRows, actualCols, tileSize);
        WARP_CUDA_ERROR_CHECK(cudaDeviceSynchronize());
        WARP_CUDA_ERROR_CHECK(cudaGetLastError());
    }

    template<typename DstType, typename SrcType>
    WARP_DEVICE_API void launchCopyCastDataOnCudaKernel(DstType* dst, SrcType* src, const size_t size, const bool restrictPtrs) {
        WARP_CUDA_CHECK_FOR_IMPLICIT_HOST_MEMORY(src);
        WARP_CUDA_CHECK_FOR_IMPLICIT_HOST_MEMORY(dst);

        int numOfSms = 0;
        int device;
        WARP_CUDA_ERROR_CHECK(cudaGetDevice(&device));
        WARP_CUDA_ERROR_CHECK(cudaDeviceGetAttribute(&numOfSms, cudaDevAttrMultiProcessorCount, device));

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
        WARP_CUDA_ERROR_CHECK(cudaDeviceSynchronize());
        WARP_CUDA_ERROR_CHECK(cudaGetLastError());
    }
}