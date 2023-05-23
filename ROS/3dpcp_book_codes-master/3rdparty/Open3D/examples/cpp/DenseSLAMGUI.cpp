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

#include <atomic>
#include <sstream>
#include <thread>

#include "open3d/Open3D.h"

using namespace open3d;
using namespace open3d::visualization;

// Tanglo colorscheme (see https://en.wikipedia.org/wiki/Tango_Desktop_Project)
static const Eigen::Vector3d kTangoOrange(0.961, 0.475, 0.000);
static const Eigen::Vector3d kTangoSkyBlueDark(0.125, 0.290, 0.529);

//------------------------------------------------------------------------------
class PropertyPanel : public gui::VGrid {
    using Super = gui::VGrid;

public:
    PropertyPanel(int spacing, int left_margin)
        : gui::VGrid(2, spacing, gui::Margins(left_margin, 0, 0, 0)) {
        default_label_color_ =
                std::make_shared<gui::Label>("temp")->GetTextColor();
    }

    void AddBool(const std::string& name,
                 std::atomic<bool>* bool_addr,
                 bool default_val,
                 const std::string& tooltip = "") {
        auto cb = std::make_shared<gui::Checkbox>("");
        cb->SetChecked(default_val);
        *bool_addr = default_val;
        cb->SetOnChecked([bool_addr, this](bool is_checked) {
            *bool_addr = is_checked;
            this->NotifyChanged();
        });
        auto label = std::make_shared<gui::Label>(name.c_str());
        label->SetTooltip(tooltip.c_str());
        AddChild(label);
        AddChild(cb);
    }

    void AddFloatSlider(const std::string& name,
                        std::atomic<double>* num_addr,
                        double default_val,
                        double min_val,
                        double max_val,
                        const std::string& tooltip = "") {
        auto s = std::make_shared<gui::Slider>(gui::Slider::DOUBLE);
        s->SetLimits(min_val, max_val);
        s->SetValue(default_val);
        *num_addr = default_val;
        s->SetOnValueChanged([num_addr, this](double new_val) {
            *num_addr = new_val;
            this->NotifyChanged();
        });
        auto label = std::make_shared<gui::Label>(name.c_str());
        label->SetTooltip(tooltip.c_str());
        AddChild(label);
        AddChild(s);
    }

    void AddIntSlider(const std::string& name,
                      std::atomic<int>* num_addr,
                      int default_val,
                      int min_val,
                      int max_val,
                      const std::string& tooltip = "") {
        auto s = std::make_shared<gui::Slider>(gui::Slider::INT);
        s->SetLimits(min_val, max_val);
        s->SetValue(default_val);
        *num_addr = default_val;
        s->SetOnValueChanged([num_addr, this](int new_val) {
            *num_addr = new_val;
            this->NotifyChanged();
        });
        auto label = std::make_shared<gui::Label>(name.c_str());
        label->SetTooltip(tooltip.c_str());
        AddChild(label);
        AddChild(s);
    }

    void AddValues(const std::string& name,
                   std::atomic<int>* idx_addr,
                   int default_idx,
                   std::vector<std::string> values,
                   const std::string& tooltip = "") {
        auto combo = std::make_shared<gui::Combobox>();
        for (auto& v : values) {
            combo->AddItem(v.c_str());
        }
        combo->SetSelectedIndex(default_idx);
        *idx_addr = default_idx;
        combo->SetOnValueChanged(
                [idx_addr, this](const char* new_value, int new_idx) {
                    *idx_addr = new_idx;
                    this->NotifyChanged();
                });
        auto label = std::make_shared<gui::Label>(name.c_str());
        label->SetTooltip(tooltip.c_str());
        AddChild(label);
        AddChild(combo);
    }

    void SetEnabled(bool enable) override {
        Super::SetEnabled(enable);
        for (auto child : GetChildren()) {
            child->SetEnabled(enable);
            auto label = std::dynamic_pointer_cast<gui::Label>(child);
            if (label) {
                if (enable) {
                    label->SetTextColor(default_label_color_);
                } else {
                    label->SetTextColor(gui::Color(0.5f, 0.5f, 0.5f, 1.0f));
                }
            }
        }
    }

