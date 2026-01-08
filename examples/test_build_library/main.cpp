//
// Created by Steven Roddan on 12/21/2025.
//

#include <warp/host/test.h>
#include <warp/device/CudaKernels.h>

#include <warp/host/Matrix.hpp>

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


int main() {

    A<int> a;
    B<int> b;

    a.foo(b);

    // host lib
    warp::test();

    warp::device::test((float*)nullptr);

    warp::Matrix<int> mat(100,100);
}