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

#include "open3d/t/geometry/TriangleMesh.h"

#include <string>
#include <unordered_map>

#include "open3d/core/CUDAUtils.h"
#include "pybind/t/geometry/geometry.h"

namespace open3d {
namespace t {
namespace geometry {

void pybind_trianglemesh(py::module& m) {
    py::class_<TriangleMesh, PyGeometry<TriangleMesh>,
               std::shared_ptr<TriangleMesh>, Geometry, DrawableGeometry>
            triangle_mesh(m, "TriangleMesh",
                          R"(
A triangle mesh contains vertices and triangles. The triangle mesh class stores
the attribute data in key-value maps. There are two maps: the vertex attributes
map, and the triangle attribute map.

The attributes of the triangle mesh have different levels::

    import open3d as o3d

    device = o3d.core.Device("CPU:0")
    dtype_f = o3d.core.float32
    dtype_i = o3d.core.int32

    # Create an empty triangle mesh
    # Use mesh.vertex to access the vertices' attributes
    # Use mesh.triangle to access the triangles' attributes
    mesh = o3d.t.geometry.TriangleMesh(device)

    # Default attribute: vertex["positions"], triangle["indices"]
    # These attributes is created by default and is required by all triangle
    # meshes. The shape of both must be (N, 3). The device of "positions"
    # determines the device of the triangle mesh.
    mesh.vertex["positions"] = o3d.core.Tensor([[0, 0, 0],
                                                [0, 0, 1],
                                                [0, 1, 0],
                                                [0, 1, 1]], dtype_f, device)
    mesh.triangle["indices"] = o3d.core.Tensor([[0, 1, 2],
                                                [0, 2, 3]]], dtype_i, device)

    # Common attributes: vertex["colors"]  , vertex["normals"]
    #                    triangle["colors"], triangle["normals"]
    # Common attributes are used in built-in triangle mesh operations. The
    # spellings must be correct. For example, if "normal" is used instead of
    # "normals", some internal operations that expects "normals" will not work.
    # "normals" and "colors" must have shape (N, 3) and must be on the same
    # device as the triangle mesh.
    mesh.vertex["normals"] = o3c.core.Tensor([[0, 0, 1],
                                              [0, 1, 0],
                                              [1, 0, 0],
                                              [1, 1, 1]], dtype_f, device)
    mesh.vertex["colors"] = o3c.core.Tensor([[0.0, 0.0, 0.0],
                                             [0.1, 0.1, 0.1],
                                             [0.2, 0.2, 0.2],
                                             [0.3, 0.3, 0.3]], dtype_f, device)
    mesh.triangle["normals"] = o3c.core.Tensor(...)
    mesh.triangle["colors"] = o3c.core.Tensor(...)

    # User-defined attributes
    # You can also attach custom attributes. The value tensor must be on the
    # same device as the triangle mesh. The are no restrictions on the shape and
    # dtype, e.g.,
    pcd.vertex["labels"] = o3c.core.Tensor(...)
    pcd.triangle["features"] = o3c.core.Tensor(...)
)");

    // Constructors.
    triangle_mesh
            .def(py::init<const core::Device&>(),
                 "Construct an empty trianglemesh on the provided ``device`` "
                 "(default: 'CPU:0').",
                 "device"_a = core::Device("CPU:0"))
            .def(py::init<const core::Tensor&, const core::Tensor&>(),
                 "vertex_positions"_a, "triangle_indices"_a)
            .def("__repr__", &TriangleMesh::ToString);

    // Triangle mesh's attributes: vertices, vertex_colors, vertex_normals, etc.
    // def_property_readonly is sufficient, since the returned TensorMap can
    // be editable in Python. We don't want the TensorMap to be replaced
    // by another TensorMap in Python.
    triangle_mesh.def_property_readonly(
            "vertex",
            py::overload_cast<>(&TriangleMesh::GetVertexAttr, py::const_));
    triangle_mesh.def_property_readonly(
            "triangle",
            py::overload_cast<>(&TriangleMesh::GetTriangleAttr, py::const_));

    // Device transfers.
    triangle_mesh.def("to", &TriangleMesh::To,
                      "Transfer the triangle mesh to a specified device.",
                      "device"_a, "copy"_a = false);
    triangle_mesh.def("clone", &TriangleMesh::Clone,
                      "Returns copy of the triangle mesh on the same device.");

    triangle_mesh.def(
            "cpu",
            [](const TriangleMesh& triangle_mesh) {
                return triangle_mesh.To(core::Device("CPU:0"));
            },
            "Transfer the triangle mesh to CPU. If the triangle mesh "
            "is already on CPU, no copy will be performed.");
    triangle_mesh.def(
            "cuda",
            [](const TriangleMesh& triangle_mesh, int device_id) {
                return triangle_mesh.To(core::Device("CUDA", device_id));
            },
            "Transfer the triangle mesh to a CUDA device. If the triangle mesh "
            "is already on the specified CUDA device, no copy will be "
            "performed.",
            "device_id"_a = 0);

    // Triangle Mesh's specific functions.
    triangle_mesh.def("get_min_bound", &TriangleMesh::GetMinBound,
                      "Returns the min bound for point coordinates.");
    triangle_mesh.def("get_max_bound", &TriangleMesh::GetMaxBound,
                      "Returns the max bound for point coordinates.");
    triangle_mesh.def("get_center", &TriangleMesh::GetCenter,
                      "Returns the center for point coordinates.");
    triangle_mesh.def("transform", &TriangleMesh::Transform, "transformation"_a,
                      "Transforms the points and normals (if exist).");
    triangle_mesh.def("translate", &TriangleMesh::Translate, "translation"_a,
                      "relative"_a = true, "Translates points.");
    triangle_mesh.def("scale", &TriangleMesh::Scale, "scale"_a, "center"_a,
                      "Scale points.");
    triangle_mesh.def("rotate", &TriangleMesh::Rotate, "R"_a, "center"_a,
                      "Rotate points and normals (if exist).");

    triangle_mesh.def_static(
            "from_legacy", &TriangleMesh::FromLegacy, "mesh_legacy"_a,
            "vertex_dtype"_a = core::Float32, "triangle_dtype"_a = core::Int64,
            "device"_a = core::Device("CPU:0"),
            "Create a TriangleMesh from a legacy Open3D TriangleMesh.");
    triangle_mesh.def("to_legacy", &TriangleMesh::ToLegacy,
                      "Convert to a legacy Open3D TriangleMesh.");
}

}  // namespace geometry
}  // namespace t
}  // namespace open3d