    void SetOnChanged(std::function<void()> f) { on_changed_ = f; }

private:
    gui::Color default_label_color_;
    std::function<void()> on_changed_;

    void NotifyChanged() {
        if (on_changed_) {
            on_changed_();
        }
    }
};

//------------------------------------------------------------------------------
class ReconstructionWindow : public gui::Window {
    using Super = gui::Window;

public:
    ReconstructionWindow(const std::string& dataset_path,
                         const std::string& intrinsic_path,
                         const std::string& device,
                         gui::FontId monospace)
        : gui::Window("Open3D - Reconstruction", 1280, 800),
          dataset_path_(dataset_path),
          intrinsic_path_(intrinsic_path),
          device_str_(device),
          is_running_(false),
          is_started_(false),
          monospace_(monospace) {
        ////////////////////////////////////////
        /// General layout
        auto& theme = GetTheme();
        int em = theme.font_size;
        int spacing = int(std::round(0.25f * float(em)));
        int left_margin = em;
        int vspacing = int(std::round(0.5f * float(em)));
        gui::Margins margins(int(std::round(0.5f * float(em))));
        panel_ = std::make_shared<gui::Vert>(spacing, margins);
        widget3d_ = std::make_shared<gui::SceneWidget>();
        fps_panel_ = std::make_shared<gui::Vert>(spacing, margins);

        AddChild(panel_);
        AddChild(widget3d_);
        AddChild(fps_panel_);

        ////////////////////////////////////////
        /// Property panels
        fixed_props_ = std::make_shared<PropertyPanel>(spacing, left_margin);
        fixed_props_->AddIntSlider("Depth scale", &prop_values_.depth_scale,
                                   1000, 1, 5000,
                                   "Scale factor applied to the depth values "
                                   "from the depth image.");
        fixed_props_->AddFloatSlider("Voxel size", &prop_values_.voxel_size,
                                     3.0 / 512, 0.004, 0.01,
                                     "Voxel size for the TSDF voxel grid.");
        fixed_props_->AddIntSlider(
                "Block count", &prop_values_.bucket_count, 40000, 10000, 100000,
                "Number of estimated voxel blocks for spatial "
                "hashmap. Will be adapted dynamically, but "
                "may trigger memory issue during rehashing for large scenes.");
        fixed_props_->AddIntSlider(
                "Estimated points", &prop_values_.pointcloud_size, 6000000,
                500000, 8000000,
                "Estimated number of points in the point cloud; used to speed "
                "extraction of points into the 3D scene.");

        adjustable_props_ =
                std::make_shared<PropertyPanel>(spacing, left_margin);
        adjustable_props_->AddIntSlider(
                "Update interval", &prop_values_.surface_interval, 50, 1, 500,
                "The number of iterations between updating the 3D display.");

        adjustable_props_->AddFloatSlider("Depth max", &prop_values_.depth_max,
                                          3.0, 1.0, 5.0,
                                          "Maximum depth before point is "
                                          "discarded as part of background.");
        adjustable_props_->AddFloatSlider(
                "Depth diff", &prop_values_.depth_diff, 0.07, 0.03, 0.5,
                "Depth truncation to reject outlier correspondences in "
                "tracking.");
        adjustable_props_->AddBool("Update surface",
                                   &prop_values_.update_surface, true,
                                   "Update surface every several frames, "
                                   "determined by the update interval.");
        adjustable_props_->AddBool(
                "Raycast color", &prop_values_.raycast_color, true,
                "Enable bilinear interpolated color image for visualization.");

        panel_->AddChild(std::make_shared<gui::Label>("Starting settings"));
        panel_->AddChild(fixed_props_);
        panel_->AddFixed(vspacing);
        panel_->AddChild(
                std::make_shared<gui::Label>("Reconstruction settings"));
        panel_->AddChild(adjustable_props_);

        auto b = std::make_shared<gui::ToggleSwitch>("Resume/Pause");
        b->SetOnClicked([b, this](bool is_on) {
            if (!this->is_started_) {
                gui::Application::GetInstance().PostToMainThread(
                        this, [this]() {
                            int max_points = prop_values_.pointcloud_size;
                            t::geometry::PointCloud pcd_placeholder(
                                    core::Tensor({max_points, 3},
                                                 core::Dtype::Float32,
                                                 core::Device("CPU:0")));
                            pcd_placeholder.SetPointColors(core::Tensor(
                                    {max_points, 3}, core::Dtype::Float32,
                                    core::Device("CPU:0")));

                            auto mat = rendering::MaterialRecord();
                            mat.shader = "defaultUnlit";
                            mat.sRGB_vertex_color = true;
                            this->widget3d_->GetScene()
                                    ->GetScene()
                                    ->AddGeometry("points", pcd_placeholder,
                                                  mat);

                            this->trajectory_ = std::make_shared<
                                    camera::PinholeCameraTrajectory>();

                            float voxel_size = prop_values_.voxel_size;
                            // The SDF truncation distance is empirically set to
                            // 6 * voxel_size. Further SDF measurements can be
                            // regarded as outliers and truncated for a smooth
                            // result.
                            // The volumetric hash map maps 3D coordinates to
                            // 16^3 voxel blocks, to ensure a globally sparse
                            // locally dense data structure. This captures the
                            // data distribution while maintaining a good memory
                            // access pattern.
                            this->model_ =
                                    std::make_shared<t::pipelines::slam::Model>(
                                            voxel_size, 16,
                                            prop_values_.bucket_count,
                                            core::Tensor::Eye(
                                                    4, core::Dtype::Float64,
                                                    core::Device("CPU:0")),
                                            core::Device(device_str_));
                            this->is_started_ = true;
                        });
            }
            this->is_running_ = !(this->is_running_);
            this->adjustable_props_->SetEnabled(true);
        });
        panel_->AddChild(b);
        panel_->AddFixed(vspacing);

        panel_->AddStretch();

        ////////////////////////////////////////
        /// Tabs
        gui::Margins tab_margins(0, int(std::round(0.5f * float(em))), 0, 0);
        auto tabs = std::make_shared<gui::TabControl>();
        panel_->AddChild(tabs);
        auto tab1 = std::make_shared<gui::Vert>(0, tab_margins);
        input_color_image_ = std::make_shared<gui::ImageWidget>();
        input_depth_image_ = std::make_shared<gui::ImageWidget>();
        tab1->AddChild(input_color_image_);
        tab1->AddFixed(vspacing);
        tab1->AddChild(input_depth_image_);
        tabs->AddTab("Input images", tab1);

        auto tab2 = std::make_shared<gui::Vert>(0, tab_margins);
        raycast_color_image_ = std::make_shared<gui::ImageWidget>();
        raycast_depth_image_ = std::make_shared<gui::ImageWidget>();

        tab2->AddChild(raycast_color_image_);
        tab2->AddFixed(vspacing);
        tab2->AddChild(raycast_depth_image_);
        tabs->AddTab("Raycast images", tab2);

        auto tab3 = std::make_shared<gui::Vert>(0, tab_margins);
        output_info_ = std::make_shared<gui::Label>("");
        output_info_->SetFontId(monospace_);
        tab3->AddChild(output_info_);
        tabs->AddTab("Info", tab3);

        widget3d_->SetScene(
                std::make_shared<rendering::Open3DScene>(GetRenderer()));

        output_fps_ = std::make_shared<gui::Label>("FPS: 0.0");
        fps_panel_->AddChild(output_fps_);

        is_done_ = false;
        SetOnClose([this]() {
            is_done_ = true;

            if (is_started_) {
                utility::LogInfo("Writing reconstruction to scene.ply...");
                auto pcd = model_->ExtractPointCloud(
                        prop_values_.pointcloud_size, 3.0);
                auto pcd_legacy =
                        std::make_shared<open3d::geometry::PointCloud>(
                                pcd.ToLegacy());
                io::WritePointCloud("scene.ply", *pcd_legacy);

                utility::LogInfo("Writing trajectory to trajectory.log...");
                io::WritePinholeCameraTrajectory("trajectory.log",
                                                 *trajectory_);
            }
            return true;  // false would cancel the close
        });
        update_thread_ = std::thread([this]() { this->UpdateMain(); });
    }

