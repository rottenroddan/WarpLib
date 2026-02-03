//
// Created by Steven Roddan on 1/25/2026.
//

#include <warp/WarpLib.hpp>
#include <gtest/gtest.h>

size_t COLS = 512;
size_t ROWS = 512;

template<typename T, typename U>
static void validate(T truth, U test) {
    for (size_t i = 0; i < truth.getRows(); i++) {
        for (size_t j = 0; j < truth.getCols(); j++) {
            //std::cout << truth.get(i,j) << " vs " << test.get(i,j) << " ";
            ASSERT_EQ(truth.get(i,j), test.get(i,j)) << "Failed at: i:" << i << " j:" << j;
        }
        //std::cout << std::endl;
    }
}

template<typename T>
static void populateWithMemIndex(T& t) {
    int idx = 0;
    for (size_t i = 0; i < t.getRows(); i++) {
        for (size_t j = 0; j < t.getCols(); j++) {
            t.at(i,j) = static_cast<T::value_type>(idx);
            idx++;
        }
    }
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromGenericHostToGenericHostWithSameLayouts) {
    using namespace warp;
    Matrix<int, mem::resource::GenericHostResource> truth(ROWS, COLS);
    Matrix<int, mem::resource::GenericHostResource> test(ROWS, COLS);
    ASSERT_EQ(truth.getRows(), test.getRows());
    ASSERT_EQ(truth.getCols(), test.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test);
    return validate(truth, test);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromCachedHostToCachedHostWithSameLayouts) {
    using namespace warp;
    Matrix<int, mem::resource::HostCacheAlignedResource> truth(ROWS, COLS);
    Matrix<int, mem::resource::HostCacheAlignedResource> test(ROWS, COLS);
    ASSERT_EQ(truth.getRows(), test.getRows());
    ASSERT_EQ(truth.getCols(), test.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test);
    return validate(truth, test);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromCudaManagedToCudaManagedWithSameLayouts) {
    using namespace warp;
    Matrix<int, mem::resource::CudaManagedResource> truth(ROWS, COLS);
    Matrix<int, mem::resource::CudaManagedResource> test(ROWS, COLS);
    ASSERT_EQ(truth.getRows(), test.getRows());
    ASSERT_EQ(truth.getCols(), test.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test);
    return validate(truth, test);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromCudaPinnedToCudaPinnedWithSameLayouts) {
    using namespace warp;
    Matrix<int, mem::resource::CudaPinnedResource> truth(ROWS, COLS);
    Matrix<int, mem::resource::CudaPinnedResource> test(ROWS, COLS);
    ASSERT_EQ(truth.getRows(), test.getRows());
    ASSERT_EQ(truth.getCols(), test.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test);
    return validate(truth, test);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromGenericHostToGenericHostWithRowToRowLayout) {
    using namespace warp;
    Matrix<int, mem::resource::GenericHostResource, mem::layout::TileRowMajorLayout<16>> truth(ROWS, COLS);
    Matrix<int, mem::resource::GenericHostResource, mem::layout::TileRowMajorLayout<16>> test(ROWS, COLS);
    ASSERT_EQ(truth.getRows(), test.getRows());
    ASSERT_EQ(truth.getCols(), test.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test);
    return validate(truth, test);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromGenericHostToGenericHostWithRowToColLayout) {
    using namespace warp;
    Matrix<int, mem::resource::GenericHostResource, mem::layout::TileRowMajorLayout<16>> truth(ROWS, COLS);
    Matrix<int, mem::resource::GenericHostResource, mem::layout::TileColMajorLayout<16>> test(ROWS, COLS);
    ASSERT_EQ(truth.getRows(), test.getRows());
    ASSERT_EQ(truth.getCols(), test.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test);
    return validate(truth, test);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromGenericHostToGenericHostWithColToRowLayout) {
    using namespace warp;
    Matrix<int, mem::resource::GenericHostResource, mem::layout::TileColMajorLayout<16>> truth(ROWS, COLS);
    Matrix<int, mem::resource::GenericHostResource, mem::layout::TileRowMajorLayout<16>> test(ROWS, COLS);
    ASSERT_EQ(truth.getRows(), test.getRows());
    ASSERT_EQ(truth.getCols(), test.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test);
    return validate(truth, test);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromGenericHostToGenericHostWithColToColLayout) {
    using namespace warp;
    Matrix<int, mem::resource::GenericHostResource, mem::layout::TileColMajorLayout<16>> truth(ROWS, COLS);
    Matrix<int, mem::resource::GenericHostResource, mem::layout::TileColMajorLayout<16>> test(ROWS, COLS);
    ASSERT_EQ(truth.getRows(), test.getRows());
    ASSERT_EQ(truth.getCols(), test.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test);
    return validate(truth, test);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromGenericHostToCudaDeviceBackToHostWithSameLayout) {
    using namespace warp;
    Matrix<int, mem::resource::CudaPinnedResource> truth(ROWS, COLS);
    Matrix<int, mem::resource::CudaDeviceResource> test_device(ROWS, COLS);
    Matrix<int, mem::resource::CudaPinnedResource> test_host(ROWS, COLS);

    ASSERT_EQ(truth.getRows(), test_device.getRows());
    ASSERT_EQ(truth.getCols(), test_device.getCols());
    ASSERT_EQ(truth.getRows(), test_host.getRows());
    ASSERT_EQ(truth.getCols(), test_host.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test_device);
    test_device.copyTo(test_host);
    return validate(truth, test_host);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromGenericHostToCudaDeviceBackToHostWithSameLayoutDifferentTypes) {
    using namespace warp;
    Matrix<int, mem::resource::CudaPinnedResource> truth(ROWS, COLS);
    Matrix<int, mem::resource::CudaDeviceResource> test_device(ROWS, COLS);
    Matrix<float, mem::resource::CudaPinnedResource> test_host(ROWS, COLS);

    ASSERT_EQ(truth.getRows(), test_device.getRows());
    ASSERT_EQ(truth.getCols(), test_device.getCols());
    ASSERT_EQ(truth.getRows(), test_host.getRows());
    ASSERT_EQ(truth.getCols(), test_host.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test_device);
    test_device.copyTo(test_host);

    return validate(truth, test_host);
}

TEST(MatrixTransformerTestSuite, HandlesCopyFromGenericHostToCudaDeviceBackToHostWithDifferentLayoutSameTypes) {
    using namespace warp;
    Matrix<int, mem::resource::CudaPinnedResource, mem::layout::TileRowMajorLayout<16>> truth(ROWS, COLS);
    Matrix<int, mem::resource::CudaDeviceResource, mem::layout::TileRowMajorLayout<16>> test_device(ROWS, COLS);
    Matrix<int, mem::resource::CudaPinnedResource> test_host(ROWS, COLS);

    ASSERT_EQ(truth.getRows(), test_device.getRows());
    ASSERT_EQ(truth.getCols(), test_device.getCols());
    ASSERT_EQ(truth.getRows(), test_host.getRows());
    ASSERT_EQ(truth.getCols(), test_host.getCols());

    populateWithMemIndex(truth);
    truth.copyTo(test_device);
    test_device.copyTo(test_host);

    return validate(truth, test_host);
}