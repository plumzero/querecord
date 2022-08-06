// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sixteenth.proto

#include "sixteenth.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace mam {
class OrderMatchResultDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<OrderMatchResult> _instance;
} _OrderMatchResult_default_instance_;
}  // namespace mam
static void InitDefaultsscc_info_OrderMatchResult_sixteenth_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::mam::_OrderMatchResult_default_instance_;
    new (ptr) ::mam::OrderMatchResult();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::mam::OrderMatchResult::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_OrderMatchResult_sixteenth_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_OrderMatchResult_sixteenth_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_sixteenth_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_sixteenth_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_sixteenth_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_sixteenth_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mam::OrderMatchResult, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::mam::OrderMatchResult, reqid_),
  PROTOBUF_FIELD_OFFSET(::mam::OrderMatchResult, orderid_),
  PROTOBUF_FIELD_OFFSET(::mam::OrderMatchResult, dealprice_),
  PROTOBUF_FIELD_OFFSET(::mam::OrderMatchResult, dealvolume_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::mam::OrderMatchResult)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mam::_OrderMatchResult_default_instance_),
};

const char descriptor_table_protodef_sixteenth_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017sixteenth.proto\022\003mam\"Y\n\020OrderMatchResu"
  "lt\022\r\n\005reqId\030\001 \001(\005\022\017\n\007orderId\030\002 \001(\t\022\021\n\tde"
  "alPrice\030\003 \001(\005\022\022\n\ndealVolume\030\004 \001(\005b\006proto"
  "3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_sixteenth_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_sixteenth_2eproto_sccs[1] = {
  &scc_info_OrderMatchResult_sixteenth_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_sixteenth_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_sixteenth_2eproto = {
  false, false, descriptor_table_protodef_sixteenth_2eproto, "sixteenth.proto", 121,
  &descriptor_table_sixteenth_2eproto_once, descriptor_table_sixteenth_2eproto_sccs, descriptor_table_sixteenth_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_sixteenth_2eproto::offsets,
  file_level_metadata_sixteenth_2eproto, 1, file_level_enum_descriptors_sixteenth_2eproto, file_level_service_descriptors_sixteenth_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_sixteenth_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_sixteenth_2eproto)), true);
namespace mam {

// ===================================================================

void OrderMatchResult::InitAsDefaultInstance() {
}
class OrderMatchResult::_Internal {
 public:
};

OrderMatchResult::OrderMatchResult(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:mam.OrderMatchResult)
}
OrderMatchResult::OrderMatchResult(const OrderMatchResult& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  orderid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_orderid().empty()) {
    orderid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_orderid(),
      GetArena());
  }
  ::memcpy(&reqid_, &from.reqid_,
    static_cast<size_t>(reinterpret_cast<char*>(&dealvolume_) -
    reinterpret_cast<char*>(&reqid_)) + sizeof(dealvolume_));
  // @@protoc_insertion_point(copy_constructor:mam.OrderMatchResult)
}

void OrderMatchResult::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_OrderMatchResult_sixteenth_2eproto.base);
  orderid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&reqid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&dealvolume_) -
      reinterpret_cast<char*>(&reqid_)) + sizeof(dealvolume_));
}

OrderMatchResult::~OrderMatchResult() {
  // @@protoc_insertion_point(destructor:mam.OrderMatchResult)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void OrderMatchResult::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  orderid_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void OrderMatchResult::ArenaDtor(void* object) {
  OrderMatchResult* _this = reinterpret_cast< OrderMatchResult* >(object);
  (void)_this;
}
void OrderMatchResult::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void OrderMatchResult::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const OrderMatchResult& OrderMatchResult::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_OrderMatchResult_sixteenth_2eproto.base);
  return *internal_default_instance();
}


void OrderMatchResult::Clear() {
// @@protoc_insertion_point(message_clear_start:mam.OrderMatchResult)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  orderid_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::memset(&reqid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&dealvolume_) -
      reinterpret_cast<char*>(&reqid_)) + sizeof(dealvolume_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* OrderMatchResult::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 reqId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          reqid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string orderId = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_orderid();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "mam.OrderMatchResult.orderId"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 dealPrice = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          dealprice_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 dealVolume = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          dealvolume_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* OrderMatchResult::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mam.OrderMatchResult)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 reqId = 1;
  if (this->reqid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_reqid(), target);
  }

  // string orderId = 2;
  if (this->orderid().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_orderid().data(), static_cast<int>(this->_internal_orderid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mam.OrderMatchResult.orderId");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_orderid(), target);
  }

  // int32 dealPrice = 3;
  if (this->dealprice() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_dealprice(), target);
  }

  // int32 dealVolume = 4;
  if (this->dealvolume() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_dealvolume(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mam.OrderMatchResult)
  return target;
}

size_t OrderMatchResult::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mam.OrderMatchResult)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string orderId = 2;
  if (this->orderid().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_orderid());
  }

  // int32 reqId = 1;
  if (this->reqid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_reqid());
  }

  // int32 dealPrice = 3;
  if (this->dealprice() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_dealprice());
  }

  // int32 dealVolume = 4;
  if (this->dealvolume() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_dealvolume());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void OrderMatchResult::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:mam.OrderMatchResult)
  GOOGLE_DCHECK_NE(&from, this);
  const OrderMatchResult* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<OrderMatchResult>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:mam.OrderMatchResult)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:mam.OrderMatchResult)
    MergeFrom(*source);
  }
}

void OrderMatchResult::MergeFrom(const OrderMatchResult& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mam.OrderMatchResult)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.orderid().size() > 0) {
    _internal_set_orderid(from._internal_orderid());
  }
  if (from.reqid() != 0) {
    _internal_set_reqid(from._internal_reqid());
  }
  if (from.dealprice() != 0) {
    _internal_set_dealprice(from._internal_dealprice());
  }
  if (from.dealvolume() != 0) {
    _internal_set_dealvolume(from._internal_dealvolume());
  }
}

void OrderMatchResult::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:mam.OrderMatchResult)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void OrderMatchResult::CopyFrom(const OrderMatchResult& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mam.OrderMatchResult)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool OrderMatchResult::IsInitialized() const {
  return true;
}

void OrderMatchResult::InternalSwap(OrderMatchResult* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  orderid_.Swap(&other->orderid_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(OrderMatchResult, dealvolume_)
      + sizeof(OrderMatchResult::dealvolume_)
      - PROTOBUF_FIELD_OFFSET(OrderMatchResult, reqid_)>(
          reinterpret_cast<char*>(&reqid_),
          reinterpret_cast<char*>(&other->reqid_));
}

::PROTOBUF_NAMESPACE_ID::Metadata OrderMatchResult::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace mam
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mam::OrderMatchResult* Arena::CreateMaybeMessage< ::mam::OrderMatchResult >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mam::OrderMatchResult >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>