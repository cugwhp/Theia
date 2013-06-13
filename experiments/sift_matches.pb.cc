// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: experiments/sift_matches.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "experiments/sift_matches.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* FeatureKnnProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FeatureKnnProto_reflection_ = NULL;
const ::google::protobuf::Descriptor* FeatureMatchProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FeatureMatchProto_reflection_ = NULL;
const ::google::protobuf::Descriptor* ImagePairMatchProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ImagePairMatchProto_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_experiments_2fsift_5fmatches_2eproto() {
  protobuf_AddDesc_experiments_2fsift_5fmatches_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "experiments/sift_matches.proto");
  GOOGLE_CHECK(file != NULL);
  FeatureKnnProto_descriptor_ = file->message_type(0);
  static const int FeatureKnnProto_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureKnnProto, feature_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureKnnProto, distance_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureKnnProto, scale_),
  };
  FeatureKnnProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FeatureKnnProto_descriptor_,
      FeatureKnnProto::default_instance_,
      FeatureKnnProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureKnnProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureKnnProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FeatureKnnProto));
  FeatureMatchProto_descriptor_ = file->message_type(1);
  static const int FeatureMatchProto_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureMatchProto, feature_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureMatchProto, scale_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureMatchProto, knn_match_),
  };
  FeatureMatchProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FeatureMatchProto_descriptor_,
      FeatureMatchProto::default_instance_,
      FeatureMatchProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureMatchProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FeatureMatchProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FeatureMatchProto));
  ImagePairMatchProto_descriptor_ = file->message_type(2);
  static const int ImagePairMatchProto_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagePairMatchProto, image1_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagePairMatchProto, image2_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagePairMatchProto, feature_match_),
  };
  ImagePairMatchProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ImagePairMatchProto_descriptor_,
      ImagePairMatchProto::default_instance_,
      ImagePairMatchProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagePairMatchProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ImagePairMatchProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ImagePairMatchProto));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_experiments_2fsift_5fmatches_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FeatureKnnProto_descriptor_, &FeatureKnnProto::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FeatureMatchProto_descriptor_, &FeatureMatchProto::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ImagePairMatchProto_descriptor_, &ImagePairMatchProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_experiments_2fsift_5fmatches_2eproto() {
  delete FeatureKnnProto::default_instance_;
  delete FeatureKnnProto_reflection_;
  delete FeatureMatchProto::default_instance_;
  delete FeatureMatchProto_reflection_;
  delete ImagePairMatchProto::default_instance_;
  delete ImagePairMatchProto_reflection_;
}

void protobuf_AddDesc_experiments_2fsift_5fmatches_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\036experiments/sift_matches.proto\"F\n\017Feat"
    "ureKnnProto\022\022\n\nfeature_id\030\002 \001(\r\022\020\n\010dista"
    "nce\030\004 \001(\002\022\r\n\005scale\030\005 \001(\002\"[\n\021FeatureMatch"
    "Proto\022\022\n\nfeature_id\030\001 \001(\r\022\r\n\005scale\030\002 \001(\002"
    "\022#\n\tknn_match\030\003 \003(\0132\020.FeatureKnnProto\"f\n"
    "\023ImagePairMatchProto\022\021\n\timage1_id\030\001 \001(\r\022"
    "\021\n\timage2_id\030\002 \001(\r\022)\n\rfeature_match\030\003 \003("
    "\0132\022.FeatureMatchProto", 301);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "experiments/sift_matches.proto", &protobuf_RegisterTypes);
  FeatureKnnProto::default_instance_ = new FeatureKnnProto();
  FeatureMatchProto::default_instance_ = new FeatureMatchProto();
  ImagePairMatchProto::default_instance_ = new ImagePairMatchProto();
  FeatureKnnProto::default_instance_->InitAsDefaultInstance();
  FeatureMatchProto::default_instance_->InitAsDefaultInstance();
  ImagePairMatchProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_experiments_2fsift_5fmatches_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_experiments_2fsift_5fmatches_2eproto {
  StaticDescriptorInitializer_experiments_2fsift_5fmatches_2eproto() {
    protobuf_AddDesc_experiments_2fsift_5fmatches_2eproto();
  }
} static_descriptor_initializer_experiments_2fsift_5fmatches_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int FeatureKnnProto::kFeatureIdFieldNumber;
const int FeatureKnnProto::kDistanceFieldNumber;
const int FeatureKnnProto::kScaleFieldNumber;
#endif  // !_MSC_VER

FeatureKnnProto::FeatureKnnProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FeatureKnnProto::InitAsDefaultInstance() {
}

