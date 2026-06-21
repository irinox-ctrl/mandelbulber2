// Extended mutation UI registry data (clip, inversion, julia)
#include "mutation_ui_registry.hpp"

namespace {
static const int kExtTypes_0[] = {1, 5, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19, 22};
static const int kExtTypes_1[] = {1, 5, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19, 22};
static const int kExtTypes_2[] = {1, 5, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19, 22};
static const int kExtTypes_3[] = {1, 5, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19, 22};
static const int kExtTypes_4[] = {2, 3, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 25, 26, 27, 28, 29, 30};
static const int kExtTypes_5[] = {2, 3, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 25, 26, 27, 28, 29, 30};
static const int kExtTypes_6[] = {2};
static const int kExtTypes_7[] = {2};
static const int kExtTypes_8[] = {4};
static const int kExtTypes_9[] = {4};
static const int kExtTypes_10[] = {9, 26};
static const int kExtTypes_11[] = {9, 26};
static const int kExtTypes_12[] = {9, 10, 23, 28, 30};
static const int kExtTypes_13[] = {9, 10, 23, 28, 30};
static const int kExtTypes_14[] = {14, 15};
static const int kExtTypes_15[] = {14, 15};
static const int kExtTypes_16[] = {31, 33, 34, 35};
static const int kExtTypes_17[] = {31, 33, 34, 35};
static const int kExtTypes_18[] = {6, 8, 20, 24, 27};
static const int kExtTypes_19[] = {6, 8, 20, 24, 27};
static const int kExtTypes_20[] = {8};
static const int kExtTypes_21[] = {8};
static const int kExtTypes_22[] = {1, 3, 4, 5, 7, 9, 10, 15, 16, 17, 18, 20, 23};
static const int kExtTypes_23[] = {1, 3, 4, 5, 7, 9, 10, 15, 16, 17, 18, 20, 23};
static const int kExtTypes_24[] = {1, 4, 7, 18};
static const int kExtTypes_25[] = {1, 4, 7, 18};
static const int kExtTypes_26[] = {1, 4, 11, 18};
static const int kExtTypes_27[] = {1, 4, 11, 18};
static const int kExtTypes_28[] = {6};
static const int kExtTypes_29[] = {6};
static const int kExtTypes_30[] = {8, 25, 26};
static const int kExtTypes_31[] = {8, 25, 26};
static const int kExtTypes_32[] = {22, 25, 26};
static const int kExtTypes_33[] = {22, 25, 26};
static const int kExtTypes_34[] = {25};
static const int kExtTypes_35[] = {25};
static const int kExtTypes_36[] = {12};
static const int kExtTypes_37[] = {12};
static const int kExtTypes_38[] = {14};
static const int kExtTypes_39[] = {14};
static const int kExtTypes_40[] = {28};
static const int kExtTypes_41[] = {28};
static const int kExtTypes_42[] = {29};
static const int kExtTypes_43[] = {29};
static const int kExtTypes_44[] = {11, 12, 13, 14};
static const int kExtTypes_45[] = {11, 12, 13, 14};
static const int kExtTypes_46[] = {11, 12, 13, 14};
static const int kExtTypes_47[] = {11, 12, 13, 14};
static const int kExtTypes_48[] = {11, 12, 13};
static const int kExtTypes_49[] = {11, 12, 13};
static const sMutationParamRule kExtendedParamRules[] = {
	{ "clip", "label_clip_center", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinbox_mutation_clip_center_ax", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinbox_mutation_clip_center_ay", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinbox_mutation_clip_center_az", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "label_clip_bool", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinboxInt_mutation_clip_boolean_op", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "label_clip_iter_start", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinboxInt_mutation_clip_iter_start", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "label_clip_iter_stop", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinboxInt_mutation_clip_iter_stop", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "label_clip_prerot_x", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "label_clip_prerot_y", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "label_clip_prerot_z", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinbox_mutation_clip_pre_rot_ax", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinbox_mutation_clip_pre_rot_ay", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "spinbox_mutation_clip_pre_rot_az", nullptr, nullptr, 0, 0, 0, true },
	{ "clip", "label_clip_size", nullptr, kExtTypes_0, 13, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_size_ax", nullptr, kExtTypes_1, 13, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_size_ay", nullptr, kExtTypes_2, 13, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_size_az", nullptr, kExtTypes_3, 13, 0, 0, false },
	{ "clip", "label_clip_radius", nullptr, kExtTypes_4, 19, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_radius", nullptr, kExtTypes_5, 19, 0, 0, false },
	{ "clip", "label_clip_major_r", nullptr, kExtTypes_6, 1, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_major_radius", nullptr, kExtTypes_7, 1, 0, 0, false },
	{ "clip", "label_clip_angle", nullptr, kExtTypes_8, 1, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_angle", nullptr, kExtTypes_9, 1, 0, 0, false },
	{ "clip", "label_clip_freq", nullptr, kExtTypes_10, 2, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_frequency", nullptr, kExtTypes_11, 2, 0, 0, false },
	{ "clip", "label_clip_amp", nullptr, kExtTypes_12, 5, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_amplitude", nullptr, kExtTypes_13, 5, 0, 0, false },
	{ "clip", "label_clip_smooth", nullptr, kExtTypes_14, 2, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_smooth_k", nullptr, kExtTypes_15, 2, 0, 0, false },
	{ "clip", "label_clip_npoints", nullptr, kExtTypes_16, 4, 0, 0, false },
	{ "clip", "spinboxInt_mutation_clip_n_points", nullptr, kExtTypes_17, 4, 0, 0, false },
	{ "clip", "label_clip_param", nullptr, kExtTypes_18, 5, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_param_a", nullptr, kExtTypes_19, 5, 0, 0, false },
	{ "clip", "label_clip_param_b", nullptr, kExtTypes_20, 1, 0, 0, false },
	{ "clip", "spinbox_mutation_clip_param_b", nullptr, kExtTypes_21, 1, 0, 0, false },
	{ "inv", "label_inv_center", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "spinbox_mutation_inv_center_ax", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "spinbox_mutation_inv_center_ay", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "spinbox_mutation_inv_center_az", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "label_inv_iter_start", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "spinboxInt_mutation_inv_iter_start", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "label_inv_iter_stop", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "spinboxInt_mutation_inv_iter_stop", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "label_inv_prerot_x", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "label_inv_prerot_y", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "label_inv_prerot_z", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "spinbox_mutation_inv_pre_rot_ax", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "spinbox_mutation_inv_pre_rot_ay", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "spinbox_mutation_inv_pre_rot_az", nullptr, nullptr, 0, 0, 0, true },
	{ "inv", "label_inv_radius", nullptr, nullptr, 0, 2, 30, false },
	{ "inv", "spinbox_mutation_inv_radius", nullptr, nullptr, 0, 2, 30, false },
	{ "inv", "label_inv_param_a", nullptr, kExtTypes_22, 13, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_param_a", nullptr, kExtTypes_23, 13, 0, 0, false },
	{ "inv", "label_inv_param_b", nullptr, kExtTypes_24, 4, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_param_b", nullptr, kExtTypes_25, 4, 0, 0, false },
	{ "inv", "label_inv_param_c", nullptr, kExtTypes_26, 4, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_param_c", nullptr, kExtTypes_27, 4, 0, 0, false },
	{ "inv", "label_inv_angle", nullptr, kExtTypes_28, 1, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_angle", nullptr, kExtTypes_29, 1, 0, 0, false },
	{ "inv", "label_inv_freq", nullptr, kExtTypes_30, 3, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_frequency", nullptr, kExtTypes_31, 3, 0, 0, false },
	{ "inv", "label_inv_amp", nullptr, kExtTypes_32, 3, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_amplitude", nullptr, kExtTypes_33, 3, 0, 0, false },
	{ "inv", "label_inv_scale", nullptr, kExtTypes_34, 1, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_scale", nullptr, kExtTypes_35, 1, 0, 0, false },
	{ "inv", "label_inv_weight", nullptr, kExtTypes_36, 1, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_weight", nullptr, kExtTypes_37, 1, 0, 0, false },
	{ "inv", "label_inv_nsteps", nullptr, kExtTypes_38, 1, 0, 0, false },
	{ "inv", "spinboxInt_mutation_inv_n_steps", nullptr, kExtTypes_39, 1, 0, 0, false },
	{ "inv", "label_inv_threshold", nullptr, kExtTypes_40, 1, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_threshold", nullptr, kExtTypes_41, 1, 0, 0, false },
	{ "inv", "label_inv_colorfactor", nullptr, kExtTypes_42, 1, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_color_factor", nullptr, kExtTypes_43, 1, 0, 0, false },
	{ "inv", "label_inv_center2", nullptr, kExtTypes_44, 4, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_center2_ax", nullptr, kExtTypes_45, 4, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_center2_ay", nullptr, kExtTypes_46, 4, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_center2_az", nullptr, kExtTypes_47, 4, 0, 0, false },
	{ "inv", "label_inv_radius2", nullptr, kExtTypes_48, 3, 0, 0, false },
	{ "inv", "spinbox_mutation_inv_radius2", nullptr, kExtTypes_49, 3, 0, 0, false },
};
static const sMutationJuliaUiRule kJuliaUiRules[] = {
	{ "comboBox_mutation_julia_start", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_start", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "comboBox_mutation_julia_injection", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_injection", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "spinboxInt_mutation_julia_iter_start", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_iter_s", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "spinboxInt_mutation_julia_iter_stop", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_iter_e", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_iter", true, false, -1, false, -1, false, -1, false, -1, -1 },
	{ "comboBox_mutation_julia_c_transform", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_c_transform", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_c_mul", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_c_mul", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "spinboxd3_mutation_julia_c_rot_x", false, true, -1, false, 3, false, -1, false, -1, -1 },
	{ "spinboxd3_mutation_julia_c_rot_y", false, true, -1, false, 3, false, -1, false, -1, -1 },
	{ "spinboxd3_mutation_julia_c_rot_z", false, true, -1, false, 3, false, -1, false, -1, -1 },
	{ "label_c_rotation", false, true, -1, false, 3, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_c_radius", false, true, -1, false, 1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_c_radius", false, true, -1, false, 1, false, -1, false, -1, -1 },
	{ "spinboxd_mutation_julia_c_mobius_a", false, true, -1, false, 2, false, -1, false, -1, -1 },
	{ "spinboxd_mutation_julia_c_mobius_b", false, true, -1, false, 2, false, -1, false, -1, -1 },
	{ "spinboxd_mutation_julia_c_mobius_d", false, true, -1, false, 2, false, -1, false, -1, -1 },
	{ "label_m_bius_a", false, true, -1, false, 2, false, -1, false, -1, -1 },
	{ "label_m_bius_b", false, true, -1, false, 2, false, -1, false, -1, -1 },
	{ "label_m_bius_d", false, true, -1, false, 2, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_c_power", false, true, -1, false, 4, false, -1, false, -1, -1 },
	{ "label_mutation_julia_c_power", false, true, -1, false, 4, false, -1, false, -1, -1 },
	{ "comboBox_mutation_julia_dynamic", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_dynamic", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_pulse_freq", false, true, -1, false, -1, true, 2, false, -1, -1 },
	{ "label_mutation_julia_pulse_freq", false, true, -1, false, -1, true, 2, false, -1, -1 },
	{ "spinboxd_mutation_julia_pulse_amp", false, true, -1, false, -1, true, 2, false, -1, -1 },
	{ "label_pulse_amp", false, true, -1, false, -1, true, 2, false, -1, -1 },
	{ "spinbox_mutation_julia_absorb", false, true, -1, false, -1, true, 4, false, -1, -1 },
	{ "label_mutation_julia_absorb", false, true, -1, false, -1, true, 4, false, -1, -1 },
	{ "comboBox_mutation_julia_multi", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_multi", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "spinboxd_mutation_julia_noise_freq", false, true, -1, false, -1, false, -1, true, 4, -1 },
	{ "label_julia_noise_freq", false, true, -1, false, -1, false, -1, true, 4, -1 },
	{ "spinboxd_mutation_julia_noise_amp", false, true, -1, false, -1, false, -1, true, 4, -1 },
	{ "label_julia_noise_amp", false, true, -1, false, -1, false, -1, true, 4, -1 },
	{ "spinboxd3_mutation_julia_fourier_c2_x", false, true, -1, false, -1, false, -1, true, 3, -1 },
	{ "spinboxd3_mutation_julia_fourier_c2_y", false, true, -1, false, -1, false, -1, true, 3, -1 },
	{ "spinboxd3_mutation_julia_fourier_c2_z", false, true, -1, false, -1, false, -1, true, 3, -1 },
	{ "label_fourier_c2", false, true, -1, false, -1, false, -1, true, 3, -1 },
	{ "spinboxd3_mutation_julia_fourier_c3_x", false, true, -1, false, -1, false, -1, true, 3, -1 },
	{ "spinboxd3_mutation_julia_fourier_c3_y", false, true, -1, false, -1, false, -1, true, 3, -1 },
	{ "spinboxd3_mutation_julia_fourier_c3_z", false, true, -1, false, -1, false, -1, true, 3, -1 },
	{ "label_fourier_c3", false, true, -1, false, -1, false, -1, true, 3, -1 },
	{ "spinboxd3_mutation_julia_bipolar_cr_x", false, true, -1, false, -1, false, -1, true, 1, -1 },
	{ "spinboxd3_mutation_julia_bipolar_cr_y", false, true, -1, false, -1, false, -1, true, 1, -1 },
	{ "spinboxd3_mutation_julia_bipolar_cr_z", false, true, -1, false, -1, false, -1, true, 1, -1 },
	{ "label_bipolar_cr", false, true, -1, false, -1, false, -1, true, 1, -1 },
	{ "spinboxInt_mutation_julia_ctransform_iter_start", false, true, -1, true, -1, false, -1, false, -1, -1 },
	{ "spinboxInt_mutation_julia_ctransform_iter_stop", false, true, -1, true, -1, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_ctransform_strength", false, true, -1, true, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_ctransform_iter_start_l", false, true, -1, true, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_ctransform_iter_stop_l", false, true, -1, true, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_ctransform_strength_l", false, true, -1, true, -1, false, -1, false, -1, -1 },
	{ "spinboxInt_mutation_julia_dynamic_iter_start", false, true, -1, false, -1, true, -1, false, -1, -1 },
	{ "spinboxInt_mutation_julia_dynamic_iter_stop", false, true, -1, false, -1, true, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_dynamic_strength", false, true, -1, false, -1, true, -1, false, -1, -1 },
	{ "label_mutation_julia_dynamic_iter_start_l", false, true, -1, false, -1, true, -1, false, -1, -1 },
	{ "label_mutation_julia_dynamic_iter_stop_l", false, true, -1, false, -1, true, -1, false, -1, -1 },
	{ "label_mutation_julia_dynamic_strength_l", false, true, -1, false, -1, true, -1, false, -1, -1 },
	{ "spinboxInt_mutation_julia_multi_iter_start", false, true, -1, false, -1, false, -1, true, -1, -1 },
	{ "spinboxInt_mutation_julia_multi_iter_stop", false, true, -1, false, -1, false, -1, true, -1, -1 },
	{ "spinbox_mutation_julia_multi_strength", false, true, -1, false, -1, false, -1, true, -1, -1 },
	{ "label_mutation_julia_multi_iter_start_l", false, true, -1, false, -1, false, -1, true, -1, -1 },
	{ "label_mutation_julia_multi_iter_stop_l", false, true, -1, false, -1, false, -1, true, -1, -1 },
	{ "label_mutation_julia_multi_strength_l", false, true, -1, false, -1, false, -1, true, -1, -1 },
	{ "spinbox_mutation_julia_injection_strength", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_de_factor", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_injection_strength_l", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_de_factor_l", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_ext_header", false, true, -1, false, -1, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_decay_rate", false, true, -1, false, -1, true, 6, false, -1, -1 },
	{ "label_mutation_julia_decay_rate_l", false, true, -1, false, -1, true, 6, false, -1, -1 },
	{ "spinbox_mutation_julia_spiral_angle", false, true, -1, true, 10, false, -1, false, -1, -1 },
	{ "label_mutation_julia_spiral_angle_l", false, true, -1, true, 10, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_spiral_angle", false, true, -1, false, -1, true, 10, false, -1, -1 },
	{ "label_mutation_julia_spiral_angle_l", false, true, -1, false, -1, true, 10, false, -1, -1 },
	{ "spinbox_mutation_julia_chaos_r", false, true, -1, false, -1, true, 9, false, -1, -1 },
	{ "label_mutation_julia_chaos_r_l", false, true, -1, false, -1, true, 9, false, -1, -1 },
	{ "spinbox_mutation_julia_threshold", false, true, 9, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_threshold_l", false, true, 9, false, -1, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_threshold", false, true, -1, false, -1, true, 3, false, -1, -1 },
	{ "label_mutation_julia_threshold_l", false, true, -1, false, -1, true, 3, false, -1, -1 },
	{ "spinbox_mutation_julia_threshold", false, true, -1, false, -1, true, 8, false, -1, -1 },
	{ "label_mutation_julia_threshold_l", false, true, -1, false, -1, true, 8, false, -1, -1 },
	{ "spinbox_mutation_julia_gradient_end", false, true, 10, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_gradient_end_l", false, true, 10, false, -1, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_box_fold_limit", false, true, -1, true, 9, false, -1, false, -1, -1 },
	{ "label_mutation_julia_box_fold_limit_l", false, true, -1, true, 9, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_start_epsilon", false, false, -1, false, -1, false, -1, false, -1, 9 },
	{ "label_mutation_julia_start_epsilon_l", false, false, -1, false, -1, false, -1, false, -1, 9 },
	{ "spinboxd3_mutation_julia_layer_c2_x", false, true, 11, false, -1, false, -1, false, -1, -1 },
	{ "spinboxd3_mutation_julia_layer_c2_y", false, true, 11, false, -1, false, -1, false, -1, -1 },
	{ "spinboxd3_mutation_julia_layer_c2_z", false, true, 11, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_layer_c2_l", false, true, 11, false, -1, false, -1, false, -1, -1 },
	{ "label_mutation_julia_layer_c2_yz_l", false, true, 11, false, -1, false, -1, false, -1, -1 },
	{ "spinbox_mutation_julia_dist_band_mid", false, true, -1, false, -1, false, -1, true, 10, -1 },
	{ "spinbox_mutation_julia_dist_band_far", false, true, -1, false, -1, false, -1, true, 10, -1 },
	{ "label_mutation_julia_dist_band_l", false, true, -1, false, -1, false, -1, true, 10, -1 },
	{ "label_mutation_julia_dist_band_far_l", false, true, -1, false, -1, false, -1, true, 10, -1 },
};
static const sMutationSystemBinding kExtendedSystemBindings[] = {
	{ "clip", "groupCheck_mutation_clip_enabled", "comboBox_mutation_clip_type" },
	{ "inv", "groupCheck_mutation_inversion_enabled", "comboBox_mutation_inv_type" },
};
} // namespace

const sMutationParamRule *cMutationUiRegistry::ExtendedParamRulesData() { return kExtendedParamRules; }
int cMutationUiRegistry::ExtendedParamRulesCount() { return int(sizeof(kExtendedParamRules)/sizeof(kExtendedParamRules[0])); }
const sMutationJuliaUiRule *cMutationUiRegistry::JuliaRulesData() { return kJuliaUiRules; }
int cMutationUiRegistry::JuliaRulesCount() { return int(sizeof(kJuliaUiRules)/sizeof(kJuliaUiRules[0])); }
const sMutationSystemBinding *cMutationUiRegistry::ExtendedSystemBindingsData() { return kExtendedSystemBindings; }
int cMutationUiRegistry::ExtendedSystemBindingsCount() { return int(sizeof(kExtendedSystemBindings)/sizeof(kExtendedSystemBindings[0])); }