    ~ReconstructionWindow() { update_thread_.join(); }

    void Layout(const gui::LayoutContext& context) override {
        int em = context.theme.font_size;
        int panel_width = 20 * em;
        // The usable part of the window may not be the full size if there
        // is a menu.
        auto content_rect = GetContentRect();
        panel_->SetFrame(gui::Rect(content_rect.x, content_rect.y, panel_width,
                                   content_rect.height));
        int x = panel_->GetFrame().GetRight();
        widget3d_->SetFrame(gui::Rect(x, content_rect.y,
                                      content_rect.GetRight() - x,
                                      content_rect.height));

        int fps_panel_width = 7 * em;
        int fps_panel_height = 2 * em;
        fps_panel_->SetFrame(
                gui::Rect(content_rect.GetRight() - fps_panel_width,
                          content_rect.y, fps_panel_width, fps_panel_height));

        // Now that all the children are sized correctly, we can super to
        // layout all their children.
        Super::Layout(context);
    }

    void SetInfo(const std::string& output) {
        output_info_->SetText(output.c_str());
    }
    void SetFPS(const std::string& output) {
        output_fps_->SetText(output.c_str());
    }

protected:
    std::string dataset_path_;
    std::string intrinsic_path_;
    std::string device_str_;

    // General logic
    std::atomic<bool> is_running_;
    std::atomic<bool> is_started_;
    std::atomic<bool> is_done_;

