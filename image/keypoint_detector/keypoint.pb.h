// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: image/keypoint_detector/keypoint.proto

#ifndef PROTOBUF_image_2fkeypoint_5fdetector_2fkeypoint_2eproto__INCLUDED
#define PROTOBUF_image_2fkeypoint_5fdetector_2fkeypoint_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

namespace theia {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();
void protobuf_AssignDesc_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();
void protobuf_ShutdownFile_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();

class KeypointProto;
class KeypointProto_Location;
class KeypointsProto;

enum KeypointProto_KeypointType {
  KeypointProto_KeypointType_OTHER = 0,
  KeypointProto_KeypointType_FAST = 1,
  KeypointProto_KeypointType_HARRIS = 2
};
bool KeypointProto_KeypointType_IsValid(int value);
const KeypointProto_KeypointType KeypointProto_KeypointType_KeypointType_MIN = KeypointProto_KeypointType_OTHER;
const KeypointProto_KeypointType KeypointProto_KeypointType_KeypointType_MAX = KeypointProto_KeypointType_HARRIS;
const int KeypointProto_KeypointType_KeypointType_ARRAYSIZE = KeypointProto_KeypointType_KeypointType_MAX + 1;

const ::google::protobuf::EnumDescriptor* KeypointProto_KeypointType_descriptor();
inline const ::std::string& KeypointProto_KeypointType_Name(KeypointProto_KeypointType value) {
  return ::google::protobuf::internal::NameOfEnum(
    KeypointProto_KeypointType_descriptor(), value);
}
inline bool KeypointProto_KeypointType_Parse(
    const ::std::string& name, KeypointProto_KeypointType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<KeypointProto_KeypointType>(
    KeypointProto_KeypointType_descriptor(), name, value);
}
// ===================================================================

class KeypointProto_Location : public ::google::protobuf::Message {
 public:
  KeypointProto_Location();
  virtual ~KeypointProto_Location();

  KeypointProto_Location(const KeypointProto_Location& from);

  inline KeypointProto_Location& operator=(const KeypointProto_Location& from) {
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
  static const KeypointProto_Location& default_instance();

  void Swap(KeypointProto_Location* other);

  // implements Message ----------------------------------------------

  KeypointProto_Location* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeypointProto_Location& from);
  void MergeFrom(const KeypointProto_Location& from);
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

  // optional double x = 1;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 1;
  inline double x() const;
  inline void set_x(double value);

  // optional double y = 2;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 2;
  inline double y() const;
  inline void set_y(double value);

  // @@protoc_insertion_point(class_scope:theia.KeypointProto.Location)
 private:
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  double x_;
  double y_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();
  friend void protobuf_AssignDesc_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();
  friend void protobuf_ShutdownFile_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();

  void InitAsDefaultInstance();
  static KeypointProto_Location* default_instance_;
};
// -------------------------------------------------------------------

class KeypointProto : public ::google::protobuf::Message {
 public:
  KeypointProto();
  virtual ~KeypointProto();

  KeypointProto(const KeypointProto& from);

  inline KeypointProto& operator=(const KeypointProto& from) {
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
  static const KeypointProto& default_instance();

  void Swap(KeypointProto* other);

  // implements Message ----------------------------------------------

  KeypointProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeypointProto& from);
  void MergeFrom(const KeypointProto& from);
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

  typedef KeypointProto_Location Location;

