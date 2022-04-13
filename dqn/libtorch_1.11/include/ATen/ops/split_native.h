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

TORCH_API ::std::vector<at::Tensor> split(const at::Tensor & self, int64_t split_size, int64_t dim=0);
TORCH_API ::std::vector<at::Tensor> split(const at::Tensor & self, at::IntArrayRef split_size, int64_t dim=0);

} // namespace native
} // namespace at
