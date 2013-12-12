// Copyright (C) 2013 The Regents of the University of California (Regents).
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//
//     * Neither the name of The Regents or University of California nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Please contact the author of this library if you have any questions.
// Author: Chris Sweeney (cmsweeney@cs.ucsb.edu)

#include <Eigen/Core>
#include <Eigen/SVD>
#include <Eigen/Eigenvalues>
#include <glog/logging.h>
#include <vector>

#include "theia/vision/sfm/triangulation/triangulation.h"

namespace theia {
using Eigen::MatrixXd;
using Eigen::Matrix4d;
using Eigen::Vector3d;
using Eigen::Vector4d;

// Triangulates 2 posed views
Vector4d Triangulate(const ProjectionMatrix& pose_left,
                     const ProjectionMatrix& pose_right,
                     const Vector3d& point_left, const Vector3d& point_right) {
  Matrix4d design_matrix;
  design_matrix.row(0) =
      (point_left[0] / point_left[2]) * pose_left.row(2) - pose_left.row(0);
  design_matrix.row(1) =
      (point_left[1] / point_left[2]) * pose_left.row(2) - pose_left.row(1);
  design_matrix.row(2) =
      (point_right[0] / point_right[2]) * pose_right.row(2) - pose_right.row(0);
  design_matrix.row(3) =
      (point_right[1] / point_right[2]) * pose_right.row(2) - pose_right.row(1);

  // Extract nullspace.
  return design_matrix.jacobiSvd(Eigen::ComputeFullV).matrixV().rightCols<1>();
}

// Triangulates N views by computing SVD that minimizes the error.
Vector4d TriangulateNViewSVD(const std::vector<ProjectionMatrix>& poses,
                             const std::vector<Vector3d>& points) {
  CHECK_EQ(poses.size(), points.size());

  MatrixXd design_matrix(3 * points.size(), 4 + points.size());

  for (int i = 0; i < points.size(); i++) {
    design_matrix.block<3, 4>(3 * i, 0) = -poses[i].matrix();
    design_matrix.block<3, 1>(3 * i, 4 + i) = (points[i] / points[i].z());
  }

  // Computing SVD on A'A is more efficient and gives the same null-space.
  return (design_matrix.transpose() * design_matrix)
      .jacobiSvd(Eigen::ComputeFullV).matrixV().rightCols<1>().head(4);
}

Vector4d TriangulateNView(const std::vector<ProjectionMatrix>& poses,
                          const std::vector<Vector3d>& points) {
  CHECK_EQ(poses.size(), points.size());

  Matrix4d design_matrix = Matrix4d::Zero();
  for (int i = 0; i < points.size(); i++) {
    const Eigen::Matrix<double, 3, 4> cost_term =
        poses[i].matrix() -
        points[i] * points[i].transpose() * poses[i].matrix();
    design_matrix = design_matrix + cost_term.transpose() * cost_term;
  }

  Eigen::SelfAdjointEigenSolver<Matrix4d> eigen_solver(design_matrix);
  return eigen_solver.eigenvectors().col(0);
}

}  // namespace theia