FeatureKnnProto::FeatureKnnProto(const FeatureKnnProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FeatureKnnProto::SharedCtor() {
  _cached_size_ = 0;
  feature_id_ = 0u;
  distance_ = 0;
  scale_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FeatureKnnProto::~FeatureKnnProto() {
  SharedDtor();
}

void FeatureKnnProto::SharedDtor() {
  if (this != default_instance_) {
  }
}

void FeatureKnnProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FeatureKnnProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FeatureKnnProto_descriptor_;
}

const FeatureKnnProto& FeatureKnnProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_experiments_2fsift_5fmatches_2eproto();
  return *default_instance_;
}

FeatureKnnProto* FeatureKnnProto::default_instance_ = NULL;

FeatureKnnProto* FeatureKnnProto::New() const {
  return new FeatureKnnProto;
}

void FeatureKnnProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    feature_id_ = 0u;
    distance_ = 0;
    scale_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FeatureKnnProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 feature_id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &feature_id_)));
          set_has_feature_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(37)) goto parse_distance;
        break;
      }

      // optional float distance = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_distance:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &distance_)));
          set_has_distance();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(45)) goto parse_scale;
        break;
      }

      // optional float scale = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_scale:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &scale_)));
          set_has_scale();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FeatureKnnProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 feature_id = 2;
  if (has_feature_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->feature_id(), output);
  }

  // optional float distance = 4;
  if (has_distance()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(4, this->distance(), output);
  }

  // optional float scale = 5;
  if (has_scale()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(5, this->scale(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FeatureKnnProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 feature_id = 2;
  if (has_feature_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->feature_id(), target);
  }

  // optional float distance = 4;
  if (has_distance()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(4, this->distance(), target);
  }

  // optional float scale = 5;
  if (has_scale()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(5, this->scale(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FeatureKnnProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 feature_id = 2;
    if (has_feature_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->feature_id());
    }

    // optional float distance = 4;
    if (has_distance()) {
      total_size += 1 + 4;
    }

    // optional float scale = 5;
    if (has_scale()) {
      total_size += 1 + 4;
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FeatureKnnProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FeatureKnnProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FeatureKnnProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FeatureKnnProto::MergeFrom(const FeatureKnnProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_feature_id()) {
      set_feature_id(from.feature_id());
    }
    if (from.has_distance()) {
      set_distance(from.distance());
    }
    if (from.has_scale()) {
      set_scale(from.scale());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FeatureKnnProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FeatureKnnProto::CopyFrom(const FeatureKnnProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FeatureKnnProto::IsInitialized() const {

  return true;
}

void FeatureKnnProto::Swap(FeatureKnnProto* other) {
  if (other != this) {
    std::swap(feature_id_, other->feature_id_);
    std::swap(distance_, other->distance_);
    std::swap(scale_, other->scale_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FeatureKnnProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FeatureKnnProto_descriptor_;
  metadata.reflection = FeatureKnnProto_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int FeatureMatchProto::kFeatureIdFieldNumber;
const int FeatureMatchProto::kScaleFieldNumber;
const int FeatureMatchProto::kKnnMatchFieldNumber;
#endif  // !_MSC_VER

FeatureMatchProto::FeatureMatchProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FeatureMatchProto::InitAsDefaultInstance() {
}

FeatureMatchProto::FeatureMatchProto(const FeatureMatchProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FeatureMatchProto::SharedCtor() {
  _cached_size_ = 0;
  feature_id_ = 0u;
  scale_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FeatureMatchProto::~FeatureMatchProto() {
  SharedDtor();
}

void FeatureMatchProto::SharedDtor() {
  if (this != default_instance_) {
  }
}

void FeatureMatchProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FeatureMatchProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FeatureMatchProto_descriptor_;
}

const FeatureMatchProto& FeatureMatchProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_experiments_2fsift_5fmatches_2eproto();
  return *default_instance_;
}

FeatureMatchProto* FeatureMatchProto::default_instance_ = NULL;

FeatureMatchProto* FeatureMatchProto::New() const {
  return new FeatureMatchProto;
}

void FeatureMatchProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    feature_id_ = 0u;
    scale_ = 0;
  }
  knn_match_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FeatureMatchProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 feature_id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &feature_id_)));
          set_has_feature_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(21)) goto parse_scale;
        break;
      }

      // optional float scale = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED32) {
         parse_scale:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &scale_)));
          set_has_scale();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_knn_match;
        break;
      }

      // repeated .FeatureKnnProto knn_match = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_knn_match:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_knn_match()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_knn_match;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FeatureMatchProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 feature_id = 1;
  if (has_feature_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->feature_id(), output);
  }

  // optional float scale = 2;
  if (has_scale()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->scale(), output);
  }

  // repeated .FeatureKnnProto knn_match = 3;
  for (int i = 0; i < this->knn_match_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->knn_match(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FeatureMatchProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 feature_id = 1;
  if (has_feature_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->feature_id(), target);
  }

  // optional float scale = 2;
  if (has_scale()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->scale(), target);
  }

  // repeated .FeatureKnnProto knn_match = 3;
  for (int i = 0; i < this->knn_match_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->knn_match(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FeatureMatchProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 feature_id = 1;
    if (has_feature_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->feature_id());
    }

    // optional float scale = 2;
    if (has_scale()) {
      total_size += 1 + 4;
    }

  }
  // repeated .FeatureKnnProto knn_match = 3;
  total_size += 1 * this->knn_match_size();
  for (int i = 0; i < this->knn_match_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->knn_match(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FeatureMatchProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FeatureMatchProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FeatureMatchProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FeatureMatchProto::MergeFrom(const FeatureMatchProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  knn_match_.MergeFrom(from.knn_match_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_feature_id()) {
      set_feature_id(from.feature_id());
    }
    if (from.has_scale()) {
      set_scale(from.scale());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FeatureMatchProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FeatureMatchProto::CopyFrom(const FeatureMatchProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FeatureMatchProto::IsInitialized() const {

  return true;
}

void FeatureMatchProto::Swap(FeatureMatchProto* other) {
  if (other != this) {
    std::swap(feature_id_, other->feature_id_);
    std::swap(scale_, other->scale_);
    knn_match_.Swap(&other->knn_match_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FeatureMatchProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FeatureMatchProto_descriptor_;
  metadata.reflection = FeatureMatchProto_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int ImagePairMatchProto::kImage1IdFieldNumber;
const int ImagePairMatchProto::kImage2IdFieldNumber;
const int ImagePairMatchProto::kFeatureMatchFieldNumber;
#endif  // !_MSC_VER

ImagePairMatchProto::ImagePairMatchProto()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ImagePairMatchProto::InitAsDefaultInstance() {
}

ImagePairMatchProto::ImagePairMatchProto(const ImagePairMatchProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ImagePairMatchProto::SharedCtor() {
  _cached_size_ = 0;
  image1_id_ = 0u;
  image2_id_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ImagePairMatchProto::~ImagePairMatchProto() {
  SharedDtor();
}

void ImagePairMatchProto::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ImagePairMatchProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ImagePairMatchProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ImagePairMatchProto_descriptor_;
}

const ImagePairMatchProto& ImagePairMatchProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_experiments_2fsift_5fmatches_2eproto();
  return *default_instance_;
}

ImagePairMatchProto* ImagePairMatchProto::default_instance_ = NULL;

ImagePairMatchProto* ImagePairMatchProto::New() const {
  return new ImagePairMatchProto;
}

void ImagePairMatchProto::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    image1_id_ = 0u;
    image2_id_ = 0u;
  }
  feature_match_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ImagePairMatchProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 image1_id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &image1_id_)));
          set_has_image1_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_image2_id;
        break;
      }

      // optional uint32 image2_id = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_image2_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &image2_id_)));
          set_has_image2_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_feature_match;
        break;
      }

      // repeated .FeatureMatchProto feature_match = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_feature_match:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_feature_match()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_feature_match;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ImagePairMatchProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 image1_id = 1;
  if (has_image1_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->image1_id(), output);
  }

  // optional uint32 image2_id = 2;
  if (has_image2_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->image2_id(), output);
  }

  // repeated .FeatureMatchProto feature_match = 3;
  for (int i = 0; i < this->feature_match_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->feature_match(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ImagePairMatchProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 image1_id = 1;
  if (has_image1_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->image1_id(), target);
  }

  // optional uint32 image2_id = 2;
  if (has_image2_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->image2_id(), target);
  }

  // repeated .FeatureMatchProto feature_match = 3;
  for (int i = 0; i < this->feature_match_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->feature_match(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ImagePairMatchProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 image1_id = 1;
    if (has_image1_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->image1_id());
    }

    // optional uint32 image2_id = 2;
    if (has_image2_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->image2_id());
    }

  }
  // repeated .FeatureMatchProto feature_match = 3;
  total_size += 1 * this->feature_match_size();
  for (int i = 0; i < this->feature_match_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->feature_match(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ImagePairMatchProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ImagePairMatchProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ImagePairMatchProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ImagePairMatchProto::MergeFrom(const ImagePairMatchProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  feature_match_.MergeFrom(from.feature_match_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_image1_id()) {
      set_image1_id(from.image1_id());
    }
    if (from.has_image2_id()) {
      set_image2_id(from.image2_id());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ImagePairMatchProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ImagePairMatchProto::CopyFrom(const ImagePairMatchProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ImagePairMatchProto::IsInitialized() const {

  return true;
}

void ImagePairMatchProto::Swap(ImagePairMatchProto* other) {
  if (other != this) {
    std::swap(image1_id_, other->image1_id_);
    std::swap(image2_id_, other->image2_id_);
    feature_match_.Swap(&other->feature_match_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ImagePairMatchProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ImagePairMatchProto_descriptor_;
  metadata.reflection = ImagePairMatchProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
