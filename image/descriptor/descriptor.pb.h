// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: image/descriptor/descriptor.proto

#ifndef PROTOBUF_image_2fdescriptor_2fdescriptor_2eproto__INCLUDED
#define PROTOBUF_image_2fdescriptor_2fdescriptor_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "image/keypoint_detector/keypoint.pb.h"
// @@protoc_insertion_point(includes)

namespace theia {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_image_2fdescriptor_2fdescriptor_2eproto();
void protobuf_AssignDesc_image_2fdescriptor_2fdescriptor_2eproto();
void protobuf_ShutdownFile_image_2fdescriptor_2fdescriptor_2eproto();

class DescriptorProto;
class DescriptorProto_Color;
class DescriptorsProto;

enum DescriptorProto_DescriptorType {
  DescriptorProto_DescriptorType_OTHER = 0,
  DescriptorProto_DescriptorType_BRIEF = 1,
  DescriptorProto_DescriptorType_DAISY = 2,
  DescriptorProto_DescriptorType_PATCH = 3,
  DescriptorProto_DescriptorType_SIFT = 4,
  DescriptorProto_DescriptorType_BRISK = 5
};
bool DescriptorProto_DescriptorType_IsValid(int value);
const DescriptorProto_DescriptorType DescriptorProto_DescriptorType_DescriptorType_MIN = DescriptorProto_DescriptorType_OTHER;
const DescriptorProto_DescriptorType DescriptorProto_DescriptorType_DescriptorType_MAX = DescriptorProto_DescriptorType_BRISK;
const int DescriptorProto_DescriptorType_DescriptorType_ARRAYSIZE = DescriptorProto_DescriptorType_DescriptorType_MAX + 1;

const ::google::protobuf::EnumDescriptor* DescriptorProto_DescriptorType_descriptor();
inline const ::std::string& DescriptorProto_DescriptorType_Name(DescriptorProto_DescriptorType value) {
  return ::google::protobuf::internal::NameOfEnum(
    DescriptorProto_DescriptorType_descriptor(), value);
}
inline bool DescriptorProto_DescriptorType_Parse(
    const ::std::string& name, DescriptorProto_DescriptorType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DescriptorProto_DescriptorType>(
    DescriptorProto_DescriptorType_descriptor(), name, value);
}
// ===================================================================

class DescriptorProto_Color : public ::google::protobuf::Message {
 public:
  DescriptorProto_Color();
  virtual ~DescriptorProto_Color();

  DescriptorProto_Color(const DescriptorProto_Color& from);

  inline DescriptorProto_Color& operator=(const DescriptorProto_Color& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DescriptorProto_Color& default_instance();

  void Swap(DescriptorProto_Color* other);

  // implements Message ----------------------------------------------

  DescriptorProto_Color* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DescriptorProto_Color& from);
  void MergeFrom(const DescriptorProto_Color& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional float r = 1;
  inline bool has_r() const;
  inline void clear_r();
  static const int kRFieldNumber = 1;
  inline float r() const;
  inline void set_r(float value);

  // optional float g = 2;
  inline bool has_g() const;
  inline void clear_g();
  static const int kGFieldNumber = 2;
  inline float g() const;
  inline void set_g(float value);

  // optional float b = 3;
  inline bool has_b() const;
  inline void clear_b();
  static const int kBFieldNumber = 3;
  inline float b() const;
  inline void set_b(float value);

  // @@protoc_insertion_point(class_scope:theia.DescriptorProto.Color)
 private:
  inline void set_has_r();
  inline void clear_has_r();
  inline void set_has_g();
  inline void clear_has_g();
  inline void set_has_b();
  inline void clear_has_b();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  float r_;
  float g_;
  float b_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_image_2fdescriptor_2fdescriptor_2eproto();
  friend void protobuf_AssignDesc_image_2fdescriptor_2fdescriptor_2eproto();
  friend void protobuf_ShutdownFile_image_2fdescriptor_2fdescriptor_2eproto();

  void InitAsDefaultInstance();
  static DescriptorProto_Color* default_instance_;
};
// -------------------------------------------------------------------

class DescriptorProto : public ::google::protobuf::Message {
 public:
  DescriptorProto();
  virtual ~DescriptorProto();

