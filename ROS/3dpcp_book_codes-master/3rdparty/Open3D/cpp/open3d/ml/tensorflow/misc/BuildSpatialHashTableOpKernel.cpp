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

#include "BuildSpatialHashTableOpKernel.h"

#include "open3d/core/nns/FixedRadiusSearchImpl.h"

using namespace tensorflow;

template <class T>
class BuildSpatialHashTableOpKernelCPU : public BuildSpatialHashTableOpKernel {
public:
    explicit BuildSpatialHashTableOpKernelCPU(
            OpKernelConstruction* construction)
        : BuildSpatialHashTableOpKernel(construction) {}

    void Kernel(tensorflow::OpKernelContext* context,
                const tensorflow::Tensor& points,
                const tensorflow::Tensor& radius,
                const tensorflow::Tensor& points_row_splits,
                const std::vector<uint32_t>& hash_table_splits,
                tensorflow::Tensor& hash_table_index,
                tensorflow::Tensor& hash_table_cell_splits) {
        open3d::core::nns::impl::BuildSpatialHashTableCPU(
                points.shape().dim_size(0), points.flat<T>().data(),
                radius.scalar<T>()(), points_row_splits.shape().dim_size(0),
                (int64_t*)points_row_splits.flat<int64>().data(),
                hash_table_splits.data(),
                hash_table_cell_splits.shape().dim_size(0),
                hash_table_cell_splits.flat<uint32_t>().data(),
                hash_table_index.flat<uint32_t>().data());
    }
};

#define REG_KB(type)                                            \
    REGISTER_KERNEL_BUILDER(Name("Open3DBuildSpatialHashTable") \
                                    .Device(DEVICE_CPU)         \
                                    .TypeConstraint<type>("T"), \
                            BuildSpatialHashTableOpKernelCPU<type>);
REG_KB(float)
REG_KB(double)
#undef REG_KB