  typedef KeypointProto_KeypointType KeypointType;
  static const KeypointType OTHER = KeypointProto_KeypointType_OTHER;
  static const KeypointType FAST = KeypointProto_KeypointType_FAST;
  static const KeypointType HARRIS = KeypointProto_KeypointType_HARRIS;
  static inline bool KeypointType_IsValid(int value) {
    return KeypointProto_KeypointType_IsValid(value);
  }
  static const KeypointType KeypointType_MIN =
    KeypointProto_KeypointType_KeypointType_MIN;
  static const KeypointType KeypointType_MAX =
    KeypointProto_KeypointType_KeypointType_MAX;
  static const int KeypointType_ARRAYSIZE =
    KeypointProto_KeypointType_KeypointType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  KeypointType_descriptor() {
    return KeypointProto_KeypointType_descriptor();
  }
  static inline const ::std::string& KeypointType_Name(KeypointType value) {
    return KeypointProto_KeypointType_Name(value);
  }
  static inline bool KeypointType_Parse(const ::std::string& name,
      KeypointType* value) {
    return KeypointProto_KeypointType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // optional int32 keypoint_id = 1;
  inline bool has_keypoint_id() const;
  inline void clear_keypoint_id();
  static const int kKeypointIdFieldNumber = 1;
  inline ::google::protobuf::int32 keypoint_id() const;
  inline void set_keypoint_id(::google::protobuf::int32 value);

  // optional int32 image_id = 2;
  inline bool has_image_id() const;
  inline void clear_image_id();
  static const int kImageIdFieldNumber = 2;
  inline ::google::protobuf::int32 image_id() const;
  inline void set_image_id(::google::protobuf::int32 value);

  // optional .theia.KeypointProto.KeypointType keypoint_detector = 3;
  inline bool has_keypoint_detector() const;
  inline void clear_keypoint_detector();
  static const int kKeypointDetectorFieldNumber = 3;
  inline ::theia::KeypointProto_KeypointType keypoint_detector() const;
  inline void set_keypoint_detector(::theia::KeypointProto_KeypointType value);

  // optional .theia.KeypointProto.Location location = 4;
  inline bool has_location() const;
  inline void clear_location();
  static const int kLocationFieldNumber = 4;
  inline const ::theia::KeypointProto_Location& location() const;
  inline ::theia::KeypointProto_Location* mutable_location();
  inline ::theia::KeypointProto_Location* release_location();
  inline void set_allocated_location(::theia::KeypointProto_Location* location);

  // optional double strength = 5;
  inline bool has_strength() const;
  inline void clear_strength();
  static const int kStrengthFieldNumber = 5;
  inline double strength() const;
  inline void set_strength(double value);

  // optional double orientation = 6;
  inline bool has_orientation() const;
  inline void clear_orientation();
  static const int kOrientationFieldNumber = 6;
  inline double orientation() const;
  inline void set_orientation(double value);

  // optional double scale = 7;
  inline bool has_scale() const;
  inline void clear_scale();
  static const int kScaleFieldNumber = 7;
  inline double scale() const;
  inline void set_scale(double value);

  // optional int32 track_id = 8;
  inline bool has_track_id() const;
  inline void clear_track_id();
  static const int kTrackIdFieldNumber = 8;
  inline ::google::protobuf::int32 track_id() const;
  inline void set_track_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:theia.KeypointProto)
 private:
  inline void set_has_keypoint_id();
  inline void clear_has_keypoint_id();
  inline void set_has_image_id();
  inline void clear_has_image_id();
  inline void set_has_keypoint_detector();
  inline void clear_has_keypoint_detector();
  inline void set_has_location();
  inline void clear_has_location();
  inline void set_has_strength();
  inline void clear_has_strength();
  inline void set_has_orientation();
  inline void clear_has_orientation();
  inline void set_has_scale();
  inline void clear_has_scale();
  inline void set_has_track_id();
  inline void clear_has_track_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 keypoint_id_;
  ::google::protobuf::int32 image_id_;
  ::theia::KeypointProto_Location* location_;
  double strength_;
  int keypoint_detector_;
  ::google::protobuf::int32 track_id_;
  double orientation_;
  double scale_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(8 + 31) / 32];

  friend void  protobuf_AddDesc_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();
  friend void protobuf_AssignDesc_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();
  friend void protobuf_ShutdownFile_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();

  void InitAsDefaultInstance();
  static KeypointProto* default_instance_;
};
// -------------------------------------------------------------------

class KeypointsProto : public ::google::protobuf::Message {
 public:
  KeypointsProto();
  virtual ~KeypointsProto();

  KeypointsProto(const KeypointsProto& from);

