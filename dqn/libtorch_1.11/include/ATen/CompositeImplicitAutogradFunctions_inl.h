#pragma once
// @generated by tools/codegen/gen.py from DispatchKeyFunctions_inl.h

// NB: The implementing C++ file is RegisterDispatchKey.cpp

// The only #includes we need are for custom classes that have defaults in the C++ API
#include <c10/core/MemoryFormat.h>
#include <c10/core/Scalar.h>
#include <ATen/core/Reduction.h>

#if defined(AT_PER_OPERATOR_HEADERS) && defined(TORCH_ASSERT_ONLY_METHOD_OPERATORS)
#error This change adds a dependency on all pytorch operators, meaning the     \
  file will need to be re-compiled every time an operator is changed or added. \
  Consider including a specific operator from                                  \
  <ATen/ops/{my_operator}_compositeimplicitautograd_dispatch.h>.                   \
  See NOTE [TORCH_ASSERT_ONLY_METHOD_OPERATORS].
#endif

#include <ATen/ops/_add_batch_dim_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_autocast_to_full_precision_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_autocast_to_reduced_precision_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_batch_norm_impl_index_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_batch_norm_impl_index_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cast_Byte_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cast_Char_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cast_Double_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cast_Float_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cast_Half_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cast_Int_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cast_Long_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cast_Short_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_choose_qparams_per_tensor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_convolution_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_convolution_double_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_convolution_mode_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_csr_to_block_csr_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cufft_clear_plan_cache_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cufft_get_plan_cache_max_size_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cufft_get_plan_cache_size_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_cufft_set_plan_cache_max_size_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_debug_has_internal_overlap_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_dim_arange_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_embedding_bag_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_embedding_bag_sparse_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_fake_quantize_learnable_per_channel_affine_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_fake_quantize_learnable_per_tensor_affine_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_gather_sparse_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_grid_sampler_2d_cpu_fallback_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_has_compatible_shallow_copy_type_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_is_zerotensor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_lu_with_info_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_nnpack_available_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_pack_padded_sequence_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_pad_circular_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_pad_enum_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_pad_packed_sequence_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_remove_batch_dim_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_reshape_from_tensor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_rowwise_prune_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_saturate_weight_to_fp16_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_shape_as_tensor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sobol_engine_draw_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sobol_engine_ff_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sobol_engine_initialize_state_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sobol_engine_scramble_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sparse_coo_tensor_unsafe_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sparse_csr_tensor_unsafe_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sparse_log_softmax_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sparse_mm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sparse_softmax_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_sparse_sum_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_test_ambiguous_defaults_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_test_serialization_subcmul_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_test_string_default_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_thnn_differentiable_gru_cell_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_thnn_differentiable_lstm_cell_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_to_cpu_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_unpack_dual_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_use_cudnn_rnn_flatten_weight_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_validate_sparse_coo_tensor_args_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_validate_sparse_csr_tensor_args_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_version_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_weight_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/_weight_norm_differentiable_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/absolute_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/adaptive_avg_pool1d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/adaptive_avg_pool2d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/adaptive_avg_pool3d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/adaptive_max_pool1d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/addr_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/adjoint_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/affine_grid_generator_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/align_as_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/align_tensors_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/align_to_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/all_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/allclose_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/alpha_dropout_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/and_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/any_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/arange_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/arccos_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/arccosh_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/arcsin_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/arcsinh_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/arctan_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/arctan2_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/arctanh_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/argsort_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/argwhere_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/atleast_1d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/atleast_2d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/atleast_3d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/avg_pool1d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/bartlett_window_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/batch_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/bernoulli_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/bilinear_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/binary_cross_entropy_with_logits_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/bitwise_and_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/bitwise_or_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/bitwise_xor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/blackman_window_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/block_diag_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/broadcast_tensors_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/broadcast_to_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/can_cast_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cartesian_prod_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cat_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cdist_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/chain_matmul_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/choose_qparams_optimized_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/chunk_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/clip_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/coalesce_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/column_stack_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/combinations_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/concat_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conj_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conj_physical_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/contiguous_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conv1d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conv2d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conv3d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conv_tbc_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conv_transpose1d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conv_transpose2d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/conv_transpose3d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/corrcoef_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cosine_embedding_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cosine_similarity_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cov_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cross_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cross_entropy_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/ctc_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cudnn_is_acceptable_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cummax_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cummaxmin_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cummin_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cumprod_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cumprod_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cumsum_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/cumulative_trapezoid_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/data_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/det_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/diag_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/diagflat_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/diagonal_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/diff_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/divide_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/dropout_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/dsplit_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/dstack_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/einsum_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/embedding_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/embedding_bag_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/embedding_sparse_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/empty_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/expand_as_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/eye_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fake_quantize_per_channel_affine_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fake_quantize_per_channel_affine_cachemask_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fake_quantize_per_tensor_affine_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fake_quantize_per_tensor_affine_cachemask_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fbgemm_linear_fp16_weight_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fbgemm_linear_fp16_weight_fp32_activation_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fbgemm_linear_int8_weight_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fbgemm_linear_int8_weight_fp32_activation_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fbgemm_linear_quantize_weight_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fbgemm_pack_gemm_matrix_fp16_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fbgemm_pack_quantized_matrix_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/feature_alpha_dropout_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/feature_dropout_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_fft_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_fft2_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_fftfreq_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_fftn_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_fftshift_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_hfft_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_hfft2_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_hfftn_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_ifft_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_ifft2_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_ifftn_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_ifftshift_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_ihfft_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_ihfft2_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_ihfftn_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_irfft_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_irfft2_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_irfftn_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_rfft_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_rfft2_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_rfftfreq_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fft_rfftn_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fill_diagonal_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fix_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/flatten_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/flatten_dense_tensors_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fliplr_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/flipud_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/float_power_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/floor_divide_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/frobenius_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/full_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/full_like_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/fused_moving_avg_obs_fake_quant_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/gather_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/gather_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/ger_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/gradient_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/greater_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/greater_equal_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/grid_sampler_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/group_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/gru_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/gru_cell_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/hamming_window_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/hann_window_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/hinge_embedding_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/histogramdd_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/hsplit_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/hstack_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/imag_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/index_add_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/index_copy_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/index_fill_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/index_select_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/index_select_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/infinitely_differentiable_gelu_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/inner_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/instance_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_complex_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_conj_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_distributed_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_floating_point_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_inference_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_leaf_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_neg_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_nonzero_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_same_size_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_signed_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/is_vulkan_available_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/isclose_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/isfinite_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/isreal_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/istft_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/item_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/kaiser_window_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/kron_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/kthvalue_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/layer_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/ldexp_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/less_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/less_equal_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_cholesky_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_cond_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_det_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_diagonal_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_eigvals_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_eigvalsh_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_inv_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_lu_factor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_matmul_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_matrix_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_matrix_power_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_matrix_rank_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_multi_dot_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_pinv_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_svd_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_svdvals_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_tensorinv_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linalg_tensorsolve_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linear_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/linspace_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/log_sigmoid_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/log_softmax_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/logcumsumexp_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/logspace_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/logsumexp_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/lstm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/lstm_cell_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/mH_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/mT_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/margin_ranking_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/masked_select_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/matmul_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/matrix_H_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/matrix_exp_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/matrix_exp_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/matrix_power_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/matrix_rank_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/max_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/max_pool1d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/max_pool1d_with_indices_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/max_pool2d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/max_pool3d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/mean_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/median_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/meshgrid_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/min_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/mish_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/mode_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/moveaxis_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/movedim_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/msort_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/multilabel_margin_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/multiply_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nanmean_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nanmedian_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nanquantile_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/narrow_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/native_channel_shuffle_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/native_group_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/native_layer_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/negative_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nested_tensor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/new_full_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/new_ones_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/new_zeros_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nll_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nll_loss2d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nll_loss_nd_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nonzero_numpy_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/norm_except_dim_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/normal_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/not_equal_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/nuclear_norm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/numpy_T_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/one_hot_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/ones_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/ones_like_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/or_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/orgqr_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/outer_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/output_nr_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/pad_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/pad_sequence_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/pairwise_distance_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/pdist_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/pin_memory_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/pinverse_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/pixel_shuffle_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/pixel_unshuffle_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/poisson_nll_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/positive_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/prod_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/promote_types_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/put_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/qr_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/quantile_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/quantized_gru_cell_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/quantized_lstm_cell_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/quantized_rnn_relu_cell_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/quantized_rnn_tanh_cell_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/rand_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/rand_like_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/randint_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/randint_like_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/randn_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/randn_like_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/randperm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/range_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/ravel_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/real_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/refine_names_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/relu6_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/rename_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/repeat_interleave_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/requires_grad_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/reshape_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/reshape_as_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/resolve_conj_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/resolve_neg_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/result_type_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/retain_grad_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/retains_grad_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/rnn_relu_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/rnn_relu_cell_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/rnn_tanh_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/rnn_tanh_cell_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/row_stack_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/rrelu_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/scalar_tensor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/scatter_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/scatter_add_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/select_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/selu_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/set_data_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/silu_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/size_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/slow_conv3d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/smm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/softmax_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/sort_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/sparse_coo_tensor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/sparse_csr_tensor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_digamma_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_erf_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_erfc_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_erfinv_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_exp2_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_expit_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_expm1_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_gammainc_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_gammaincc_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_gammaln_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_i0_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_log1p_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_log_softmax_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_logit_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_logsumexp_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_multigammaln_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_ndtr_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_polygamma_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_psi_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_round_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_sinc_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_softmax_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/special_xlogy_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/split_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/square_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/squeeze_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/sspaddmm_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/std_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/std_mean_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/stft_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/stride_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/subtract_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/sum_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/sum_to_size_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/svd_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/swapaxes_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/swapdims_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/take_along_dim_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/tensor_split_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/tensordot_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/thnn_conv2d_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/tile_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/to_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/to_dense_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/to_dense_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/to_mkldnn_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/trace_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/transpose_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/trapezoid_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/trapz_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/triplet_margin_loss_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/true_divide_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/type_as_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/unbind_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/unflatten_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/unflatten_dense_tensors_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/unsafe_chunk_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/value_selecting_reduction_backward_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/vander_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/var_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/var_mean_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/view_as_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/vsplit_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/vstack_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/where_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/xor_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/zeros_compositeimplicitautograd_dispatch.h>
#include <ATen/ops/zeros_like_compositeimplicitautograd_dispatch.h>

namespace at {
namespace compositeimplicitautograd {



} // namespace compositeimplicitautograd
} // namespace at
