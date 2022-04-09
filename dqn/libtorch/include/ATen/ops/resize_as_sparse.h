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



#include <ATen/ops/resize_as_sparse_ops.h>

namespace at {


// aten::resize_as_sparse_(Tensor(a!) self, Tensor the_template) -> Tensor(a!)
TORCH_API inline const at::Tensor & resize_as_sparse_(const at::Tensor & self, const at::Tensor & the_template) {
    return at::_ops::resize_as_sparse_::call(self, the_template);
}

}
