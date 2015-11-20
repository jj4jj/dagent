// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: dagent.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "dagent.pb.h"

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

namespace dagent {

namespace {

const ::google::protobuf::Descriptor* MsgDAgent_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MsgDAgent_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_dagent_2eproto() {
  protobuf_AddDesc_dagent_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "dagent.proto");
  GOOGLE_CHECK(file != NULL);
  MsgDAgent_descriptor_ = file->message_type(0);
  static const int MsgDAgent_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgDAgent, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgDAgent, msg_data_),
  };
  MsgDAgent_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MsgDAgent_descriptor_,
      MsgDAgent::default_instance_,
      MsgDAgent_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgDAgent, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgDAgent, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MsgDAgent));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_dagent_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MsgDAgent_descriptor_, &MsgDAgent::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_dagent_2eproto() {
  delete MsgDAgent::default_instance_;
  delete MsgDAgent_reflection_;
}

void protobuf_AddDesc_dagent_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014dagent.proto\022\006dagent\"+\n\tMsgDAgent\022\014\n\004t"
    "ype\030\001 \002(\005\022\020\n\010msg_data\030\002 \001(\014", 67);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "dagent.proto", &protobuf_RegisterTypes);
  MsgDAgent::default_instance_ = new MsgDAgent();
  MsgDAgent::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_dagent_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_dagent_2eproto {
  StaticDescriptorInitializer_dagent_2eproto() {
    protobuf_AddDesc_dagent_2eproto();
  }
} static_descriptor_initializer_dagent_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int MsgDAgent::kTypeFieldNumber;
const int MsgDAgent::kMsgDataFieldNumber;
#endif  // !_MSC_VER

MsgDAgent::MsgDAgent()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:dagent.MsgDAgent)
}

void MsgDAgent::InitAsDefaultInstance() {
}

MsgDAgent::MsgDAgent(const MsgDAgent& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:dagent.MsgDAgent)
}

void MsgDAgent::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  type_ = 0;
  msg_data_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MsgDAgent::~MsgDAgent() {
  // @@protoc_insertion_point(destructor:dagent.MsgDAgent)
  SharedDtor();
}

void MsgDAgent::SharedDtor() {
  if (msg_data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete msg_data_;
  }
  if (this != default_instance_) {
  }
}

void MsgDAgent::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MsgDAgent::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MsgDAgent_descriptor_;
}

const MsgDAgent& MsgDAgent::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_dagent_2eproto();
  return *default_instance_;
}

MsgDAgent* MsgDAgent::default_instance_ = NULL;

MsgDAgent* MsgDAgent::New() const {
  return new MsgDAgent;
}

void MsgDAgent::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    type_ = 0;
    if (has_msg_data()) {
      if (msg_data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        msg_data_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MsgDAgent::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:dagent.MsgDAgent)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 type = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
          set_has_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_msg_data;
        break;
      }

      // optional bytes msg_data = 2;
      case 2: {
        if (tag == 18) {
         parse_msg_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_msg_data()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:dagent.MsgDAgent)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:dagent.MsgDAgent)
  return false;
#undef DO_
}

void MsgDAgent::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:dagent.MsgDAgent)
  // required int32 type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->type(), output);
  }

  // optional bytes msg_data = 2;
  if (has_msg_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->msg_data(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:dagent.MsgDAgent)
}

::google::protobuf::uint8* MsgDAgent::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:dagent.MsgDAgent)
  // required int32 type = 1;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->type(), target);
  }

  // optional bytes msg_data = 2;
  if (has_msg_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->msg_data(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:dagent.MsgDAgent)
  return target;
}

int MsgDAgent::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->type());
    }

    // optional bytes msg_data = 2;
    if (has_msg_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->msg_data());
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

void MsgDAgent::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MsgDAgent* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MsgDAgent*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MsgDAgent::MergeFrom(const MsgDAgent& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_msg_data()) {
      set_msg_data(from.msg_data());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MsgDAgent::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MsgDAgent::CopyFrom(const MsgDAgent& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MsgDAgent::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void MsgDAgent::Swap(MsgDAgent* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(msg_data_, other->msg_data_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MsgDAgent::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MsgDAgent_descriptor_;
  metadata.reflection = MsgDAgent_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace dagent

// @@protoc_insertion_point(global_scope)
