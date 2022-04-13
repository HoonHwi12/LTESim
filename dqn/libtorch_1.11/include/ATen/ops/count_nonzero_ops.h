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


struct TORCH_API count_nonzero_dim_IntList {
  using schema = at::Tensor (const at::Tensor &, at::IntArrayRef);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::count_nonzero")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "dim_IntList")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "count_nonzero.dim_IntList(Tensor self, int[] dim) -> Tensor")
  static at::Tensor call(const at::Tensor & self, at::IntArrayRef dim);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::IntArrayRef dim);
};

struct TORCH_API count_nonzero {
  using schema = at::Tensor (const at::Tensor &, c10::optional<int64_t>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::count_nonzero")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "count_nonzero(Tensor self, int? dim=None) -> Tensor")
  static at::Tensor call(const at::Tensor & self, c10::optional<int64_t> dim);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, c10::optional<int64_t> dim);
};

}} // namespace at::_ops
