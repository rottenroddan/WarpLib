//
// Created by Steven Roddan on 12/21/2025.
//

#include <warp/host/test.h>
#include <warp/device/CudaKernels.h>

void warp::test() {
    warp::device::test((float*) nullptr);

    std::cout << "Test" << std::endl;
}