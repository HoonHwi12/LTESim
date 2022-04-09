#pragma once

// @generated by tools/codegen/gen.py from Function.h

#include <ATen/Context.h>
#include <ATen/DeviceGuard.h>
#include <ATen/TensorUtils.h>
#include <ATen/TracerMode.h>
#include <ATen/core/Generator.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <c10/util/Optional.h>



#include <ATen/ops/masked_fill_ops.h>

namespace at {


// aten::masked_fill.Scalar(Tensor self, Tensor mask, Scalar value) -> Tensor
TORCH_API inline at::Tensor masked_fill(const at::Tensor & self, const at::Tensor & mask, const at::Scalar & value) {
    return at::_ops::masked_fill_Scalar::call(self, mask, value);
}

// aten::masked_fill.Tensor(Tensor self, Tensor mask, Tensor value) -> Tensor
TORCH_API inline at::Tensor masked_fill(const at::Tensor & self, const at::Tensor & mask, const at::Tensor & value) {
    return at::_ops::masked_fill_Tensor::call(self, mask, value);
}

}