  DescriptorProto(const DescriptorProto& from);

  inline DescriptorProto& operator=(const DescriptorProto& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DescriptorProto& default_instance();

  void Swap(DescriptorProto* other);

  // implements Message ----------------------------------------------

  DescriptorProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DescriptorProto& from);
  void MergeFrom(const DescriptorProto& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef DescriptorProto_Color Color;

  typedef DescriptorProto_DescriptorType DescriptorType;
  static const DescriptorType OTHER = DescriptorProto_DescriptorType_OTHER;
  static const DescriptorType BRIEF = DescriptorProto_DescriptorType_BRIEF;
  static const DescriptorType DAISY = DescriptorProto_DescriptorType_DAISY;
  static const DescriptorType PATCH = DescriptorProto_DescriptorType_PATCH;
  static const DescriptorType SIFT = DescriptorProto_DescriptorType_SIFT;
  static const DescriptorType BRISK = DescriptorProto_DescriptorType_BRISK;
  static inline bool DescriptorType_IsValid(int value) {
    return DescriptorProto_DescriptorType_IsValid(value);
  }
  static const DescriptorType DescriptorType_MIN =
    DescriptorProto_DescriptorType_DescriptorType_MIN;
  static const DescriptorType DescriptorType_MAX =
    DescriptorProto_DescriptorType_DescriptorType_MAX;
  static const int DescriptorType_ARRAYSIZE =
    DescriptorProto_DescriptorType_DescriptorType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  DescriptorType_descriptor() {
    return DescriptorProto_DescriptorType_descriptor();
  }
  static inline const ::std::string& DescriptorType_Name(DescriptorType value) {
    return DescriptorProto_DescriptorType_Name(value);
  }
  static inline bool DescriptorType_Parse(const ::std::string& name,
      DescriptorType* value) {
    return DescriptorProto_DescriptorType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional int32 descriptor_id = 1;
  inline bool has_descriptor_id() const;
  inline void clear_descriptor_id();
  static const int kDescriptorIdFieldNumber = 1;
  inline ::google::protobuf::int32 descriptor_id() const;
  inline void set_descriptor_id(::google::protobuf::int32 value);

  // optional int32 image_id = 2;
  inline bool has_image_id() const;
  inline void clear_image_id();
  static const int kImageIdFieldNumber = 2;
  inline ::google::protobuf::int32 image_id() const;
  inline void set_image_id(::google::protobuf::int32 value);

  // optional .theia.KeypointProto keypoint = 3;
  inline bool has_keypoint() const;
  inline void clear_keypoint();
  static const int kKeypointFieldNumber = 3;
  inline const ::theia::KeypointProto& keypoint() const;
  inline ::theia::KeypointProto* mutable_keypoint();
  inline ::theia::KeypointProto* release_keypoint();
  inline void set_allocated_keypoint(::theia::KeypointProto* keypoint);

  // optional string binary_descriptor = 4;
  inline bool has_binary_descriptor() const;
  inline void clear_binary_descriptor();
  static const int kBinaryDescriptorFieldNumber = 4;
  inline const ::std::string& binary_descriptor() const;
  inline void set_binary_descriptor(const ::std::string& value);
  inline void set_binary_descriptor(const char* value);
  inline void set_binary_descriptor(const char* value, size_t size);
  inline ::std::string* mutable_binary_descriptor();
  inline ::std::string* release_binary_descriptor();
  inline void set_allocated_binary_descriptor(::std::string* binary_descriptor);

  // repeated float float_descriptor = 5;
  inline int float_descriptor_size() const;
  inline void clear_float_descriptor();
  static const int kFloatDescriptorFieldNumber = 5;
  inline float float_descriptor(int index) const;
  inline void set_float_descriptor(int index, float value);
  inline void add_float_descriptor(float value);
  inline const ::google::protobuf::RepeatedField< float >&
      float_descriptor() const;
  inline ::google::protobuf::RepeatedField< float >*
      mutable_float_descriptor();

  // optional int32 x = 6;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 6;
  inline ::google::protobuf::int32 x() const;
  inline void set_x(::google::protobuf::int32 value);

  // optional int32 y = 7;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 7;
  inline ::google::protobuf::int32 y() const;
  inline void set_y(::google::protobuf::int32 value);

  // optional double strength = 8;
  inline bool has_strength() const;
  inline void clear_strength();
  static const int kStrengthFieldNumber = 8;
  inline double strength() const;
  inline void set_strength(double value);

  // optional double orientation = 9;
  inline bool has_orientation() const;
  inline void clear_orientation();
  static const int kOrientationFieldNumber = 9;
  inline double orientation() const;
  inline void set_orientation(double value);

  // optional double scale = 10;
  inline bool has_scale() const;
  inline void clear_scale();
  static const int kScaleFieldNumber = 10;
  inline double scale() const;
  inline void set_scale(double value);

  // optional int32 track_id = 11;
  inline bool has_track_id() const;
  inline void clear_track_id();
  static const int kTrackIdFieldNumber = 11;
  inline ::google::protobuf::int32 track_id() const;
  inline void set_track_id(::google::protobuf::int32 value);

  // optional .theia.DescriptorProto.Color color = 12;
  inline bool has_color() const;
  inline void clear_color();
  static const int kColorFieldNumber = 12;
  inline const ::theia::DescriptorProto_Color& color() const;
  inline ::theia::DescriptorProto_Color* mutable_color();
  inline ::theia::DescriptorProto_Color* release_color();
  inline void set_allocated_color(::theia::DescriptorProto_Color* color);

  // optional .theia.DescriptorProto.DescriptorType descriptor_type = 13;
  inline bool has_descriptor_type() const;
  inline void clear_descriptor_type();
  static const int kDescriptorTypeFieldNumber = 13;
  inline ::theia::DescriptorProto_DescriptorType descriptor_type() const;
  inline void set_descriptor_type(::theia::DescriptorProto_DescriptorType value);

  // @@protoc_insertion_point(class_scope:theia.DescriptorProto)
 private:
  inline void set_has_descriptor_id();
  inline void clear_has_descriptor_id();
  inline void set_has_image_id();
  inline void clear_has_image_id();
  inline void set_has_keypoint();
  inline void clear_has_keypoint();
  inline void set_has_binary_descriptor();
  inline void clear_has_binary_descriptor();
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_strength();
  inline void clear_has_strength();
  inline void set_has_orientation();
  inline void clear_has_orientation();
  inline void set_has_scale();
  inline void clear_has_scale();
  inline void set_has_track_id();
  inline void clear_has_track_id();
  inline void set_has_color();
  inline void clear_has_color();
  inline void set_has_descriptor_type();
  inline void clear_has_descriptor_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 descriptor_id_;
  ::google::protobuf::int32 image_id_;
  ::theia::KeypointProto* keypoint_;
  ::std::string* binary_descriptor_;
  ::google::protobuf::RepeatedField< float > float_descriptor_;
  ::google::protobuf::int32 x_;
  ::google::protobuf::int32 y_;
  double strength_;
  double orientation_;
  double scale_;
  ::theia::DescriptorProto_Color* color_;
  ::google::protobuf::int32 track_id_;
  int descriptor_type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(13 + 31) / 32];

  friend void  protobuf_AddDesc_image_2fdescriptor_2fdescriptor_2eproto();
  friend void protobuf_AssignDesc_image_2fdescriptor_2fdescriptor_2eproto();
  friend void protobuf_ShutdownFile_image_2fdescriptor_2fdescriptor_2eproto();

  void InitAsDefaultInstance();
  static DescriptorProto* default_instance_;
};
// -------------------------------------------------------------------

class DescriptorsProto : public ::google::protobuf::Message {
 public:
  DescriptorsProto();
  virtual ~DescriptorsProto();

