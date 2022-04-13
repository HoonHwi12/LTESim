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

TORCH_API at::Tensor kl_div_backward_cpu(const at::Tensor & grad_output, const at::Tensor & self, const at::Tensor & target, int64_t reduction=at::Reduction::Mean, bool log_target=false);
TORCH_API at::Tensor kl_div_backward_cuda(const at::Tensor & grad_output, const at::Tensor & self, const at::Tensor & target, int64_t reduction=at::Reduction::Mean, bool log_target=false);

} // namespace native
} // namespace at
