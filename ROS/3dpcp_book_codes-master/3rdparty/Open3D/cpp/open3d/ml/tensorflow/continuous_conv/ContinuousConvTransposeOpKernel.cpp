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

#include "ContinuousConvTransposeOpKernel.h"

#include "open3d/ml/impl/continuous_conv/ContinuousConvTranspose.h"

using namespace open3d;
using namespace open3d::ml::impl;
using namespace tensorflow;

template <class TFeat, class TOut, class TReal, class TIndex>
class ContinuousConvTransposeOpKernelCPU
    : public ContinuousConvTransposeOpKernel<TIndex> {
public:
    explicit ContinuousConvTransposeOpKernelCPU(
            OpKernelConstruction* construction)
        : ContinuousConvTransposeOpKernel<TIndex>(construction) {}

    void Kernel(tensorflow::OpKernelContext* context,
                const tensorflow::Tensor& filter,
                const tensorflow::Tensor& out_positions,
                const tensorflow::Tensor& out_importance,
                const tensorflow::Tensor& extents,
                const tensorflow::Tensor& offset,
                const tensorflow::Tensor& inp_positions,
                const tensorflow::Tensor& inp_features,
                const tensorflow::Tensor& inp_neighbors_importance_sum,
                const tensorflow::Tensor& inp_neighbors_row_splits,
                const tensorflow::Tensor& neighbors_index,
                const tensorflow::Tensor& neighbors_importance,
                const tensorflow::Tensor& neighbors_row_splits,
                const std::vector<int>& filter_dims,
                const bool individual_extents,
                const bool isotropic_extents,
                const bool point_importances,
                const bool has_neighbors_importances,
                tensorflow::Tensor& out_features) {
        CConvTransposeComputeFeaturesCPU<TFeat, TOut, TReal, TIndex>(
                out_features.flat<TOut>().data(), filter_dims,
                filter.flat<TFeat>().data(), out_positions.shape().dim_size(0),
                out_positions.flat<TReal>().data(),
                point_importances ? out_importance.flat<TFeat>().data()
                                  : nullptr,
                inp_positions.shape().dim_size(0),
                inp_positions.flat<TReal>().data(),
                inp_features.flat<TFeat>().data(),
                has_neighbors_importances
                        ? inp_neighbors_importance_sum.flat<TFeat>().data()
                        : nullptr,
                (int64_t*)inp_neighbors_row_splits.flat<int64>().data(),
                neighbors_index.shape().dim_size(0),
                (TIndex*)neighbors_index.flat<TIndex>().data(),
                has_neighbors_importances
                        ? neighbors_importance.flat<TFeat>().data()
                        : nullptr,
                (int64_t*)neighbors_row_splits.flat<int64>().data(),
                extents.flat<TReal>().data(), offset.flat<TReal>().data(),
                this->interpolation, this->coordinate_mapping,
                this->align_corners, individual_extents, isotropic_extents,
                this->normalize);
    }
};

#define REG_KB(feattype, outtype, realtype, indextype)                      \
    REGISTER_KERNEL_BUILDER(                                                \
            Name("Open3DContinuousConvTranspose")                           \
                    .Device(DEVICE_CPU)                                     \
                    .TypeConstraint<feattype>("TFeat")                      \
                    .TypeConstraint<outtype>("output_type")                 \
                    .TypeConstraint<realtype>("TReal")                      \
                    .TypeConstraint<indextype>("TIndex"),                   \
            ContinuousConvTransposeOpKernelCPU<feattype, outtype, realtype, \
                                               indextype>);
REG_KB(float, float, float, int32)
REG_KB(bfloat16, float, float, int32)
REG_KB(bfloat16, bfloat16, float, int32)
#undef REG_KB
