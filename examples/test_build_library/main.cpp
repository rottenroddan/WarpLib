//
// Created by Steven Roddan on 12/21/2025.
//

#include <warp/host/test.h>
#include <warp/device/CudaKernels.h>

#include <warp/host/Matrix.hpp>
#include <warp/host/resources/CudaDeviceResource.hpp>

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

struct C {
    int x {100};
};


int main() {
    const C* const c = new C();

    std::cout << c->x << std::endl;
    std::cout << c->x
    << std::endl;


    delete c;


    A<int> a;
    B<int> b;

    a.foo(b);

    // host lib
    warp::test();

    warp::device::test((float*)nullptr);

    warp::Matrix<int> mat(100,100);

    warp::Matrix<int, warp::resource::CudaDeviceResource> dev(100, 100);
}