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


struct TORCH_API batch_norm_backward_reduce {
  using schema = ::std::tuple<at::Tensor,at::Tensor,at::Tensor,at::Tensor> (const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const c10::optional<at::Tensor> &, bool, bool, bool);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(name, "aten::batch_norm_backward_reduce")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(overload_name, "")
  STATIC_CONSTEXPR_STR_INL_EXCEPT_WIN_CUDA(schema_str, "batch_norm_backward_reduce(Tensor grad_out, Tensor input, Tensor mean, Tensor invstd, Tensor? weight, bool input_g, bool weight_g, bool bias_g) -> (Tensor, Tensor, Tensor, Tensor)")
  static ::std::tuple<at::Tensor,at::Tensor,at::Tensor,at::Tensor> call(const at::Tensor & grad_out, const at::Tensor & input, const at::Tensor & mean, const at::Tensor & invstd, const c10::optional<at::Tensor> & weight, bool input_g, bool weight_g, bool bias_g);
  static ::std::tuple<at::Tensor,at::Tensor,at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & grad_out, const at::Tensor & input, const at::Tensor & mean, const at::Tensor & invstd, const c10::optional<at::Tensor> & weight, bool input_g, bool weight_g, bool bias_g);
};

}} // namespace at::_ops
