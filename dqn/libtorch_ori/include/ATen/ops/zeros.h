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



#include <ATen/ops/zeros_ops.h>

namespace at {


// aten::zeros.names(int[] size, *, Dimname[]? names, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=None) -> Tensor
TORCH_API inline at::Tensor zeros(at::IntArrayRef size, c10::optional<at::DimnameList> names, at::TensorOptions options={}) {
    return at::_ops::zeros_names::call(size, names, optTypeMetaToScalarType(options.dtype_opt()), options.layout_opt(), options.device_opt(), options.pinned_memory_opt());
}

// aten::zeros.names(int[] size, *, Dimname[]? names, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=None) -> Tensor
TORCH_API inline at::Tensor zeros(at::IntArrayRef size, c10::optional<at::DimnameList> names, c10::optional<at::ScalarType> dtype, c10::optional<at::Layout> layout, c10::optional<at::Device> device, c10::optional<bool> pin_memory) {
    return at::_ops::zeros_names::call(size, names, dtype, layout, device, pin_memory);
}

// aten::zeros(int[] size, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=None) -> Tensor
TORCH_API inline at::Tensor zeros(at::IntArrayRef size, at::TensorOptions options={}) {
    return at::_ops::zeros::call(size, optTypeMetaToScalarType(options.dtype_opt()), options.layout_opt(), options.device_opt(), options.pinned_memory_opt());
}

// aten::zeros(int[] size, *, ScalarType? dtype=None, Layout? layout=None, Device? device=None, bool? pin_memory=None) -> Tensor
TORCH_API inline at::Tensor zeros(at::IntArrayRef size, c10::optional<at::ScalarType> dtype, c10::optional<at::Layout> layout, c10::optional<at::Device> device, c10::optional<bool> pin_memory) {
    return at::_ops::zeros::call(size, dtype, layout, device, pin_memory);
}

// aten::zeros.out(int[] size, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & zeros_out(at::Tensor & out, at::IntArrayRef size) {
    return at::_ops::zeros_out::call(size, out);
}

// aten::zeros.out(int[] size, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & zeros_outf(at::IntArrayRef size, at::Tensor & out) {
    return at::_ops::zeros_out::call(size, out);
}

}
