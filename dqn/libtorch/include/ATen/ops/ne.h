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



#include <ATen/ops/ne_ops.h>

namespace at {


// aten::ne.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & ne_out(at::Tensor & out, const at::Tensor & self, const at::Scalar & other) {
    return at::_ops::ne_Scalar_out::call(self, other, out);
}

// aten::ne.Scalar_out(Tensor self, Scalar other, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & ne_outf(const at::Tensor & self, const at::Scalar & other, at::Tensor & out) {
    return at::_ops::ne_Scalar_out::call(self, other, out);
}

// aten::ne.Scalar(Tensor self, Scalar other) -> Tensor
TORCH_API inline at::Tensor ne(const at::Tensor & self, const at::Scalar & other) {
    return at::_ops::ne_Scalar::call(self, other);
}

// aten::ne.Tensor_out(Tensor self, Tensor other, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & ne_out(at::Tensor & out, const at::Tensor & self, const at::Tensor & other) {
    return at::_ops::ne_Tensor_out::call(self, other, out);
}

// aten::ne.Tensor_out(Tensor self, Tensor other, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & ne_outf(const at::Tensor & self, const at::Tensor & other, at::Tensor & out) {
    return at::_ops::ne_Tensor_out::call(self, other, out);
}

// aten::ne.Tensor(Tensor self, Tensor other) -> Tensor
TORCH_API inline at::Tensor ne(const at::Tensor & self, const at::Tensor & other) {
    return at::_ops::ne_Tensor::call(self, other);
}

}
