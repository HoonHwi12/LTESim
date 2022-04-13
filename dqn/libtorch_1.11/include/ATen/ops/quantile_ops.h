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


struct TORCH_API quantile {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, c10::optional<int64_t>, bool, c10::string_view);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::quantile")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "quantile(Tensor self, Tensor q, int? dim=None, bool keepdim=False, *, str interpolation='linear') -> Tensor")
  static at::Tensor call(const at::Tensor & self, const at::Tensor & q, c10::optional<int64_t> dim, bool keepdim, c10::string_view interpolation);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & q, c10::optional<int64_t> dim, bool keepdim, c10::string_view interpolation);
};

struct TORCH_API quantile_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, c10::optional<int64_t>, bool, c10::string_view, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::quantile")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "out")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "quantile.out(Tensor self, Tensor q, int? dim=None, bool keepdim=False, *, str interpolation='linear', Tensor(a!) out) -> Tensor(a!)")
  static at::Tensor & call(const at::Tensor & self, const at::Tensor & q, c10::optional<int64_t> dim, bool keepdim, c10::string_view interpolation, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, const at::Tensor & q, c10::optional<int64_t> dim, bool keepdim, c10::string_view interpolation, at::Tensor & out);
};

struct TORCH_API quantile_scalar {
  using schema = at::Tensor (const at::Tensor &, double, c10::optional<int64_t>, bool, c10::string_view);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::quantile")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "scalar")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "quantile.scalar(Tensor self, float q, int? dim=None, bool keepdim=False, *, str interpolation='linear') -> Tensor")
  static at::Tensor call(const at::Tensor & self, double q, c10::optional<int64_t> dim, bool keepdim, c10::string_view interpolation);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, double q, c10::optional<int64_t> dim, bool keepdim, c10::string_view interpolation);
};

struct TORCH_API quantile_scalar_out {
  using schema = at::Tensor & (const at::Tensor &, double, c10::optional<int64_t>, bool, c10::string_view, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::quantile")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "scalar_out")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "quantile.scalar_out(Tensor self, float q, int? dim=None, bool keepdim=False, *, str interpolation='linear', Tensor(a!) out) -> Tensor(a!)")
  static at::Tensor & call(const at::Tensor & self, double q, c10::optional<int64_t> dim, bool keepdim, c10::string_view interpolation, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, double q, c10::optional<int64_t> dim, bool keepdim, c10::string_view interpolation, at::Tensor & out);
};

}} // namespace at::_ops
