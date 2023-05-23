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

#define EIGEN_USE_GPU
#include "BuildSpatialHashTableOpKernel.h"
#include "open3d/core/CUDAUtils.h"
#include "open3d/core/nns/FixedRadiusSearchImpl.cuh"

using namespace open3d;
using namespace tensorflow;

template <class T>
class BuildSpatialHashTableOpKernelCUDA : public BuildSpatialHashTableOpKernel {
public:
    explicit BuildSpatialHashTableOpKernelCUDA(
            OpKernelConstruction* construction)
        : BuildSpatialHashTableOpKernel(construction) {
        texture_alignment =
                open3d::core::GetCUDACurrentDeviceTextureAlignment();
    }

    void Kernel(tensorflow::OpKernelContext* context,
                const tensorflow::Tensor& points,
                const tensorflow::Tensor& radius,
                const tensorflow::Tensor& points_row_splits,
                const std::vector<uint32_t>& hash_table_splits,
                tensorflow::Tensor& hash_table_index,
                tensorflow::Tensor& hash_table_cell_splits) {
        auto device = context->eigen_gpu_device();

        void* temp_ptr = nullptr;
        size_t temp_size = 0;

        // determine temp_size
        open3d::core::nns::impl::BuildSpatialHashTableCUDA(
                device.stream(), temp_ptr, temp_size, texture_alignment,
                points.shape().dim_size(0), points.flat<T>().data(),
                radius.scalar<T>()(), points_row_splits.shape().dim_size(0),
                (int64_t*)points_row_splits.flat<int64>().data(),
                hash_table_splits.data(),
                hash_table_cell_splits.shape().dim_size(0),
                hash_table_cell_splits.flat<uint32_t>().data(),
                hash_table_index.flat<uint32_t>().data());

        Tensor temp_tensor;
        TensorShape temp_shape({ssize_t(temp_size)});
        OP_REQUIRES_OK(context,
                       context->allocate_temp(DataTypeToEnum<uint8_t>::v(),
                                              temp_shape, &temp_tensor));
        temp_ptr = temp_tensor.flat<uint8_t>().data();

        // actually build the table
        open3d::core::nns::impl::BuildSpatialHashTableCUDA(
                device.stream(), temp_ptr, temp_size, texture_alignment,
                points.shape().dim_size(0), points.flat<T>().data(),
                radius.scalar<T>()(), points_row_splits.shape().dim_size(0),
                (int64_t*)points_row_splits.flat<int64>().data(),
                hash_table_splits.data(),
                hash_table_cell_splits.shape().dim_size(0),
                hash_table_cell_splits.flat<uint32_t>().data(),
                hash_table_index.flat<uint32_t>().data());
    }

private:
    int texture_alignment;
};

#define REG_KB(type)                                                       \
    REGISTER_KERNEL_BUILDER(Name("Open3DBuildSpatialHashTable")            \
                                    .Device(DEVICE_GPU)                    \
                                    .TypeConstraint<type>("T")             \
                                    .HostMemory("radius")                  \
                                    .HostMemory("points_row_splits")       \
                                    .HostMemory("hash_table_splits")       \
                                    .HostMemory("hash_table_size_factor"), \
                            BuildSpatialHashTableOpKernelCUDA<type>);
REG_KB(float)
#undef REG_KB