  inline KeypointsProto& operator=(const KeypointsProto& from) {
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
  static const KeypointsProto& default_instance();

  void Swap(KeypointsProto* other);

  // implements Message ----------------------------------------------

  KeypointsProto* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeypointsProto& from);
  void MergeFrom(const KeypointsProto& from);
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

  // repeated .theia.KeypointProto keypoint = 1;
  inline int keypoint_size() const;
  inline void clear_keypoint();
  static const int kKeypointFieldNumber = 1;
  inline const ::theia::KeypointProto& keypoint(int index) const;
  inline ::theia::KeypointProto* mutable_keypoint(int index);
  inline ::theia::KeypointProto* add_keypoint();
  inline const ::google::protobuf::RepeatedPtrField< ::theia::KeypointProto >&
      keypoint() const;
  inline ::google::protobuf::RepeatedPtrField< ::theia::KeypointProto >*
      mutable_keypoint();

  // @@protoc_insertion_point(class_scope:theia.KeypointsProto)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::theia::KeypointProto > keypoint_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();
  friend void protobuf_AssignDesc_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();
  friend void protobuf_ShutdownFile_image_2fkeypoint_5fdetector_2fkeypoint_2eproto();

  void InitAsDefaultInstance();
  static KeypointsProto* default_instance_;
};
// ===================================================================


// ===================================================================

// KeypointProto_Location

// optional double x = 1;
inline bool KeypointProto_Location::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeypointProto_Location::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeypointProto_Location::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeypointProto_Location::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline double KeypointProto_Location::x() const {
  return x_;
}
inline void KeypointProto_Location::set_x(double value) {
  set_has_x();
  x_ = value;
}

// optional double y = 2;
inline bool KeypointProto_Location::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KeypointProto_Location::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KeypointProto_Location::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KeypointProto_Location::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline double KeypointProto_Location::y() const {
  return y_;
}
inline void KeypointProto_Location::set_y(double value) {
  set_has_y();
  y_ = value;
}

// -------------------------------------------------------------------

// KeypointProto

// optional int32 keypoint_id = 1;
inline bool KeypointProto::has_keypoint_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeypointProto::set_has_keypoint_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeypointProto::clear_has_keypoint_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeypointProto::clear_keypoint_id() {
  keypoint_id_ = 0;
  clear_has_keypoint_id();
}
inline ::google::protobuf::int32 KeypointProto::keypoint_id() const {
  return keypoint_id_;
}
inline void KeypointProto::set_keypoint_id(::google::protobuf::int32 value) {
  set_has_keypoint_id();
  keypoint_id_ = value;
}

// optional int32 image_id = 2;
inline bool KeypointProto::has_image_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KeypointProto::set_has_image_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KeypointProto::clear_has_image_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KeypointProto::clear_image_id() {
  image_id_ = 0;
  clear_has_image_id();
}
inline ::google::protobuf::int32 KeypointProto::image_id() const {
  return image_id_;
}
inline void KeypointProto::set_image_id(::google::protobuf::int32 value) {
  set_has_image_id();
  image_id_ = value;
}

// optional .theia.KeypointProto.KeypointType keypoint_detector = 3;
inline bool KeypointProto::has_keypoint_detector() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void KeypointProto::set_has_keypoint_detector() {
  _has_bits_[0] |= 0x00000004u;
}
inline void KeypointProto::clear_has_keypoint_detector() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void KeypointProto::clear_keypoint_detector() {
  keypoint_detector_ = 0;
  clear_has_keypoint_detector();
}
inline ::theia::KeypointProto_KeypointType KeypointProto::keypoint_detector() const {
  return static_cast< ::theia::KeypointProto_KeypointType >(keypoint_detector_);
}
inline void KeypointProto::set_keypoint_detector(::theia::KeypointProto_KeypointType value) {
  assert(::theia::KeypointProto_KeypointType_IsValid(value));
  set_has_keypoint_detector();
  keypoint_detector_ = value;
}

