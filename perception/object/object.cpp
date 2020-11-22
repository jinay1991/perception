///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#include "perception/object/object.h"

#include "perception/common/logging/logging.h"

#include <opencv4/opencv2/calib3d/calib3d.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/matx.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>

namespace perception
{
namespace
{
/// @brief Minimum Detection Score required to consider Valid Object and report to ObjectList
constexpr float kMinObjectDetectionScore{0.50F};

/// @brief Provide Object Id (classification) based on Label Id (COCO Label Map)
///
/// @param label_id[in] Label Id (COCO Label Map)
///
/// @return Object Id (classification label)
constexpr ObjectId GetObjectId(const LabelId& label_id)
{
    ObjectId object_id{ObjectId::kInvalid};

    switch (label_id)
    {
        case LabelId::kPerson:
        {
            object_id = ObjectId::kPedestrian;
            break;
        }
        case LabelId::kBicycle:
        {
            object_id = ObjectId::kBicycle;
            break;
        }
        case LabelId::kCar:
        {
            object_id = ObjectId::kCar;
            break;
        }
        case LabelId::kMotorcycle:
        {
            object_id = ObjectId::kMotorBike;
            break;
        }
        case LabelId::kBus:
        case LabelId::kTruck:
        {
            object_id = ObjectId::kTruck;
            break;
        }
        case LabelId::kTrafficLight:
        {
            object_id = ObjectId::kTrafficLight;
            break;
        }
        case LabelId::kStopSign:
        {
            object_id = ObjectId::kTrafficSign_Stop;
            break;
        }
        case LabelId::kBird:
        case LabelId::kCat:
        case LabelId::kDog:
        case LabelId::kHorse:
        case LabelId::kSheep:
        case LabelId::kCow:
        case LabelId::kElephant:
        case LabelId::kBear:
        case LabelId::kZebra:
        case LabelId::kGiraffe:
        {
            object_id = ObjectId::kAnimal;
            break;
        }
        default:
        {
            object_id = ObjectId::kUnknown;
            break;
        }
    }

    return object_id;
}

/// @brief Provide Transformation Matrix based on the given rotational and translation matrices
///
/// @param rotational[in] Rotation Matrix [3x3]
/// @param translation[in] Translation Matrix [3x1]
///
/// @return Transformation matrix (4x4)
cv::Mat GetTransformation(const cv::Mat& rotational, const cv::Mat& translation)
{
    cv::Mat res{};
    cv::Rodrigues(rotational, res);

    // clang-format off
    const cv::Mat transformation{cv::Matx44d{res.at<double>(0, 0), res.at<double>(0, 1), res.at<double>(0, 2), translation.at<double>(0),
                                             res.at<double>(1, 0), res.at<double>(1, 1), res.at<double>(1, 2), translation.at<double>(1),
                                             res.at<double>(2, 0), res.at<double>(2, 1), res.at<double>(2, 2), translation.at<double>(2),
                                             0.0, 0.0, 0.0, 1.0}};
    // clang-format on
    return transformation;
}

/// @brief Transforms given 2D Point to 3D
///
/// @param point[in] 2D Point
/// @param rotational[in] Rotation Matrix [3x3]
/// @param translation[in] Translation Matrix [3x1]
///
/// @return Point in 3D Space
cv::Point3d TransformTo3D(const cv::Point2d& point, const cv::Mat& rotational, const cv::Mat& translation)
{
    const cv::Mat transformation = GetTransformation(rotational, translation);
    const cv::Mat homogeneous_point{cv::Matx41d{point.x, point.y, 1.0, 1.0}};
    const cv::Mat transformed_point = transformation * homogeneous_point;

    const cv::Point3d object_point_3d{
        transformed_point.at<double>(0), transformed_point.at<double>(1), transformed_point.at<double>(2)};
    return object_point_3d;
}

/// @brief Calculates Euclidean Distance from Origin (0, 0, 0) in 3D Space
///
/// @param position[in] Position (aka 3D Point)
///
/// @return Euclidean distance of given point from origin
units::length::meter_t GetEuclideanDistance(const Position& position)
{
    return units::math::sqrt(units::math::pow<2>(position.x) + units::math::pow<2>(position.y) +
                             units::math::pow<2>(position.z));
}

/// @brief Calculate Pose for the given rotational matrix
///
/// @ref   https://stackoverflow.com/questions/23009549/roll-pitch-yaw-calculation/23010193#23010193
///
/// @param rotational[in] Rotation Matrix [3x3]
///
/// @return Euler angles (pose) - Yaw, Pitch and Roll for the given rotation matrix
Pose GetObjectPose(const cv::Mat& rotational)
{
    cv::Mat res{};
    cv::Rodrigues(rotational, res);
    const auto pitch = std::atan2(-res.at<double>(2, 0),
                                  std::sqrt(std::pow(res.at<double>(0, 0), 2) + std::pow(res.at<double>(1, 0), 2)));
    const auto yaw = std::atan2(res.at<double>(1, 0) / std::cos(pitch), res.at<double>(0, 0) / std::cos(pitch));
    const auto roll = std::atan2(res.at<double>(2, 1) / std::cos(pitch), res.at<double>(2, 2) / std::cos(pitch));
    const Pose pose{units::angle::radian_t{yaw}, units::angle::radian_t{pitch}, units::angle::radian_t{roll}};
    return pose;
}

/// @brief Provide associated LaneId for given Position (aka 3D point)
/// @note For 3D Point, x axis pointing in the right side from the camera, y axis pointing down, and z axis pointing in
/// the direction camera is faced.
///
/// @param position[in] Position (aka 3D Point)
///
/// @return LaneId
constexpr LaneId GetLaneId(const Position& position)
{
    LaneId lane_id{LaneId::kEgo};
    if (position.y > (kMaxLaneWidth / 2))
    {
        lane_id = LaneId::kRight;
    }
    else if (position.y < -(kMaxLaneWidth / 2))
    {
        lane_id = LaneId::kLeft;
    }
    return lane_id;
}
}  // namespace

Object::Object()
    : inference_engine_params_{"external/ssd_mobilenet_v2_coco/saved_model",
                               "image_tensor",
                               {"detection_classes", "detection_scores", "detection_boxes", "num_detections"}},
      inference_engine_{},
      camera_message_{},
      ego_velocity_{},
      object_list_message_{}
{
}

void Object::Init()
{
    inference_engine_.SelectInferenceEngine(InferenceEngineType::kTensorFlow, inference_engine_params_);
    inference_engine_.Init();
}

void Object::Step()
{
    inference_engine_.Execute(camera_message_.undistorted_image);

    UpdateOutputs();
}

void Object::Shutdown()
{
    inference_engine_.Shutdown();
}

void Object::SetCameraMessage(const CameraMessage& camera_message)
{
    camera_message_ = camera_message;
}

void Object::SetEgoVelocity(const units::velocity::meters_per_second_t& ego_velocity)
{
    ego_velocity_ = ego_velocity;
}

const ObjectListMessage& Object::GetObjectListMessage() const
{
    return object_list_message_;
}

void Object::UpdateOutputs()
{
    const auto results = inference_engine_.GetResults();
    const cv::Mat detection_classes = results.at(0);
    const cv::Mat detection_scores = results.at(1);
    const cv::Mat detection_boxes = results.at(2);
    const cv::Mat num_detections = results.at(3);

    object_list_message_.number_of_valid_objects = 0;
    object_list_message_.time_point = camera_message_.time_point;
    object_list_message_.objects.fill(ObjectMessage{});

    for (auto idx = 0; !num_detections.empty() && idx < static_cast<std::int32_t>(num_detections.at<float>(0, 0));
         ++idx)
    {
        const auto score = detection_scores.at<float>(idx, 0);
        const auto label = static_cast<std::int32_t>(detection_classes.at<float>(idx, 0));
        const auto ymin = detection_boxes.at<float>(idx, 0);
        const auto xmin = detection_boxes.at<float>(idx, 1);
        const auto ymax = detection_boxes.at<float>(idx, 2);
        const auto xmax = detection_boxes.at<float>(idx, 3);

        const auto bounding_box = BoundingBox{xmin * static_cast<float>(camera_message_.image.cols),
                                              ymin * static_cast<float>(camera_message_.image.rows),
                                              (xmax - xmin) * static_cast<float>(camera_message_.image.cols),
                                              (ymax - ymin) * static_cast<float>(camera_message_.image.rows)};
        if (score > kMinObjectDetectionScore)
        {
            ++object_list_message_.number_of_valid_objects;
            object_list_message_.objects.at(idx) = GenerateObjectMessage(bounding_box, static_cast<LabelId>(label));
        }
    }

    LOG(INFO) << "Observed {" << object_list_message_.number_of_valid_objects << "} detected valid objects!";
    LOG(DEBUG) << object_list_message_;
}

ObjectMessage Object::GenerateObjectMessage(const BoundingBox& bounding_box, const LabelId& label_id)
{
    ObjectMessage object{};
    cv::Mat rotational{};
    cv::Mat translation{};
    UpdateSpatialMatrix(bounding_box, camera_message_.image.rows, camera_message_.image.cols, rotational, translation);
    const cv::Point2d bottom_center{(bounding_box.x + bounding_box.width) / 2.0, bounding_box.height};
    const cv::Point3d bottom_center_3d = TransformTo3D(bottom_center, rotational, translation);
    const Position position{units::length::millimeter_t{bottom_center_3d.x},
                            units::length::millimeter_t{bottom_center_3d.y},
                            units::length::millimeter_t{bottom_center_3d.z}};

    const auto distance = GetEuclideanDistance(position);
    object.distance = distance;

    // x axis pointing in the right side from the camera, y axis pointing down, and z axis pointing in the direction
    // camera is faced.
    object.longitudinal_distance = position.z;
    object.lateral_distance = position.x;

    object.bounding_box = bounding_box;
    object.id = GetObjectId(label_id);
    object.position = position;
    object.pose = GetObjectPose(rotational);
    object.time_to_collision = distance / ego_velocity_;
    object.lane_id = GetLaneId(position);

    return object;
}

void Object::UpdateSpatialMatrix(const BoundingBox& bounding_box,
                                 const std::int32_t rows,
                                 const std::int32_t cols,
                                 cv::Mat& rotational,
                                 cv::Mat& translation) const
{
    const std::array<cv::Point3d, 4U> camera_point_3d{
        cv::Point3d(0, 0, 1), cv::Point3d(cols, 0, 1), cv::Point3d(cols, rows, 1), cv::Point3d(0, rows, 1)};

    const std::array<cv::Point2d, 4U> object_points_2d{
        cv::Point2d(bounding_box.x, bounding_box.y),
        cv::Point2d(bounding_box.x + bounding_box.width, bounding_box.y),
        cv::Point2d(bounding_box.x + bounding_box.width, bounding_box.y + bounding_box.height),
        cv::Point2d(bounding_box.x, bounding_box.y + bounding_box.height)};

    // compute camera pose
    cv::solvePnP(camera_point_3d,
                 object_points_2d,
                 camera_message_.calibration_params.intrinsic,
                 camera_message_.calibration_params.extrinsic,
                 rotational,
                 translation);
}

}  // namespace perception
