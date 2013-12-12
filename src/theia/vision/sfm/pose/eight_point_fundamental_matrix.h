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

#ifndef THEIA_VISION_SFM_POSE_EIGHT_POINT_FUNDAMENTAL_MATRIX_H_
#define THEIA_VISION_SFM_POSE_EIGHT_POINT_FUNDAMENTAL_MATRIX_H_

#include <Eigen/Core>
#include <vector>

namespace theia {

// Computes the Fundamental Matrix
// (http://en.wikipedia.org/wiki/Fundamental_matrix_(computer_vision) ) from 8
// or more image correspondences according to the normalized 8 point algorithm
// (Hartley and Zisserman alg 11.1 page 282). Image points are first normalized
// by a translation and scale, and the fundamental matrix is computed from the
// singular vector corresponding to the smallest singular vector of the stacked
// epipolar constraints. The estimated fundamental matrix is the computed
// fundamental matrix with the normalization transformation undone.
//
// Params:
//   image_1_points: homogeneous image points from one image (8 or more).
//   image_2_points: homogeneous image points from a second image (8 or more).
//   fundamental_matrix: the estimated fundamental matrix.
bool NormalizedEightPoint(const std::vector<Eigen::Vector3d>& image_1_points,
                          const std::vector<Eigen::Vector3d>& image_2_points,
                          Eigen::Matrix3d* fundamental_matrix);

// Same as above, but with a generic interface:
// Params:
//   num_points: the number of image correspondences used.
//   image_1_points: a 3xn array of homogeneous image points from one image (8
//     or more points).
//   image_2_points: a 3xn array of homogeneous image points from a second image
//     (8 or more points).
//   fundamental_matrix: the estimated fundamental matrix.
bool NormalizedEightPoint(const int num_points,
                          const double image_1_points[],
                          const double image_2_points[],
                          double fundamental_matrix[9]);

// Eight point algorithm for computing the fundamental matrix via the Gold
// Standard Algorithm (Alg 11.3 in Hartley and Zisserman). This minimizes the
// geometric error using Levenberg Marquardt with initialization from the
// Normalized Eight Point algorithm.
bool GoldStandardEightPoint(const std::vector<Eigen::Vector3d>& image_1_points,
                            const std::vector<Eigen::Vector3d>& image_2_points,
                            Eigen::Matrix3d* fundamental_matrix);

// Same as above, but with a generic interface.
bool GoldStandardEightPoint(const int num_points,
                            const double image_1_points[],
                            const double image_2_points[],
                            double fundamental_matrix[9]);

}  // namespace theia

#endif  // THEIA_VISION_SFM_POSE_EIGHT_POINT_FUNDAMENTAL_MATRIX_H_