    // Panels and controls
    gui::FontId monospace_;
    std::shared_ptr<gui::Vert> panel_;
    std::shared_ptr<gui::Label> output_info_;
    std::shared_ptr<PropertyPanel> fixed_props_;
    std::shared_ptr<PropertyPanel> adjustable_props_;

    std::shared_ptr<gui::SceneWidget> widget3d_;

    std::shared_ptr<gui::Vert> fps_panel_;
    std::shared_ptr<gui::Label> output_fps_;

    // Images
    std::shared_ptr<gui::ImageWidget> input_color_image_;
    std::shared_ptr<gui::ImageWidget> input_depth_image_;
    std::shared_ptr<gui::ImageWidget> raycast_color_image_;
    std::shared_ptr<gui::ImageWidget> raycast_depth_image_;

    struct {
        std::atomic<int> surface_interval;
        std::atomic<int> pointcloud_size;
        std::atomic<int> depth_scale;
        std::atomic<int> bucket_count;
        std::atomic<double> voxel_size;
        std::atomic<double> depth_max;
        std::atomic<double> depth_diff;
        std::atomic<bool> raycast_color;
        std::atomic<bool> update_surface;
    } prop_values_;

    struct {
        std::mutex lock;
        t::geometry::PointCloud pcd;
    } surface_;
    std::atomic<bool> is_scene_updated_;

    std::shared_ptr<t::pipelines::slam::Model> model_;
    std::shared_ptr<camera::PinholeCameraTrajectory> trajectory_;
    std::thread update_thread_;

protected:
    std::pair<std::vector<std::string>, std::vector<std::string>>
    LoadFilenames() {
        std::vector<std::string> rgb_candidates{"color", "image", "rgb"};
        std::vector<std::string> rgb_files;

        // Load rgb
        for (auto rgb_candidate : rgb_candidates) {
            const std::string rgb_dir = dataset_path_ + "/" + rgb_candidate;
            utility::filesystem::ListFilesInDirectoryWithExtension(
                    rgb_dir, "jpg", rgb_files);
            if (rgb_files.size() != 0) break;
            utility::filesystem::ListFilesInDirectoryWithExtension(
                    rgb_dir, "png", rgb_files);
            if (rgb_files.size() != 0) break;
        }
        if (rgb_files.size() == 0) {
            utility::LogError(
                    "RGB images not found! Please ensure a folder named color, "
                    "image, or rgb is in {}",
                    dataset_path_);
        }

        const std::string depth_dir = dataset_path_ + "/depth";
        std::vector<std::string> depth_files;
        utility::filesystem::ListFilesInDirectoryWithExtension(depth_dir, "png",
                                                               depth_files);
        if (depth_files.size() == 0) {
            utility::LogError(
                    "Depth images not found! Please ensure a folder named "
                    "depth is in {}",
                    dataset_path_);
        }

        if (depth_files.size() != rgb_files.size()) {
            utility::LogError(
                    "Number of depth images ({}) and color image ({}) "
                    "mismatch!",
                    dataset_path_);
        }

        std::sort(rgb_files.begin(), rgb_files.end());
        std::sort(depth_files.begin(), depth_files.end());
        return std::make_pair(rgb_files, depth_files);
    }

