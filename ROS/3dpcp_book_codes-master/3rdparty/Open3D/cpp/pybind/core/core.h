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

#pragma once

#include "open3d/core/Tensor.h"
#include "pybind/open3d_pybind.h"

namespace open3d {
namespace core {

void pybind_core(py::module& m);
void pybind_cuda_utils(py::module& m);
void pybind_core_blob(py::module& m);
void pybind_core_dtype(py::module& m);
void pybind_core_device(py::module& m);
void pybind_core_size_vector(py::module& m);
void pybind_core_tensor(py::module& m);
void pybind_core_tensor_accessor(py::class_<Tensor>& t);
void pybind_core_tensor_function(py::module& m);
void pybind_core_linalg(py::module& m);
void pybind_core_kernel(py::module& m);
void pybind_core_hashmap(py::module& m);
void pybind_core_hashset(py::module& m);
void pybind_core_scalar(py::module& m);

}  // namespace core
}  // namespace open3d
