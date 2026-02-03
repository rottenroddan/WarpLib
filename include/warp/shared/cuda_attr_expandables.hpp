//
// Created by Steven Roddan on 1/9/2026.
//

#ifndef WARPLIB_CUDA_ATTR_EXPANDABLES_HPP
#define WARPLIB_CUDA_ATTR_EXPANDABLES_HPP

#if defined(__CUDACC__)
    #define HOST_DEVICE __host__ __device__
    #define HOST __host__
    #define DEVICE __device__
#else
    #define HOST_DEVICE
    #define HOST
    #define DEVICE
#endif


#endif
