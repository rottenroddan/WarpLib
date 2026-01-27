//
// Created by Steven Roddan on 1/27/2026.
//

#include <iostream>
#include <ostream>
#include <warp/device/DeviceTransformers.cuh>

namespace warp::transformers::kernels {
    template<typename T, typename U>
    void launchCastOnKernelFromAToB(T* const dst, U* const src, const size_t size) {
        std::cout << "YES!" << std::endl;
    }


    template WARP_DEVICE_API void launchCastOnKernelFromAToB(float*,int*, size_t);
    template WARP_DEVICE_API void launchCastOnKernelFromAToB(int*,float*, size_t);

}