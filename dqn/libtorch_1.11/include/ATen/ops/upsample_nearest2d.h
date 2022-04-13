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



#include <ATen/ops/upsample_nearest2d_ops.h>

namespace at {


// aten::upsample_nearest2d.vec(Tensor input, int[]? output_size, float[]? scale_factors) -> Tensor
TORCH_API inline at::Tensor upsample_nearest2d(const at::Tensor & input, at::OptionalIntArrayRef output_size, c10::optional<at::ArrayRef<double>> scale_factors) {
    return at::_ops::upsample_nearest2d_vec::call(input, output_size, scale_factors);
}

// aten::upsample_nearest2d.out(Tensor self, int[2] output_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & upsample_nearest2d_out(at::Tensor & out, const at::Tensor & self, at::IntArrayRef output_size, c10::optional<double> scales_h=c10::nullopt, c10::optional<double> scales_w=c10::nullopt) {
    return at::_ops::upsample_nearest2d_out::call(self, output_size, scales_h, scales_w, out);
}

// aten::upsample_nearest2d.out(Tensor self, int[2] output_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) out) -> Tensor(a!)
TORCH_API inline at::Tensor & upsample_nearest2d_outf(const at::Tensor & self, at::IntArrayRef output_size, c10::optional<double> scales_h, c10::optional<double> scales_w, at::Tensor & out) {
    return at::_ops::upsample_nearest2d_out::call(self, output_size, scales_h, scales_w, out);
}

// aten::upsample_nearest2d(Tensor self, int[2] output_size, float? scales_h=None, float? scales_w=None) -> Tensor
TORCH_API inline at::Tensor upsample_nearest2d(const at::Tensor & self, at::IntArrayRef output_size, c10::optional<double> scales_h=c10::nullopt, c10::optional<double> scales_w=c10::nullopt) {
    return at::_ops::upsample_nearest2d::call(self, output_size, scales_h, scales_w);
}

}
