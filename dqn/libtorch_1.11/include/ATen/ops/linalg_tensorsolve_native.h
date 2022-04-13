#pragma once

// @generated by tools/codegen/gen.py from NativeFunction.h

#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <c10/util/Optional.h>
#include <c10/core/QScheme.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <tuple>
#include <vector>


namespace at {
namespace native {

TORCH_API at::Tensor linalg_tensorsolve(const at::Tensor & self, const at::Tensor & other, at::OptionalIntArrayRef dims=c10::nullopt);
TORCH_API at::Tensor & linalg_tensorsolve_out(const at::Tensor & self, const at::Tensor & other, at::OptionalIntArrayRef dims, at::Tensor & out);

} // namespace native
} // namespace at
