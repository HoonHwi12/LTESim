#pragma once

// @generated by tools/codegen/gen.py from Operator.h

#include <c10/core/QScheme.h>
#include <ATen/core/jit_type_base.h>
#include <tuple>
#include <vector>


// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
namespace c10 {

template<typename T>
class optional;
template<typename T>
class List;
class ITensorListRef;
class Stream;
class Scalar;
struct Storage;
struct TensorOptions;

}

namespace at {

class Tensor;
struct Dimname;
struct Generator;
using TensorList = c10::ArrayRef<Tensor>;
using ITensorListRef = c10::ITensorListRef;
using DimnameList = c10::ArrayRef<Dimname>;
using c10::Stream;
using c10::Storage;
using c10::QScheme;
using c10::Scalar;
using c10::TensorOptions;

namespace _ops {


struct TORCH_API bucketize_Tensor {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, bool, bool);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::bucketize")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "Tensor")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "bucketize.Tensor(Tensor self, Tensor boundaries, *, bool out_int32=False, bool right=False) -> Tensor")
  static at::Tensor call(const at::Tensor & self, const at::Tensor & boundaries, bool out_int32, bool right);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & boundaries, bool out_int32, bool right);
};

struct TORCH_API bucketize_Tensor_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, bool, bool, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::bucketize")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "Tensor_out")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "bucketize.Tensor_out(Tensor self, Tensor boundaries, *, bool out_int32=False, bool right=False, Tensor(a!) out) -> Tensor(a!)")
  static at::Tensor & call(const at::Tensor & self, const at::Tensor & boundaries, bool out_int32, bool right, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & boundaries, bool out_int32, bool right, at::Tensor & out);
};

struct TORCH_API bucketize_Scalar {
  using schema = at::Tensor (const at::Scalar &, const at::Tensor &, bool, bool);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::bucketize")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "Scalar")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "bucketize.Scalar(Scalar self, Tensor boundaries, *, bool out_int32=False, bool right=False) -> Tensor")
  static at::Tensor call(const at::Scalar & self, const at::Tensor & boundaries, bool out_int32, bool right);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Scalar & self, const at::Tensor & boundaries, bool out_int32, bool right);
};

}} // namespace at::_ops
