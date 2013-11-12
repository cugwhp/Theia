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

#ifndef THEIA_IMAGE_DESCRIPTOR_DESCRIPTOR_H_
#define THEIA_IMAGE_DESCRIPTOR_DESCRIPTOR_H_

#include <glog/logging.h>
#include <array>
#include <algorithm>

#include "theia/image/keypoint_detector/keypoint.h"
#include "theia/util/util.h"

namespace theia {
enum DescriptorType {
  INVALID = -1,
  OTHER = 0,
  PATCH,
  SIFT,
  FREAK,
  BRISK
};

// The general descriptor interface class. This allows us to have derived
// classes that can be chosen at runtime with relatively simple memory
// management. Most new descriptors should derive from either the
// FloatDescriptor or BinaryDescriptor class. Those classes have been
// specifically optimized for the descriptors of various data types (float, int,
// binary, etc.).
const int kTheiaInvalidDescriptorVar = -9999;

class Descriptor {
 public:
  Descriptor(std::size_t dimensions, DescriptorType type)
      : dimensions_(dimensions),
        descriptor_type_(type),
        x_(kTheiaInvalidDescriptorVar),
        y_(kTheiaInvalidDescriptorVar),
        strength_(kTheiaInvalidDescriptorVar),
        scale_(kTheiaInvalidDescriptorVar),
        orientation_(kTheiaInvalidDescriptorVar) {}

  virtual ~Descriptor() {}

  virtual inline void SetKeypoint(const Keypoint& keypoint) {
    x_ = keypoint.x();
    y_ = keypoint.y();
    strength_ = keypoint.strength();
    scale_ = keypoint.scale();
    orientation_ = keypoint.orientation();
  }

  // Dimensionality of the descriptor.
  inline std::size_t Dimensions() const { return dimensions_; }

  // Pointer to the data. This is admittedly an odd paradigm for accessing
  // data. FloatDescriptor classes will implement the FloatData methods and
  // BinaryDescriptor classes will implement the CharData methods. Accessing the
  // wrong type of data (e.g. FloatData from a BinaryDescriptor) will result in
  // a failure.
  virtual inline float* FloatData() { LOG(FATAL) << "Can't get float data!"; }
  virtual inline const float* FloatData() const {
    LOG(FATAL) << "Can't get float data!";
  }
  virtual inline uchar* CharData() { LOG(FATAL) << "Can't get float data!"; }
  virtual inline const uchar* CharData() const {
    LOG(FATAL) << "Can't get float data!";
  }

  // Descriptor type.
  inline DescriptorType descriptor_type() const { return descriptor_type_; }
  inline void set_descriptor_type(DescriptorType type) {
    descriptor_type_ = type;
  }

  // x location within image.
  inline double x() const { return x_; }
  inline void set_x(double x) { x_ = x; }

  // y location within image.
  inline double y() const { return y_; }
  inline void set_y(double y) { y_ = y; }

  // Optional variable strength of descriptor.
  inline bool has_strength() const {
    return strength_ != kTheiaInvalidDescriptorVar;
  }
  inline double strength() const { return strength_; }
  inline void set_strength(double strength) { strength_ = strength; }

  // Optional variable scale of descriptor.
  inline bool has_scale() const { return scale_ != kTheiaInvalidDescriptorVar; }
  inline double scale() const { return scale_; }
  inline void set_scale(double scale) { scale_ = scale; }

  // Optional variable orientation of descriptor.
  inline bool has_orientation() const {
    return orientation_ != kTheiaInvalidDescriptorVar;
  }
  inline double orientation() const { return orientation_; }
  inline void set_orientation(double orientation) {
    orientation_ = orientation;
  }

 protected:
  const std::size_t dimensions_;
  DescriptorType descriptor_type_;
  double x_;
  double y_;
  double strength_;
  double scale_;
  double orientation_;
};

// Class for Float descriptors.
class FloatDescriptor : public Descriptor {
 public:
  FloatDescriptor(std::size_t dimensions, DescriptorType type)
      : Descriptor(dimensions, type) {
    data_ = new float[dimensions];
  }
  virtual ~FloatDescriptor() { delete[] data_; }

  // Accessor operators for convenience
  virtual inline float& operator[](std::size_t i) {
    CHECK_LT(i, dimensions_);
    return data_[i];
  }
  virtual inline const float& operator[](std::size_t i) const {
    CHECK_LT(i, dimensions_);
    return data_[i];
  }

  // Get a pointer to the data.
  virtual inline float* FloatData() { return data_; }
  virtual inline const float* FloatData() const { return data_; }

 protected:
  float* data_;
};

// Class for binary descriptors.
class BinaryDescriptor : public Descriptor {
 public:
  BinaryDescriptor(std::size_t dimensions, DescriptorType type)
      : Descriptor(dimensions, type) {
    const std::size_t num_char_blocks = (dimensions_ - 1) / sizeof(uchar) + 1;
    data_ = new uchar[num_char_blocks];
  }

  // Copy constructor needs to be explicitly defined because of the reinterpret
  // cast.
  BinaryDescriptor(const BinaryDescriptor& copy_from)
      : BinaryDescriptor(copy_from.Dimensions(), copy_from.descriptor_type()) {
    const std::size_t num_char_blocks = (dimensions_ - 1) / sizeof(uchar) + 1;
    data_ = new uchar[num_char_blocks];
    std::copy(copy_from.data_, copy_from.data_ + num_char_blocks, data_);
  }

  // Assignment operator is explicitly defined so that the reinterpret cast
  // holds valid.
  BinaryDescriptor& operator=(const BinaryDescriptor& copy_from) {
    if (this != &copy_from) {
      CHECK_EQ(dimensions_, copy_from.Dimensions());
      const std::size_t num_char_blocks = (dimensions_ - 1) / sizeof(uchar) + 1;
      uchar* new_data = new uchar[num_char_blocks];
      std::copy(copy_from.data_, copy_from.data_ + num_char_blocks, new_data);
      delete[] data_;
      data_ = new_data;
    }
    return *this;
  }

  virtual ~BinaryDescriptor() { delete[] data_; }

  virtual inline uchar* CharData() { return data_; }
  virtual inline const uchar* CharData() const { return data_; }

 protected:
  // data_ is the uchar array which contains the data. The location of this data
  // is constant! We use a reinterpret cast to reference the data as a bitset
  // for simplicity. This allows us to use the uchar array for SSE operations,
  // and bitsets for the rest. This reinterpret case technique is used in
  // OpenCV, so I am assuming it is relatively safe for now. TODO(cmsweeney):
  // make sure this doesn't mess things up when we copy it!
  uchar* data_;
};

}  // namespace theia

#endif  // THEIA_IMAGE_DESCRIPTOR_DESCRIPTOR_H_