// optional .theia.KeypointProto.Location location = 4;
inline bool KeypointProto::has_location() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void KeypointProto::set_has_location() {
  _has_bits_[0] |= 0x00000008u;
}
inline void KeypointProto::clear_has_location() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void KeypointProto::clear_location() {
  if (location_ != NULL) location_->::theia::KeypointProto_Location::Clear();
  clear_has_location();
}
inline const ::theia::KeypointProto_Location& KeypointProto::location() const {
  return location_ != NULL ? *location_ : *default_instance_->location_;
}
inline ::theia::KeypointProto_Location* KeypointProto::mutable_location() {
  set_has_location();
  if (location_ == NULL) location_ = new ::theia::KeypointProto_Location;
  return location_;
}
inline ::theia::KeypointProto_Location* KeypointProto::release_location() {
  clear_has_location();
  ::theia::KeypointProto_Location* temp = location_;
  location_ = NULL;
  return temp;
}
inline void KeypointProto::set_allocated_location(::theia::KeypointProto_Location* location) {
  delete location_;
  location_ = location;
  if (location) {
    set_has_location();
  } else {
    clear_has_location();
  }
}

// optional double strength = 5;
inline bool KeypointProto::has_strength() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void KeypointProto::set_has_strength() {
  _has_bits_[0] |= 0x00000010u;
}
inline void KeypointProto::clear_has_strength() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void KeypointProto::clear_strength() {
  strength_ = 0;
  clear_has_strength();
}
inline double KeypointProto::strength() const {
  return strength_;
}
inline void KeypointProto::set_strength(double value) {
  set_has_strength();
  strength_ = value;
}

// optional double orientation = 6;
inline bool KeypointProto::has_orientation() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void KeypointProto::set_has_orientation() {
  _has_bits_[0] |= 0x00000020u;
}
inline void KeypointProto::clear_has_orientation() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void KeypointProto::clear_orientation() {
  orientation_ = 0;
  clear_has_orientation();
}
inline double KeypointProto::orientation() const {
  return orientation_;
}
inline void KeypointProto::set_orientation(double value) {
  set_has_orientation();
  orientation_ = value;
}

// optional double scale = 7;
inline bool KeypointProto::has_scale() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void KeypointProto::set_has_scale() {
  _has_bits_[0] |= 0x00000040u;
}
inline void KeypointProto::clear_has_scale() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void KeypointProto::clear_scale() {
  scale_ = 0;
  clear_has_scale();
}
inline double KeypointProto::scale() const {
  return scale_;
}
inline void KeypointProto::set_scale(double value) {
  set_has_scale();
  scale_ = value;
}

// optional int32 track_id = 8;
inline bool KeypointProto::has_track_id() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void KeypointProto::set_has_track_id() {
  _has_bits_[0] |= 0x00000080u;
}
inline void KeypointProto::clear_has_track_id() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void KeypointProto::clear_track_id() {
  track_id_ = 0;
  clear_has_track_id();
}
inline ::google::protobuf::int32 KeypointProto::track_id() const {
  return track_id_;
}
inline void KeypointProto::set_track_id(::google::protobuf::int32 value) {
  set_has_track_id();
  track_id_ = value;
}

// -------------------------------------------------------------------

// KeypointsProto

// repeated .theia.KeypointProto keypoint = 1;
inline int KeypointsProto::keypoint_size() const {
  return keypoint_.size();
}
inline void KeypointsProto::clear_keypoint() {
  keypoint_.Clear();
}
inline const ::theia::KeypointProto& KeypointsProto::keypoint(int index) const {
  return keypoint_.Get(index);
}
inline ::theia::KeypointProto* KeypointsProto::mutable_keypoint(int index) {
  return keypoint_.Mutable(index);
}
inline ::theia::KeypointProto* KeypointsProto::add_keypoint() {
  return keypoint_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::theia::KeypointProto >&
KeypointsProto::keypoint() const {
  return keypoint_;
}
inline ::google::protobuf::RepeatedPtrField< ::theia::KeypointProto >*
KeypointsProto::mutable_keypoint() {
  return &keypoint_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace theia

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::theia::KeypointProto_KeypointType>() {
  return ::theia::KeypointProto_KeypointType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_image_2fkeypoint_5fdetector_2fkeypoint_2eproto__INCLUDED
