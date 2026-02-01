//
// Created by Steven Roddan on 12/21/2025.
//

#pragma once
#include <cstdio>



namespace warp::kernels {
    __device__ void hello_world() {
        printf("Hello World From CUDA nerdosssaskdks!\n");
    }
}