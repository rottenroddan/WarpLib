//
// Created by steve on 1/15/2026.
//

#ifndef WARPLIB_VALIDATIONKERNELS_CUH
#define WARPLIB_VALIDATIONKERNELS_CUH

template<typename T>
__global__ void _validateArray(T* _truth, T* _validation, int totalSize, bool* answer) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < totalSize && _truth[index] != _validation[index]) {
        *answer = false;
    }
}

template<typename T>
bool validateArray(T* _truth, T* _validation, int totalSize) {
    bool h_result = true;
    bool* d_result;
    cudaMalloc(reinterpret_cast<void **>(&d_result), sizeof(bool));
    cudaMemcpy(d_result, &h_result, sizeof(bool), cudaMemcpyHostToDevice);

    dim3 threadBlock(256);
    dim3 grid((totalSize - 1) / threadBlock.x + 1 );
    _validateArray<T><<<grid, threadBlock>>>(_truth, _validation, totalSize, d_result);

    cudaDeviceSynchronize();
    cudaMemcpy(&h_result, d_result, sizeof(bool), cudaMemcpyDeviceToHost);
    cudaFree(d_result);
    return h_result;
}

#endif //WARPLIB_VALIDATIONKERNELS_CUH