    std::pair<core::Tensor, camera::PinholeCameraIntrinsic> LoadIntrinsics() {
        // Default
        camera::PinholeCameraIntrinsic intrinsic =
                camera::PinholeCameraIntrinsic(
                        camera::PinholeCameraIntrinsicParameters::
                                PrimeSenseDefault);
        if (intrinsic_path_.empty()) {
            utility::LogInfo("Using Primesense default intrinsics.");
        } else if (!io::ReadIJsonConvertible(intrinsic_path_, intrinsic)) {
            utility::LogWarning(
                    "Failed to load {}, using Primesense default intrinsics.",
                    intrinsic_path_);
        } else {
            utility::LogInfo("Loaded intrinsics from {}.", intrinsic_path_);
        }
        auto focal_length = intrinsic.GetFocalLength();
        auto principal_point = intrinsic.GetPrincipalPoint();
        core::Tensor intrinsic_t = core::Tensor::Init<double>(
                {{focal_length.first, 0, principal_point.first},
                 {0, focal_length.second, principal_point.second},
                 {0, 0, 1}});

        camera::PinholeCameraIntrinsic intrinsic_legacy(
                -1, -1, focal_length.first, focal_length.second,
                principal_point.first, principal_point.second);
        return std::make_pair(intrinsic_t, intrinsic_legacy);
    }

