//
// Created by Steven Roddan on 12/21/2025.
//

#include <warp/host/test.h>
#include <warp/device/CudaKernels.h>

#include <warp/host/Matrix.hpp>
#include <warp/host/resources/CudaDeviceResource.hpp>

#include "warp/host/resources/UnifiedMemoryResource.hpp"
#include "warp/shared/layout/GenericLayout.hpp"

template<class T>
class A;

template<class T>
class B;

template<class T>
class A {
public:
    T mem{};
    void foo(B<T> b) {
        std::cout << b.mem << std::endl;
    }
};

template<class T>
class B {
public:
    T mem{};
    void foo(A<T> a) {
        std::cout << a.mem << std::endl;
    }
};

template<typename T = int>
struct C {
    int x {100};
};


int main() {
    warp::Matrix<int, warp::resource::UnifiedMemoryResource, warp::mem::layout::GenericLayout<>> mat(10,10);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << mat.get(i,j) << "  ";
        }
        std::cout << std::endl;
    }
}