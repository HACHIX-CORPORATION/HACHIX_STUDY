// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018-2021 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------
//

#include "ATen/cuda/CUDAContext.h"
#include "open3d/ml/impl/misc/Voxelize.cuh"
#include "open3d/ml/pytorch/TorchHelper.h"
#include "open3d/ml/pytorch/misc/VoxelizeOpKernel.h"
#include "torch/script.h"

using namespace open3d::ml::impl;

template <class T>
void VoxelizeCUDA(const torch::Tensor& points,
                  const torch::Tensor& row_splits,
                  const torch::Tensor& voxel_size,
                  const torch::Tensor& points_range_min,
                  const torch::Tensor& points_range_max,
                  const int64_t max_points_per_voxel,
                  const int64_t max_voxels,
                  torch::Tensor& voxel_coords,
                  torch::Tensor& voxel_point_indices,
                  torch::Tensor& voxel_point_row_splits,
                  torch::Tensor& voxel_batch_splits) {
    auto stream = at::cuda::getCurrentCUDAStream();
    auto cuda_device_props = at::cuda::getCurrentDeviceProperties();
    const int texture_alignment = cuda_device_props->textureAlignment;

    VoxelizeOutputAllocator output_allocator(points.device().type(),
                                             points.device().index());

    switch (points.size(1)) {
#define CASE(NDIM)                                                            \
    case NDIM: {                                                              \
        void* temp_ptr = nullptr;                                             \
        size_t temp_size = 0;                                                 \
        VoxelizeCUDA<T, NDIM>(                                                \
                stream, temp_ptr, temp_size, texture_alignment,               \
                points.size(0), points.data_ptr<T>(), row_splits.size(0) - 1, \
                row_splits.data_ptr<int64_t>(), voxel_size.data_ptr<T>(),     \
                points_range_min.data_ptr<T>(),                               \
                points_range_max.data_ptr<T>(), max_points_per_voxel,         \
                max_voxels, output_allocator);                                \
                                                                              \
        auto temp_tensor =                                                    \
                CreateTempTensor(temp_size, points.device(), &temp_ptr);      \
                                                                              \
        VoxelizeCUDA<T, NDIM>(                                                \
                stream, temp_ptr, temp_size, texture_alignment,               \
                points.size(0), points.data_ptr<T>(), row_splits.size(0) - 1, \
                row_splits.data_ptr<int64_t>(), voxel_size.data_ptr<T>(),     \
                points_range_min.data_ptr<T>(),                               \
                points_range_max.data_ptr<T>(), max_points_per_voxel,         \
                max_voxels, output_allocator);                                \
    } break;
        CASE(1)
        CASE(2)
        CASE(3)
        CASE(4)
        CASE(5)
        CASE(6)
        CASE(7)
        CASE(8)
        default:
            break;  // will be handled by the generic torch function

#undef CASE
    }

    voxel_coords = output_allocator.VoxelCoords();
    voxel_point_indices = output_allocator.VoxelPointIndices();
    voxel_point_row_splits = output_allocator.VoxelPointRowSplits();
    voxel_batch_splits = output_allocator.VoxelBatchSplits();
}

#define INSTANTIATE(T)                                                       \
    template void VoxelizeCUDA<T>(                                           \
            const torch::Tensor& points, const torch::Tensor& row_splits,    \
            const torch::Tensor& voxel_size,                                 \
            const torch::Tensor& points_range_min,                           \
            const torch::Tensor& points_range_max,                           \
            const int64_t max_points_per_voxel, const int64_t max_voxels,    \
            torch::Tensor& voxel_coords, torch::Tensor& voxel_point_indices, \
            torch::Tensor& voxel_point_row_splits,                           \
            torch::Tensor& voxel_batch_splits);

INSTANTIATE(float)
INSTANTIATE(double)
