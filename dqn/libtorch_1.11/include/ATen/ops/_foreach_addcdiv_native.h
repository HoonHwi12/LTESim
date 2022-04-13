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

TORCH_API void foreach_tensor_addcdiv_scalar_slow_(at::TensorList self, at::TensorList tensor1, at::TensorList tensor2, const at::Scalar & value=1);
TORCH_API void foreach_tensor_addcdiv_scalar_cuda_(at::TensorList self, at::TensorList tensor1, at::TensorList tensor2, const at::Scalar & value=1);
TORCH_API void foreach_tensor_addcdiv_scalarlist_slow_(at::TensorList self, at::TensorList tensor1, at::TensorList tensor2, at::ArrayRef<at::Scalar> scalars);
TORCH_API void foreach_tensor_addcdiv_scalarlist_cuda_(at::TensorList self, at::TensorList tensor1, at::TensorList tensor2, at::ArrayRef<at::Scalar> scalars);
TORCH_API ::std::vector<at::Tensor> foreach_tensor_addcdiv_scalar_slow(at::TensorList input, at::TensorList tensor1, at::TensorList tensor2, const at::Scalar & value=1);
TORCH_API ::std::vector<at::Tensor> foreach_tensor_addcdiv_scalar_cuda(at::TensorList input, at::TensorList tensor1, at::TensorList tensor2, const at::Scalar & value=1);
TORCH_API ::std::vector<at::Tensor> foreach_tensor_addcdiv_scalarlist_slow(at::TensorList input, at::TensorList tensor1, at::TensorList tensor2, at::ArrayRef<at::Scalar> scalars);
TORCH_API ::std::vector<at::Tensor> foreach_tensor_addcdiv_scalarlist_cuda(at::TensorList input, at::TensorList tensor1, at::TensorList tensor2, at::ArrayRef<at::Scalar> scalars);

} // namespace native
} // namespace at
