//
// Created by Steven Roddan on 1/25/2026.
//

#ifndef WARPLIB_TRANSFORMERS_HPP
#define WARPLIB_TRANSFORMERS_HPP

#include <cassert>
#include <warp/host/common.hpp>

#include <warp/shared/detail.hpp>
#include <warp/shared/layout/TileRowMajorLayout.hpp>
#include <warp/shared/layout/TileColMajorLayout.hpp>
#include <warp/host/resources/CudaDeviceResource.hpp>

#include <warp/device/Common.cuh>
#include <warp/device/CudaKernels.h>
#include <warp/device/DeviceTransformers.cuh>

namespace warp::transformers {
    /**
     * @brief High-priority fast-path matrix copy using raw memory transfer.
     *
     * This overload participates in the internal copy dispatch mechanism and is
     * selected when both the source and destination matrices:
     *   - Share the exact same value type,
     *   - Share the exact same memory layout,
     *   - Are CPU-accessible resources.
     *
     * Under these conditions, the matrices are guaranteed to be memory-compatible,
     * allowing the copy to be performed as a single contiguous `memcpy`, avoiding
     * any element-wise access or layout transformation.
     *
     * The `priority_1` tag gives this overload precedence over lower-priority
     * implementations during overload resolution. If the constraints are not
     * satisfied, this overload is discarded and a lower-priority copy path is
     * considered instead.
     *
     * @tparam DstMatrix Destination matrix type.
     * @tparam SrcMatrix Source matrix type.
     * @param dst Destination matrix (must be CPU-accessible).
     * @param src Source matrix (must be CPU-accessible).
     * @param priority Internal dispatch tag indicating high priority.
     *
     * @note This function assumes identical logical dimensions at runtime and
     *       asserts if the matrices differ in size.
     */
    template<typename DstMatrix, typename SrcMatrix>
    requires
        std::is_same_v<typename DstMatrix::value_type, typename SrcMatrix::value_type> &&
        std::is_same_v<typename DstMatrix::layout_type, typename SrcMatrix::layout_type> &&
        DstMatrix::resource_type::cpu_accessible && SrcMatrix::resource_type::cpu_accessible
    void copy(DstMatrix& dst, const SrcMatrix& src, detail::internal::priority_1) {
        assert((common::isExactSameDimensions<DstMatrix, SrcMatrix>(dst, src)));
        memcpy(dst.getRaw(), src.getRaw(), dst.getActualTotalSize() * sizeof(DstMatrix::value_type));
    }

    /**
     * @brief Low-priority generic element-wise matrix copy.
     *
     * This overload serves as a safe fallback when a raw memory copy is not
     * possible due to mismatched value types and/or differing memory layouts.
     * It performs the copy by accessing each logical element individually and
     * assigning it to the destination matrix with an explicit value conversion.
     *
     * The `priority_0` tag gives this overload the lowest precedence in the copy
     * dispatch chain. It is only selected when no higher-priority copy overload
     * is viable for the given matrix types.
     *
     * This implementation guarantees correctness for CPU-accessible matrices
     * regardless of layout differences, at the cost of reduced performance
     * compared to the raw-memory fast path.
     *
     * @tparam DstMatrix Destination matrix type.
     * @tparam SrcMatrix Source matrix type.
     * @param dst Destination matrix (must be CPU-accessible).
     * @param src Source matrix (must be CPU-accessible).
     * @param priority Internal dispatch tag indicating lowest priority.
     *
     * @note This function assumes identical logical dimensions at runtime and
     *       asserts if the matrices differ in size.
     */
    template<typename DstMatrix, typename SrcMatrix>
    requires
        (!std::is_same_v<typename DstMatrix::value_type, typename SrcMatrix::value_type> ||
            !std::is_same_v<typename DstMatrix::layout_type, typename SrcMatrix::layout_type>) &&
        DstMatrix::resource_type::cpu_accessible && SrcMatrix::resource_type::cpu_accessible
    void copy(DstMatrix& dst, const SrcMatrix& src, detail::internal::priority_0) {
        assert((common::isSameDimensions<DstMatrix, SrcMatrix>(dst, src)));
        for (size_t i = 0; i < dst.getRows(); ++i) {
            for (size_t j = 0; j < dst.getCols(); ++j) {
                dst.at(i, j) = static_cast<DstMatrix::value_type>(src.get(i, j));
            }
        }
    }

    template<typename DstMatrix, typename SrcMatrix>
    requires
        std::is_same_v<typename DstMatrix::value_type, typename SrcMatrix::value_type> &&
        std::is_same_v<typename DstMatrix::layout_type, typename SrcMatrix::layout_type> &&
        DstMatrix::resource_type::cpu_accessible && (!SrcMatrix::resource_type::cpu_accessible) // device->host
    void copy(DstMatrix& dst, const SrcMatrix& src, detail::internal::priority_1) {
        assert((common::isExactSameDimensions<DstMatrix, SrcMatrix>(dst, src)));
        cudaMemcpy(dst.getRaw(), src.getRaw(), dst.getActualTotalSize() * sizeof(DstMatrix::value_type), cudaMemcpyDeviceToHost);
    }

    template<typename DstMatrix, typename SrcMatrix>
    requires
        std::is_same_v<typename DstMatrix::value_type, typename SrcMatrix::value_type> &&
        std::is_same_v<typename DstMatrix::layout_type, typename SrcMatrix::layout_type> &&
        (!DstMatrix::resource_type::cpu_accessible) && SrcMatrix::resource_type::cpu_accessible // host->device
    void copy(DstMatrix& dst, const SrcMatrix& src, detail::internal::priority_1) {
        assert((common::isExactSameDimensions<DstMatrix, SrcMatrix>(dst, src)));
        cudaMemcpy(dst.getRaw(), src.getRaw(), dst.getActualTotalSize() * sizeof(DstMatrix::value_type), cudaMemcpyHostToDevice);
    }

    template<typename DstMatrix, typename SrcMatrix>
    requires
        std::is_same_v<typename DstMatrix::value_type, typename SrcMatrix::value_type> &&
        std::is_same_v<typename DstMatrix::layout_type, typename SrcMatrix::layout_type> &&
        (!DstMatrix::resource_type::cpu_accessible) && (!SrcMatrix::resource_type::cpu_accessible) // device->device
    void copy(DstMatrix& dst, const SrcMatrix& src, detail::internal::priority_1) {
        assert((common::isExactSameDimensions<DstMatrix, SrcMatrix>(dst, src)));
        cudaMemcpy(dst.getRaw(), src.getRaw(), dst.getActualTotalSize() * sizeof(DstMatrix::value_type), cudaMemcpyDeviceToDevice);
    }

    template<typename DstMatrix, typename SrcMatrix>
    requires
        (!std::is_same_v<typename DstMatrix::value_type, typename SrcMatrix::value_type>) &&
        std::is_same_v<typename DstMatrix::layout_type, typename SrcMatrix::layout_type> &&
        DstMatrix::resource_type::cpu_accessible && (!SrcMatrix::resource_type::cpu_accessible) // device->host
    void copy(DstMatrix& dst, const SrcMatrix& src, detail::internal::priority_1) {
        assert((common::isExactSameDimensions<DstMatrix, SrcMatrix>(dst, src)));
        kernels::launchCastOnKernelFromAToB(dst.getRaw(), src.getRaw(), dst.getActualTotalSize());
    }
}

#endif //WARPLIB_TRANSFORMERS_HPP