  DescriptorsProto(const DescriptorsProto& from);

  inline DescriptorsProto& operator=(const DescriptorsProto& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DescriptorsProto& default_instance();

  void Swap(DescriptorsProto* other);

  // implements Message ----------------------------------------------

  DescriptorsProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DescriptorsProto& from);
  void MergeFrom(const DescriptorsProto& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .theia.DescriptorProto feature_descriptor = 1;
  inline int feature_descriptor_size() const;
  inline void clear_feature_descriptor();
  static const int kFeatureDescriptorFieldNumber = 1;
  inline const ::theia::DescriptorProto& feature_descriptor(int index) const;
  inline ::theia::DescriptorProto* mutable_feature_descriptor(int index);
  inline ::theia::DescriptorProto* add_feature_descriptor();
  inline const ::google::protobuf::RepeatedPtrField< ::theia::DescriptorProto >&
      feature_descriptor() const;
  inline ::google::protobuf::RepeatedPtrField< ::theia::DescriptorProto >*
      mutable_feature_descriptor();

  // @@protoc_insertion_point(class_scope:theia.DescriptorsProto)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::theia::DescriptorProto > feature_descriptor_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_image_2fdescriptor_2fdescriptor_2eproto();
  friend void protobuf_AssignDesc_image_2fdescriptor_2fdescriptor_2eproto();
  friend void protobuf_ShutdownFile_image_2fdescriptor_2fdescriptor_2eproto();

  void InitAsDefaultInstance();
  static DescriptorsProto* default_instance_;
};
// ===================================================================


// ===================================================================

// DescriptorProto_Color

// optional float r = 1;
inline bool DescriptorProto_Color::has_r() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DescriptorProto_Color::set_has_r() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DescriptorProto_Color::clear_has_r() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DescriptorProto_Color::clear_r() {
  r_ = 0;
  clear_has_r();
}
inline float DescriptorProto_Color::r() const {
  return r_;
}
inline void DescriptorProto_Color::set_r(float value) {
  set_has_r();
  r_ = value;
}

// optional float g = 2;
inline bool DescriptorProto_Color::has_g() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DescriptorProto_Color::set_has_g() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DescriptorProto_Color::clear_has_g() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DescriptorProto_Color::clear_g() {
  g_ = 0;
  clear_has_g();
}
inline float DescriptorProto_Color::g() const {
  return g_;
}
inline void DescriptorProto_Color::set_g(float value) {
  set_has_g();
  g_ = value;
}

// optional float b = 3;
inline bool DescriptorProto_Color::has_b() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DescriptorProto_Color::set_has_b() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DescriptorProto_Color::clear_has_b() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DescriptorProto_Color::clear_b() {
  b_ = 0;
  clear_has_b();
}
inline float DescriptorProto_Color::b() const {
  return b_;
}
inline void DescriptorProto_Color::set_b(float value) {
  set_has_b();
  b_ = value;
}

// -------------------------------------------------------------------

// DescriptorProto

// optional int32 descriptor_id = 1;
inline bool DescriptorProto::has_descriptor_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void DescriptorProto::set_has_descriptor_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void DescriptorProto::clear_has_descriptor_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void DescriptorProto::clear_descriptor_id() {
  descriptor_id_ = 0;
  clear_has_descriptor_id();
}
inline ::google::protobuf::int32 DescriptorProto::descriptor_id() const {
  return descriptor_id_;
}
inline void DescriptorProto::set_descriptor_id(::google::protobuf::int32 value) {
  set_has_descriptor_id();
  descriptor_id_ = value;
}

// optional int32 image_id = 2;
inline bool DescriptorProto::has_image_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DescriptorProto::set_has_image_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DescriptorProto::clear_has_image_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DescriptorProto::clear_image_id() {
  image_id_ = 0;
  clear_has_image_id();
}
inline ::google::protobuf::int32 DescriptorProto::image_id() const {
  return image_id_;
}
inline void DescriptorProto::set_image_id(::google::protobuf::int32 value) {
  set_has_image_id();
  image_id_ = value;
}

// optional .theia.KeypointProto keypoint = 3;
inline bool DescriptorProto::has_keypoint() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void DescriptorProto::set_has_keypoint() {
  _has_bits_[0] |= 0x00000004u;
}
inline void DescriptorProto::clear_has_keypoint() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void DescriptorProto::clear_keypoint() {
  if (keypoint_ != NULL) keypoint_->::theia::KeypointProto::Clear();
  clear_has_keypoint();
}
inline const ::theia::KeypointProto& DescriptorProto::keypoint() const {
  return keypoint_ != NULL ? *keypoint_ : *default_instance_->keypoint_;
}
inline ::theia::KeypointProto* DescriptorProto::mutable_keypoint() {
  set_has_keypoint();
  if (keypoint_ == NULL) keypoint_ = new ::theia::KeypointProto;
  return keypoint_;
}
inline ::theia::KeypointProto* DescriptorProto::release_keypoint() {
  clear_has_keypoint();
  ::theia::KeypointProto* temp = keypoint_;
  keypoint_ = NULL;
  return temp;
}
inline void DescriptorProto::set_allocated_keypoint(::theia::KeypointProto* keypoint) {
  delete keypoint_;
  keypoint_ = keypoint;
  if (keypoint) {
    set_has_keypoint();
  } else {
    clear_has_keypoint();
  }
}

// optional string binary_descriptor = 4;
inline bool DescriptorProto::has_binary_descriptor() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void DescriptorProto::set_has_binary_descriptor() {
  _has_bits_[0] |= 0x00000008u;
}
inline void DescriptorProto::clear_has_binary_descriptor() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void DescriptorProto::clear_binary_descriptor() {
  if (binary_descriptor_ != &::google::protobuf::internal::kEmptyString) {
    binary_descriptor_->clear();
  }
  clear_has_binary_descriptor();
}
inline const ::std::string& DescriptorProto::binary_descriptor() const {
  return *binary_descriptor_;
}
inline void DescriptorProto::set_binary_descriptor(const ::std::string& value) {
  set_has_binary_descriptor();
  if (binary_descriptor_ == &::google::protobuf::internal::kEmptyString) {
    binary_descriptor_ = new ::std::string;
  }
  binary_descriptor_->assign(value);
}
inline void DescriptorProto::set_binary_descriptor(const char* value) {
  set_has_binary_descriptor();
  if (binary_descriptor_ == &::google::protobuf::internal::kEmptyString) {
    binary_descriptor_ = new ::std::string;
  }
  binary_descriptor_->assign(value);
}
inline void DescriptorProto::set_binary_descriptor(const char* value, size_t size) {
  set_has_binary_descriptor();
  if (binary_descriptor_ == &::google::protobuf::internal::kEmptyString) {
    binary_descriptor_ = new ::std::string;
  }
  binary_descriptor_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* DescriptorProto::mutable_binary_descriptor() {
  set_has_binary_descriptor();
  if (binary_descriptor_ == &::google::protobuf::internal::kEmptyString) {
    binary_descriptor_ = new ::std::string;
  }
  return binary_descriptor_;
}
inline ::std::string* DescriptorProto::release_binary_descriptor() {
  clear_has_binary_descriptor();
  if (binary_descriptor_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = binary_descriptor_;
    binary_descriptor_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void DescriptorProto::set_allocated_binary_descriptor(::std::string* binary_descriptor) {
  if (binary_descriptor_ != &::google::protobuf::internal::kEmptyString) {
    delete binary_descriptor_;
  }
  if (binary_descriptor) {
    set_has_binary_descriptor();
    binary_descriptor_ = binary_descriptor;
  } else {
    clear_has_binary_descriptor();
    binary_descriptor_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated float float_descriptor = 5;
inline int DescriptorProto::float_descriptor_size() const {
  return float_descriptor_.size();
}
inline void DescriptorProto::clear_float_descriptor() {
  float_descriptor_.Clear();
}
inline float DescriptorProto::float_descriptor(int index) const {
  return float_descriptor_.Get(index);
}
inline void DescriptorProto::set_float_descriptor(int index, float value) {
  float_descriptor_.Set(index, value);
}
inline void DescriptorProto::add_float_descriptor(float value) {
  float_descriptor_.Add(value);
}
inline const ::google::protobuf::RepeatedField< float >&
DescriptorProto::float_descriptor() const {
  return float_descriptor_;
}
inline ::google::protobuf::RepeatedField< float >*
DescriptorProto::mutable_float_descriptor() {
  return &float_descriptor_;
}

// optional int32 x = 6;
inline bool DescriptorProto::has_x() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void DescriptorProto::set_has_x() {
  _has_bits_[0] |= 0x00000020u;
}
inline void DescriptorProto::clear_has_x() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void DescriptorProto::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline ::google::protobuf::int32 DescriptorProto::x() const {
  return x_;
}
inline void DescriptorProto::set_x(::google::protobuf::int32 value) {
  set_has_x();
  x_ = value;
}

// optional int32 y = 7;
inline bool DescriptorProto::has_y() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void DescriptorProto::set_has_y() {
  _has_bits_[0] |= 0x00000040u;
}
inline void DescriptorProto::clear_has_y() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void DescriptorProto::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline ::google::protobuf::int32 DescriptorProto::y() const {
  return y_;
}
inline void DescriptorProto::set_y(::google::protobuf::int32 value) {
  set_has_y();
  y_ = value;
}

// optional double strength = 8;
inline bool DescriptorProto::has_strength() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void DescriptorProto::set_has_strength() {
  _has_bits_[0] |= 0x00000080u;
}
inline void DescriptorProto::clear_has_strength() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void DescriptorProto::clear_strength() {
  strength_ = 0;
  clear_has_strength();
}
inline double DescriptorProto::strength() const {
  return strength_;
}
inline void DescriptorProto::set_strength(double value) {
  set_has_strength();
  strength_ = value;
}

// optional double orientation = 9;
inline bool DescriptorProto::has_orientation() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void DescriptorProto::set_has_orientation() {
  _has_bits_[0] |= 0x00000100u;
}
inline void DescriptorProto::clear_has_orientation() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void DescriptorProto::clear_orientation() {
  orientation_ = 0;
  clear_has_orientation();
}
inline double DescriptorProto::orientation() const {
  return orientation_;
}
inline void DescriptorProto::set_orientation(double value) {
  set_has_orientation();
  orientation_ = value;
}

// optional double scale = 10;
inline bool DescriptorProto::has_scale() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void DescriptorProto::set_has_scale() {
  _has_bits_[0] |= 0x00000200u;
}
inline void DescriptorProto::clear_has_scale() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void DescriptorProto::clear_scale() {
  scale_ = 0;
  clear_has_scale();
}
inline double DescriptorProto::scale() const {
  return scale_;
}
inline void DescriptorProto::set_scale(double value) {
  set_has_scale();
  scale_ = value;
}

// optional int32 track_id = 11;
inline bool DescriptorProto::has_track_id() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void DescriptorProto::set_has_track_id() {
  _has_bits_[0] |= 0x00000400u;
}
inline void DescriptorProto::clear_has_track_id() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void DescriptorProto::clear_track_id() {
  track_id_ = 0;
  clear_has_track_id();
}
inline ::google::protobuf::int32 DescriptorProto::track_id() const {
  return track_id_;
}
inline void DescriptorProto::set_track_id(::google::protobuf::int32 value) {
  set_has_track_id();
  track_id_ = value;
}

// optional .theia.DescriptorProto.Color color = 12;
inline bool DescriptorProto::has_color() const {
  return (_has_bits_[0] & 0x00000800u) != 0;
}
inline void DescriptorProto::set_has_color() {
  _has_bits_[0] |= 0x00000800u;
}
inline void DescriptorProto::clear_has_color() {
  _has_bits_[0] &= ~0x00000800u;
}
inline void DescriptorProto::clear_color() {
  if (color_ != NULL) color_->::theia::DescriptorProto_Color::Clear();
  clear_has_color();
}
inline const ::theia::DescriptorProto_Color& DescriptorProto::color() const {
  return color_ != NULL ? *color_ : *default_instance_->color_;
}
inline ::theia::DescriptorProto_Color* DescriptorProto::mutable_color() {
  set_has_color();
  if (color_ == NULL) color_ = new ::theia::DescriptorProto_Color;
  return color_;
}
inline ::theia::DescriptorProto_Color* DescriptorProto::release_color() {
  clear_has_color();
  ::theia::DescriptorProto_Color* temp = color_;
  color_ = NULL;
  return temp;
}
inline void DescriptorProto::set_allocated_color(::theia::DescriptorProto_Color* color) {
  delete color_;
  color_ = color;
  if (color) {
    set_has_color();
  } else {
    clear_has_color();
  }
}

// optional .theia.DescriptorProto.DescriptorType descriptor_type = 13;
inline bool DescriptorProto::has_descriptor_type() const {
  return (_has_bits_[0] & 0x00001000u) != 0;
}
inline void DescriptorProto::set_has_descriptor_type() {
  _has_bits_[0] |= 0x00001000u;
}
inline void DescriptorProto::clear_has_descriptor_type() {
  _has_bits_[0] &= ~0x00001000u;
}
inline void DescriptorProto::clear_descriptor_type() {
  descriptor_type_ = 0;
  clear_has_descriptor_type();
}
inline ::theia::DescriptorProto_DescriptorType DescriptorProto::descriptor_type() const {
  return static_cast< ::theia::DescriptorProto_DescriptorType >(descriptor_type_);
}
inline void DescriptorProto::set_descriptor_type(::theia::DescriptorProto_DescriptorType value) {
  assert(::theia::DescriptorProto_DescriptorType_IsValid(value));
  set_has_descriptor_type();
  descriptor_type_ = value;
}

// -------------------------------------------------------------------

// DescriptorsProto

// repeated .theia.DescriptorProto feature_descriptor = 1;
inline int DescriptorsProto::feature_descriptor_size() const {
  return feature_descriptor_.size();
}
inline void DescriptorsProto::clear_feature_descriptor() {
  feature_descriptor_.Clear();
}
inline const ::theia::DescriptorProto& DescriptorsProto::feature_descriptor(int index) const {
  return feature_descriptor_.Get(index);
}
inline ::theia::DescriptorProto* DescriptorsProto::mutable_feature_descriptor(int index) {
  return feature_descriptor_.Mutable(index);
}
inline ::theia::DescriptorProto* DescriptorsProto::add_feature_descriptor() {
  return feature_descriptor_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::theia::DescriptorProto >&
DescriptorsProto::feature_descriptor() const {
  return feature_descriptor_;
}
inline ::google::protobuf::RepeatedPtrField< ::theia::DescriptorProto >*
DescriptorsProto::mutable_feature_descriptor() {
  return &feature_descriptor_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace theia

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::theia::DescriptorProto_DescriptorType>() {
  return ::theia::DescriptorProto_DescriptorType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_image_2fdescriptor_2fdescriptor_2eproto__INCLUDED