    // Note that we cannot update the GUI on this thread, we must post to
    // the main thread!
    void UpdateMain() {
        // Load files
        std::vector<std::string> rgb_files, depth_files;
        std::tie(rgb_files, depth_files) = LoadFilenames();

        // Load intrinsics (if provided)
        core::Tensor intrinsic_t;
        camera::PinholeCameraIntrinsic intrinsic_legacy;
        std::tie(intrinsic_t, intrinsic_legacy) = LoadIntrinsics();
        camera::PinholeCameraParameters traj_param;
        traj_param.intrinsic_ = intrinsic_legacy;

        // Only set at initialization
        float depth_scale = prop_values_.depth_scale;
        core::Tensor T_frame_to_model = core::Tensor::Eye(
                4, core::Dtype::Float64, core::Device("CPU:0"));
        core::Device device(device_str_);

        t::geometry::Image ref_depth =
                *t::io::CreateImageFromFile(depth_files[0]);
        t::geometry::Image ref_color =
                *t::io::CreateImageFromFile(rgb_files[0]);

        t::pipelines::slam::Frame input_frame(
                ref_depth.GetRows(), ref_depth.GetCols(), intrinsic_t, device);
        t::pipelines::slam::Frame raycast_frame(
                ref_depth.GetRows(), ref_depth.GetCols(), intrinsic_t, device);

        // Odometry
        auto traj = std::make_shared<geometry::LineSet>();
        auto frustum = std::make_shared<geometry::LineSet>();
        auto color = std::make_shared<geometry::Image>();
        auto depth_colored = std::make_shared<geometry::Image>();

        auto raycast_color = std::make_shared<geometry::Image>();
        auto raycast_depth_colored = std::make_shared<geometry::Image>();

        is_scene_updated_ = false;

        color = std::make_shared<open3d::geometry::Image>(ref_color.ToLegacy());
        depth_colored = std::make_shared<open3d::geometry::Image>(
                ref_depth
                        .ColorizeDepth(depth_scale, 0.3, prop_values_.depth_max)
                        .ToLegacy());

        raycast_color = std::make_shared<geometry::Image>(
                t::geometry::Image(
                        core::Tensor::Zeros(
                                {ref_depth.GetRows(), ref_depth.GetCols(), 3},
                                core::Dtype::UInt8, core::Device("CPU:0")))
                        .ToLegacy());
        raycast_depth_colored = std::make_shared<geometry::Image>(
                t::geometry::Image(
                        core::Tensor::Zeros(
                                {ref_depth.GetRows(), ref_depth.GetCols(), 3},
                                core::Dtype::UInt8, core::Device("CPU:0")))
                        .ToLegacy());

        // Add placeholder in case color raycast is disabled in the beginning.
        raycast_frame.SetData(
                "color", core::Tensor::Zeros(
                                 {ref_depth.GetRows(), ref_depth.GetCols(), 3},
                                 core::Dtype::UInt8, core::Device("CPU:0")));

        // Render once to refresh
        gui::Application::GetInstance().PostToMainThread(
                this, [this, color, depth_colored, raycast_color,
                       raycast_depth_colored]() {
                    this->input_color_image_->UpdateImage(color);
                    this->input_depth_image_->UpdateImage(depth_colored);
                    this->raycast_color_image_->UpdateImage(raycast_color);
                    this->raycast_depth_image_->UpdateImage(
                            raycast_depth_colored);
                    this->SetNeedsLayout();  // size of image changed

                    geometry::AxisAlignedBoundingBox bbox(
                            Eigen::Vector3d(-5, -5, -5),
                            Eigen::Vector3d(5, 5, 5));
                    auto center = bbox.GetCenter().cast<float>();
                    this->widget3d_->SetupCamera(60, bbox, center);
                    this->widget3d_->LookAt(center,
                                            center - Eigen::Vector3f{0, 1, 3},
                                            {0.0f, -1.0f, 0.0f});
                });

        Eigen::IOFormat CleanFmt(Eigen::StreamPrecision, 0, ", ", "\n", "[",
                                 "]");

        const int fps_interval_len = 30;
        double time_interval = 0;
        size_t idx = 0;

        utility::Timer timer;
        timer.Start();
        while (!is_done_) {
            float depth_scale = prop_values_.depth_scale;

            if (!is_started_ || !is_running_) {
                // If we aren't running, sleep a little bit so that we don't
                // use 100% of the CPU just checking if we need to run.
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }

            // Input
            t::geometry::Image input_depth =
                    *t::io::CreateImageFromFile(depth_files[idx]);
            t::geometry::Image input_color =
                    *t::io::CreateImageFromFile(rgb_files[idx]);
            input_frame.SetDataFromImage("depth", input_depth);
            input_frame.SetDataFromImage("color", input_color);

            bool tracking_success = true;
            if (idx > 0) {
                auto result = model_->TrackFrameToModel(
                        input_frame, raycast_frame, depth_scale,
                        prop_values_.depth_max, prop_values_.depth_diff);

                core::Tensor translation =
                        result.transformation_.Slice(0, 0, 3).Slice(1, 3, 4);
                double translation_norm = std::sqrt(
                        (translation * translation).Sum({0, 1}).Item<double>());
                if (result.fitness_ >= 0.1 && translation_norm < 0.15) {
                    T_frame_to_model =
                            T_frame_to_model.Matmul(result.transformation_);
                } else {  // Don't update
                    tracking_success = false;
                    utility::LogWarning(
                            "Tracking failed for frame {}, fitness: {:.3f}, "
                            "translation: {:.3f}. Using previous frame's "
                            "pose.",
                            idx, result.fitness_, translation_norm);
                }
            }

            // Integrate
            model_->UpdateFramePose(idx, T_frame_to_model);
            if (tracking_success) {
                model_->Integrate(input_frame, depth_scale,
                                  prop_values_.depth_max);
            }
            model_->SynthesizeModelFrame(raycast_frame, depth_scale, 0.1,
                                         prop_values_.depth_max,
                                         prop_values_.raycast_color);

            auto K_eigen = open3d::core::eigen_converter::TensorToEigenMatrixXd(
                    intrinsic_t);
            auto T_eigen = open3d::core::eigen_converter::TensorToEigenMatrixXd(
                    T_frame_to_model);
            traj_param.extrinsic_ = T_eigen;
            trajectory_->parameters_.push_back(traj_param);

            std::stringstream info, fps;
            info.setf(std::ios::fixed, std::ios::floatfield);
            info.precision(4);
            info << fmt::format("Frame {}/{}\n\n", idx, rgb_files.size());

            info << "Transformation:\n";
            info << T_eigen.format(CleanFmt) << "\n\n";

            info << fmt::format("Active voxel blocks: {}/{}\n",
                                model_->GetHashMap().Size(),
                                model_->GetHashMap().GetCapacity());
            {
                std::lock_guard<std::mutex> locker(surface_.lock);
                int64_t len =
                        surface_.pcd.HasPointPositions()
                                ? surface_.pcd.GetPointPositions().GetLength()
                                : 0;
                info << fmt::format("Surface points: {}/{}\n", len,
                                    prop_values_.pointcloud_size)
                     << "\n";
            }

            if (idx % fps_interval_len == 0) {
                timer.Stop();
                time_interval = timer.GetDuration();
                timer.Start();
            }
            std::string fps_str =
                    fmt::format("FPS: {:.3f}\n",
                                1000.0 / (time_interval / fps_interval_len));
            info << fps_str;
            fps << fps_str;

            traj->points_.push_back(T_eigen.block<3, 1>(0, 3));
            if (traj->points_.size() > 1) {
                int n = traj->points_.size();
                traj->lines_.push_back({n - 1, n - 2});
                traj->colors_.push_back(kTangoSkyBlueDark);
            }

            frustum = open3d::geometry::LineSet::CreateCameraVisualization(
                    color->width_, color->height_, K_eigen, T_eigen.inverse(),
                    0.2);
            frustum->PaintUniformColor(kTangoOrange);

            // TODO: update support for timages-image conversion
            color = std::make_shared<open3d::geometry::Image>(
                    input_frame.GetDataAsImage("color").ToLegacy());
            depth_colored = std::make_shared<open3d::geometry::Image>(
                    input_frame.GetDataAsImage("depth")
                            .ColorizeDepth(depth_scale, 0.3,
                                           prop_values_.depth_max)
                            .ToLegacy());

            if (prop_values_.raycast_color) {
                raycast_color = std::make_shared<open3d::geometry::Image>(
                        raycast_frame.GetDataAsImage("color")
                                .To(core::Dtype::UInt8, false, 255.0f)
                                .ToLegacy());
            }

            raycast_depth_colored = std::make_shared<open3d::geometry::Image>(
                    raycast_frame.GetDataAsImage("depth")
                            .ColorizeDepth(depth_scale, 0.3,
                                           prop_values_.depth_max)
                            .ToLegacy());

            // Extract surface on demand (do before we increment idx, so that
            // we see something immediately, on interation 0)
            if ((prop_values_.update_surface &&
                 idx % static_cast<int>(prop_values_.surface_interval) == 0) ||
                idx == depth_files.size() - 1) {
                std::lock_guard<std::mutex> locker(surface_.lock);
                surface_.pcd =
                        model_->ExtractPointCloud(prop_values_.pointcloud_size,
                                                  std::min<float>(idx, 3.0f))
                                .To(core::Device("CPU:0"));
                is_scene_updated_ = true;
            }

            gui::Application::GetInstance().PostToMainThread(
                    this, [this, color, depth_colored, raycast_color,
                           raycast_depth_colored, traj, frustum,
                           info = info.str(), fps = fps.str()]() {
                        // Disable depth_scale and pcd buffer size change
                        this->fixed_props_->SetEnabled(false);

                        this->raycast_color_image_->SetVisible(
                                this->prop_values_.raycast_color);

                        this->SetInfo(info);
                        this->SetFPS(fps);
                        this->input_color_image_->UpdateImage(color);
                        this->input_depth_image_->UpdateImage(depth_colored);

                        if (prop_values_.raycast_color) {
                            this->raycast_color_image_->UpdateImage(
                                    raycast_color);
                        }
                        this->raycast_depth_image_->UpdateImage(
                                raycast_depth_colored);

                        this->widget3d_->GetScene()->RemoveGeometry("frustum");
                        auto mat = rendering::MaterialRecord();
                        mat.shader = "unlitLine";
                        mat.line_width = 5.0f;
                        this->widget3d_->GetScene()->AddGeometry(
                                "frustum", frustum.get(), mat);

                        if (traj->points_.size() > 1) {
                            // 1) Add geometry once w/ max size
                            // 2) Update geometry
                            // TPointCloud
                            this->widget3d_->GetScene()->RemoveGeometry(
                                    "trajectory");
                            auto mat = rendering::MaterialRecord();
                            mat.shader = "unlitLine";
                            mat.line_width = 5.0f;
                            this->widget3d_->GetScene()->AddGeometry(
                                    "trajectory", traj.get(), mat);
                        }

                        if (is_scene_updated_) {
                            using namespace rendering;
                            std::lock_guard<std::mutex> locker(surface_.lock);
                            if (surface_.pcd.HasPointPositions() &&
                                surface_.pcd.HasPointColors()) {
                                auto* scene =
                                        this->widget3d_->GetScene()->GetScene();

                                scene->UpdateGeometry(
                                        "points", surface_.pcd,
                                        Scene::kUpdatePointsFlag |
                                                Scene::kUpdateColorsFlag);
                            }
                            is_scene_updated_ = false;
                        }
                    });

            // Note that the user might have closed the window, in which case we
            // want to maintain a value of true.
            idx++;
            is_done_ = is_done_ | (idx >= depth_files.size());
        }
    }
};

