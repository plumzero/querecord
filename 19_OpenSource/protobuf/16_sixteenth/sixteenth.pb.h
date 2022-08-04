// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sixteenth.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_sixteenth_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_sixteenth_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3013000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3013000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_sixteenth_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_sixteenth_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_sixteenth_2eproto;
namespace mam {
class OrderMatchResult;
class OrderMatchResultDefaultTypeInternal;
extern OrderMatchResultDefaultTypeInternal _OrderMatchResult_default_instance_;
}  // namespace mam
PROTOBUF_NAMESPACE_OPEN
template<> ::mam::OrderMatchResult* Arena::CreateMaybeMessage<::mam::OrderMatchResult>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace mam {

// ===================================================================

class OrderMatchResult PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:mam.OrderMatchResult) */ {
 public:
  inline OrderMatchResult() : OrderMatchResult(nullptr) {}
  virtual ~OrderMatchResult();

  OrderMatchResult(const OrderMatchResult& from);
  OrderMatchResult(OrderMatchResult&& from) noexcept
    : OrderMatchResult() {
    *this = ::std::move(from);
  }

  inline OrderMatchResult& operator=(const OrderMatchResult& from) {
    CopyFrom(from);
    return *this;
  }
  inline OrderMatchResult& operator=(OrderMatchResult&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const OrderMatchResult& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const OrderMatchResult* internal_default_instance() {
    return reinterpret_cast<const OrderMatchResult*>(
               &_OrderMatchResult_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(OrderMatchResult& a, OrderMatchResult& b) {
    a.Swap(&b);
  }
  inline void Swap(OrderMatchResult* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(OrderMatchResult* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline OrderMatchResult* New() const final {
    return CreateMaybeMessage<OrderMatchResult>(nullptr);
  }

  OrderMatchResult* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<OrderMatchResult>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const OrderMatchResult& from);
  void MergeFrom(const OrderMatchResult& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(OrderMatchResult* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "mam.OrderMatchResult";
  }
  protected:
  explicit OrderMatchResult(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_sixteenth_2eproto);
    return ::descriptor_table_sixteenth_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kOrderIdFieldNumber = 2,
    kReqIdFieldNumber = 1,
    kDealPriceFieldNumber = 3,
    kDealVolumeFieldNumber = 4,
  };
  // string orderId = 2;
  void clear_orderid();
  const std::string& orderid() const;
  void set_orderid(const std::string& value);
  void set_orderid(std::string&& value);
  void set_orderid(const char* value);
  void set_orderid(const char* value, size_t size);
  std::string* mutable_orderid();
  std::string* release_orderid();
  void set_allocated_orderid(std::string* orderid);
  private:
  const std::string& _internal_orderid() const;
  void _internal_set_orderid(const std::string& value);
  std::string* _internal_mutable_orderid();
  public:

  // int32 reqId = 1;
  void clear_reqid();
  ::PROTOBUF_NAMESPACE_ID::int32 reqid() const;
  void set_reqid(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_reqid() const;
  void _internal_set_reqid(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 dealPrice = 3;
  void clear_dealprice();
  ::PROTOBUF_NAMESPACE_ID::int32 dealprice() const;
  void set_dealprice(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_dealprice() const;
  void _internal_set_dealprice(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 dealVolume = 4;
  void clear_dealvolume();
  ::PROTOBUF_NAMESPACE_ID::int32 dealvolume() const;
  void set_dealvolume(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_dealvolume() const;
  void _internal_set_dealvolume(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:mam.OrderMatchResult)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr orderid_;
  ::PROTOBUF_NAMESPACE_ID::int32 reqid_;
  ::PROTOBUF_NAMESPACE_ID::int32 dealprice_;
  ::PROTOBUF_NAMESPACE_ID::int32 dealvolume_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_sixteenth_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// OrderMatchResult

// int32 reqId = 1;
inline void OrderMatchResult::clear_reqid() {
  reqid_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 OrderMatchResult::_internal_reqid() const {
  return reqid_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 OrderMatchResult::reqid() const {
  // @@protoc_insertion_point(field_get:mam.OrderMatchResult.reqId)
  return _internal_reqid();
}
inline void OrderMatchResult::_internal_set_reqid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  reqid_ = value;
}
inline void OrderMatchResult::set_reqid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_reqid(value);
  // @@protoc_insertion_point(field_set:mam.OrderMatchResult.reqId)
}

// string orderId = 2;
inline void OrderMatchResult::clear_orderid() {
  orderid_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline const std::string& OrderMatchResult::orderid() const {
  // @@protoc_insertion_point(field_get:mam.OrderMatchResult.orderId)
  return _internal_orderid();
}
inline void OrderMatchResult::set_orderid(const std::string& value) {
  _internal_set_orderid(value);
  // @@protoc_insertion_point(field_set:mam.OrderMatchResult.orderId)
}
inline std::string* OrderMatchResult::mutable_orderid() {
  // @@protoc_insertion_point(field_mutable:mam.OrderMatchResult.orderId)
  return _internal_mutable_orderid();
}
inline const std::string& OrderMatchResult::_internal_orderid() const {
  return orderid_.Get();
}
inline void OrderMatchResult::_internal_set_orderid(const std::string& value) {
  
  orderid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void OrderMatchResult::set_orderid(std::string&& value) {
  
  orderid_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:mam.OrderMatchResult.orderId)
}
inline void OrderMatchResult::set_orderid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  orderid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:mam.OrderMatchResult.orderId)
}
inline void OrderMatchResult::set_orderid(const char* value,
    size_t size) {
  
  orderid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:mam.OrderMatchResult.orderId)
}
inline std::string* OrderMatchResult::_internal_mutable_orderid() {
  
  return orderid_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* OrderMatchResult::release_orderid() {
  // @@protoc_insertion_point(field_release:mam.OrderMatchResult.orderId)
  return orderid_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void OrderMatchResult::set_allocated_orderid(std::string* orderid) {
  if (orderid != nullptr) {
    
  } else {
    
  }
  orderid_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), orderid,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:mam.OrderMatchResult.orderId)
}

// int32 dealPrice = 3;
inline void OrderMatchResult::clear_dealprice() {
  dealprice_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 OrderMatchResult::_internal_dealprice() const {
  return dealprice_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 OrderMatchResult::dealprice() const {
  // @@protoc_insertion_point(field_get:mam.OrderMatchResult.dealPrice)
  return _internal_dealprice();
}
inline void OrderMatchResult::_internal_set_dealprice(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  dealprice_ = value;
}
inline void OrderMatchResult::set_dealprice(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_dealprice(value);
  // @@protoc_insertion_point(field_set:mam.OrderMatchResult.dealPrice)
}

// int32 dealVolume = 4;
inline void OrderMatchResult::clear_dealvolume() {
  dealvolume_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 OrderMatchResult::_internal_dealvolume() const {
  return dealvolume_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 OrderMatchResult::dealvolume() const {
  // @@protoc_insertion_point(field_get:mam.OrderMatchResult.dealVolume)
  return _internal_dealvolume();
}
inline void OrderMatchResult::_internal_set_dealvolume(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  dealvolume_ = value;
}
inline void OrderMatchResult::set_dealvolume(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_dealvolume(value);
  // @@protoc_insertion_point(field_set:mam.OrderMatchResult.dealVolume)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace mam

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_sixteenth_2eproto
