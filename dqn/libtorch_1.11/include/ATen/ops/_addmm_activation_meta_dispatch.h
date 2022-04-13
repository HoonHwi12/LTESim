#pragma once
// @generated by tools/codegen/gen.py from DispatchKeyFunction.h

// NB: The implementing C++ file is RegisterDispatchKey.cpp

// The only #includes we need are for custom classes that have defaults in the C++ API
#include <c10/core/MemoryFormat.h>
#include <c10/core/Scalar.h>
#include <ATen/core/Reduction.h>

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

namespace meta {

TORCH_API at::Tensor _addmm_activation(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta=1, const at::Scalar & alpha=1, bool use_gelu=false);
TORCH_API at::Tensor & _addmm_activation_out(at::Tensor & out, const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta=1, const at::Scalar & alpha=1, bool use_gelu=false);
TORCH_API at::Tensor & _addmm_activation_outf(const at::Tensor & self, const at::Tensor & mat1, const at::Tensor & mat2, const at::Scalar & beta, const at::Scalar & alpha, bool use_gelu, at::Tensor & out);

} // namespace meta
} // namespace at
