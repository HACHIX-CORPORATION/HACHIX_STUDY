# 開発環境
conda create -n open3d python=3.8

# section_basics
1. cd section_basics
2. visualization
- python o3d_visualize_points.py ..\3rdparty\Open3D\examples\test_data\bathtub_0154.ply

3. downsampling
- python o3d_voxelize_points.py ..\3rdparty\Open3D\examples\test_data\fragment.ply 0.03
- python o3d_farthest_point_sampling.py ..\3rdparty\Open3D\examples\test_data\fragment.ply 1000