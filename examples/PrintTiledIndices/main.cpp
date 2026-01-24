//
// Created by Steven Roddan on 1/21/2026.
//

#include <warp/shared/layout/TileRowMajorLayout.hpp>
#include <warp/shared/layout/TileColMajorLayout.hpp>
#include <warp/host/Matrix.hpp>

#include <iomanip>
#include <iostream>

constexpr size_t tile_size = 4;

template<typename T>
void printMat(const T& mat ) {
    for (size_t ii = 0; ii < mat.getRows(); ++ii) {
        for (size_t jj = 0; jj < mat.getCols(); ++jj) {
            std::cout << std::setw(3) << mat.get(ii,jj) << ((jj + 1) % tile_size == 0 ? " | " : " ");
        }
        std::cout << "\n";
        if ((ii + 1) % tile_size == 0) {
            for (size_t kk = 0; kk < mat.getCols() * 4 + (mat.getActualCols() / tile_size) * 2; ++kk) {
                std::cout << "-";
            }
            std::cout << "\n";
        }
    }std::cout << std::flush;
}

int main() {
    const warp::Matrix<int, warp::resource::GenericHostResource, warp::mem::layout::TileRowMajorLayout<tile_size>> rowMat(16,16);
    int* raw = rowMat.getRaw();
    for (size_t ii = 0; ii < rowMat.getActualRows()*rowMat.getActualCols(); ++ii) {
        raw[ii] = static_cast<int>(ii);
    }

    const warp::Matrix<int, warp::resource::GenericHostResource, warp::mem::layout::TileColMajorLayout<tile_size>> colMat(16,16);
    raw = colMat.getRaw();
    for (size_t ii = 0; ii < colMat.getActualRows()*colMat.getActualCols(); ++ii) {
        raw[ii] = static_cast<int>(ii);
    }

    std::cout << "Tiled Row Matrix\n";
    printMat(rowMat);
    std::cout << "\n\n";
    std::cout << "Tiled Column Matrix\n";
    printMat(colMat);
    std::cout << std::flush;
}