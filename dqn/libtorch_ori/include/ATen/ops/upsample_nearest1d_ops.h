#pragma once

// @generated by tools/codegen/gen.py from Operator.h

#include <c10/core/QScheme.h>
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
using DimnameList = c10::ArrayRef<Dimname>;
using c10::Stream;
using c10::Storage;
using c10::QScheme;
using c10::Scalar;
using c10::TensorOptions;

namespace _ops {


struct TORCH_API upsample_nearest1d_vec {
  using schema = at::Tensor (const at::Tensor &, c10::optional<at::IntArrayRef>, c10::optional<at::ArrayRef<double>>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::upsample_nearest1d")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "vec")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "upsample_nearest1d.vec(Tensor input, int[]? output_size, float[]? scale_factors) -> Tensor")
  static at::Tensor call(const at::Tensor & input, c10::optional<at::IntArrayRef> output_size, c10::optional<at::ArrayRef<double>> scale_factors);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & input, c10::optional<at::IntArrayRef> output_size, c10::optional<at::ArrayRef<double>> scale_factors);
};

struct TORCH_API upsample_nearest1d_out {
  using schema = at::Tensor & (const at::Tensor &, at::IntArrayRef, c10::optional<double>, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::upsample_nearest1d")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "out")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "upsample_nearest1d.out(Tensor self, int[1] output_size, float? scales=None, *, Tensor(a!) out) -> Tensor(a!)")
  static at::Tensor & call(const at::Tensor & self, at::IntArrayRef output_size, c10::optional<double> scales, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::IntArrayRef output_size, c10::optional<double> scales, at::Tensor & out);
};

struct TORCH_API upsample_nearest1d {
  using schema = at::Tensor (const at::Tensor &, at::IntArrayRef, c10::optional<double>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::upsample_nearest1d")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "upsample_nearest1d(Tensor self, int[1] output_size, float? scales=None) -> Tensor")
  static at::Tensor call(const at::Tensor & self, at::IntArrayRef output_size, c10::optional<double> scales);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::IntArrayRef output_size, c10::optional<double> scales);
};

}} // namespace at::_ops
