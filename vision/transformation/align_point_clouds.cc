#include "vision/transformation/align_point_clouds.h"

#include <Eigen/Dense>

// Use Besel-McKay registration to align point clouds to a model. We use SVD
// decomposition because it is better at finding the absolute minimum error for
// rotation as compared to a true ICP that Besl-McKay describe, which is only
// guaranteed to find a local minima.
namespace vision {
namespace transformation {
namespace {
double kEpsilon = 1e-4;
}  // namespace

void AlignPointClouds(const double left[][3],
                      const double right[][3],
                      int num_points,
                      double rotation[3][3],
                      double translation[3]) {
  // Compute centroids.
  Eigen::Vector3d left_vector[num_points];
  Eigen::RowVector3d right_vector[num_points];
  Eigen::Vector3d left_centroid(0.0, 0.0, 0.0);
  Eigen::RowVector3d right_centroid(0.0, 0.0, 0.0);
  for (int i = 0; i < num_points; i++) {
    left_vector[i] = Eigen::Vector3d(left[i][0], left[i][1], left[i][2]);
    right_vector[i] = Eigen::RowVector3d(right[i][0], right[i][1], right[i][2]);
    left_centroid += left_vector[i];
    right_centroid += right_vector[i];
  }

  left_centroid /= static_cast<double>(num_points);
  right_centroid /= static_cast<double>(num_points);

  // Calculate cross correlation matrix based on the points shifted about the
  // centroid.
  Eigen::Matrix3d cross_correlation = Eigen::Matrix3d::Zero();
  for (int i = 0; i < num_points; i++) {
    cross_correlation +=
        (left_vector[i] - left_centroid)*(right_vector[i] - right_centroid);
  }

  // Compute SVD decomposition of the cross correlation. This is excessive for 3
  // dimensions, but it is more stable than ICP.  TODO(cmsweeney): Evaluate the
  // performance more (SVD method runs in roughly 0.15ms on some tests
  // performed) to determine whether the closed form solution (see Horn's
  // quaternion method for analytic computation of rotation using quaternions)
  // is preferred.
  Eigen::JacobiSVD<Eigen::Matrix3d>
      svd(cross_correlation, Eigen::ComputeFullU | Eigen::ComputeFullV);
  Eigen::Map<Eigen::Matrix<double, 3, 3, Eigen::RowMajor> >
      rotation_mat((double *)(&rotation[0]));
  rotation_mat = svd.matrixV()*(svd.matrixU().transpose());

  // Rotation is solved for, but the optimal translation is the difference of
  // the right centroid and the rotated left centroid.
  Eigen::Vector3d rotated_left_centroid = rotation_mat*left_centroid;
  Eigen::Map<Eigen::RowVector3d> translation_vec(translation);
  translation_vec = right_centroid - rotated_left_centroid.transpose();
}

}  // namespace transformation
}  // namespace vision