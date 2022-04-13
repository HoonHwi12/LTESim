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


struct TORCH_API elu_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Scalar &, const at::Scalar &, const at::Scalar &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::elu")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "out")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "elu.out(Tensor self, Scalar alpha=1, Scalar scale=1, Scalar input_scale=1, *, Tensor(a!) out) -> Tensor(a!)")
  static at::Tensor & call(const at::Tensor & self, const at::Scalar & alpha, const at::Scalar & scale, const at::Scalar & input_scale, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Scalar & alpha, const at::Scalar & scale, const at::Scalar & input_scale, at::Tensor & out);
};

struct TORCH_API elu {
  using schema = at::Tensor (const at::Tensor &, const at::Scalar &, const at::Scalar &, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::elu")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "elu(Tensor self, Scalar alpha=1, Scalar scale=1, Scalar input_scale=1) -> Tensor")
  static at::Tensor call(const at::Tensor & self, const at::Scalar & alpha, const at::Scalar & scale, const at::Scalar & input_scale);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Scalar & alpha, const at::Scalar & scale, const at::Scalar & input_scale);
};

struct TORCH_API elu_ {
  using schema = at::Tensor & (at::Tensor &, const at::Scalar &, const at::Scalar &, const at::Scalar &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::elu_")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "elu_(Tensor(a!) self, Scalar alpha=1, Scalar scale=1, Scalar input_scale=1) -> Tensor(a!)")
  static at::Tensor & call(at::Tensor & self, const at::Scalar & alpha, const at::Scalar & scale, const at::Scalar & input_scale);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::Tensor & self, const at::Scalar & alpha, const at::Scalar & scale, const at::Scalar & input_scale);
};

}} // namespace at::_ops