//------------------------------------------------------------------------------
void PrintHelp() {
    using namespace open3d;

    PrintOpen3DVersion();
    // clang-format off
    utility::LogInfo("Usage:");
    utility::LogInfo("    > DenseSLAMGUI [dataset_path]");
    utility::LogInfo("      Given a sequence of RGBD images, reconstruct point cloud from color and depth images");
    utility::LogInfo("");
    utility::LogInfo("Basic options:");
    utility::LogInfo("    --voxel_size [=0.0058 (m)]");
    utility::LogInfo("    --intrinsic_path [camera_intrinsic.json]");
    utility::LogInfo("    --device [CUDA:0]");
    // clang-format on
    utility::LogInfo("");
}

int main(int argc, char* argv[]) {
    using namespace open3d;

    if (argc < 2 ||
        utility::ProgramOptionExistsAny(argc, argv, {"-h", "--help"})) {
        PrintHelp();
        return 1;
    }

    std::string dataset_path = argv[1];
    if (!utility::filesystem::DirectoryExists(dataset_path)) {
        utility::LogWarning(
                "Expected an existing directory, but {} does not exist.",
                dataset_path);
        return -1;
    }

    std::string intrinsic_path = utility::GetProgramOptionAsString(
            argc, argv, "--intrinsics_path", "");

    std::string device_code =
            utility::GetProgramOptionAsString(argc, argv, "--device", "CUDA:0");
    if (device_code != "CPU:0" && device_code != "CUDA:0") {
        utility::LogWarning(
                "Unrecognized device {}. Expecting CPU:0 or CUDA:0.",
                device_code);
        return -1;
    }
    utility::LogInfo("Using device {}.", device_code);

    auto& app = gui::Application::GetInstance();
    app.Initialize(argc, const_cast<const char**>(argv));
    auto mono =
            app.AddFont(gui::FontDescription(gui::FontDescription::MONOSPACE));
    app.AddWindow(std::make_shared<ReconstructionWindow>(
            dataset_path, intrinsic_path, device_code, mono));
    app.Run();
}
