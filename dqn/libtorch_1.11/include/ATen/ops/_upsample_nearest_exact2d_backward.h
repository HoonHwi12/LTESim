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



#include <ATen/ops/_upsample_nearest_exact2d_backward_ops.h>

namespace at {


// aten::_upsample_nearest_exact2d_backward.vec(Tensor grad_output, int[]? output_size, int[] input_size, float[]? scale_factors) -> Tensor
TORCH_API inline at::Tensor _upsample_nearest_exact2d_backward(const at::Tensor & grad_output, at::OptionalIntArrayRef output_size, at::IntArrayRef input_size, c10::optional<at::ArrayRef<double>> scale_factors) {
    return at::_ops::_upsample_nearest_exact2d_backward_vec::call(grad_output, output_size, input_size, scale_factors);
}

// aten::_upsample_nearest_exact2d_backward.grad_input(Tensor grad_output, int[2] output_size, int[4] input_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) grad_input) -> Tensor(a!)
TORCH_API inline at::Tensor & _upsample_nearest_exact2d_backward_out(at::Tensor & grad_input, const at::Tensor & grad_output, at::IntArrayRef output_size, at::IntArrayRef input_size, c10::optional<double> scales_h=c10::nullopt, c10::optional<double> scales_w=c10::nullopt) {
    return at::_ops::_upsample_nearest_exact2d_backward_grad_input::call(grad_output, output_size, input_size, scales_h, scales_w, grad_input);
}

// aten::_upsample_nearest_exact2d_backward.grad_input(Tensor grad_output, int[2] output_size, int[4] input_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) grad_input) -> Tensor(a!)
TORCH_API inline at::Tensor & _upsample_nearest_exact2d_backward_outf(const at::Tensor & grad_output, at::IntArrayRef output_size, at::IntArrayRef input_size, c10::optional<double> scales_h, c10::optional<double> scales_w, at::Tensor & grad_input) {
    return at::_ops::_upsample_nearest_exact2d_backward_grad_input::call(grad_output, output_size, input_size, scales_h, scales_w, grad_input);
}

// aten::_upsample_nearest_exact2d_backward(Tensor grad_output, int[2] output_size, int[4] input_size, float? scales_h=None, float? scales_w=None) -> Tensor
TORCH_API inline at::Tensor _upsample_nearest_exact2d_backward(const at::Tensor & grad_output, at::IntArrayRef output_size, at::IntArrayRef input_size, c10::optional<double> scales_h=c10::nullopt, c10::optional<double> scales_w=c10::nullopt) {
    return at::_ops::_upsample_nearest_exact2d_backward::call(grad_output, output_size, input_size, scales_h, scales_w);
}

}
