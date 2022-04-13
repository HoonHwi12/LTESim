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



#include <ATen/ops/silu_ops.h>

namespace at {


// aten::silu(Tensor self) -> Tensor
TORCH_API inline at::Tensor silu(const at::Tensor & self) {
    return at::_ops::silu::call(self);
}

// aten::silu_(Tensor(a!) self) -> Tensor(a!)
TORCH_API inline at::Tensor & silu_(at::Tensor & self) {
    return at::_ops::silu_::call(self);
}

// aten::silu.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & silu_out(at::Tensor & out, const at::Tensor & self) {
    return at::_ops::silu_out::call(self, out);
}

// aten::silu.out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & silu_outf(const at::Tensor & self, at::Tensor & out) {
    return at::_ops::silu_out::call(self, out);
}

}
