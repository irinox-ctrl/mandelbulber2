// Auto-generated from dock_mutation_tab.cpp gray-out tables
#include "mutation_ui_registry.hpp"

namespace {

static const int kJosParamA[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 15, 17};
static const int kJosParamB[] = {1, 2, 5, 6, 10, 11, 12, 13, 17};
static const int kJosParamC[] = {3, 4, 7, 8, 11, 12};
static const int kJosPhaseFreq[] = {2, 4, 6, 8};

static const int kPkParamB[] = {13, 14, 20, 21, 22, 29};
static const int kPkParamC[] = {21, 22, 29};
static const int kPkPhaseFreq[] = {10, 20, 21, 22};

static const int kDeP1[] = {3, 4};
static const int kDeP2[] = {4};

static const int kTypes_10[] = {1, 2, 3, 4, 6, 10, 11, 12, 13, 14, 16, 18, 19, 20, 21, 25, 26, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 51, 52, 53, 55, 57, 58, 60, 62, 63, 64, 65, 66, 69, 70, 72, 74, 75, 77, 78, 79, 81, 82, 84, 86, 90, 92, 93, 98, 100, 102, 103, 105, 107, 111, 112, 116, 118, 119, 120, 121, 122, 126, 127, 130, 131, 132, 133, 134, 135, 136, 142, 143, 145, 149, 150, 157, 159, 162, 163, 164, 165, 166, 167, 170, 171, 174, 175, 176, 177, 178, 180, 181, 182, 183, 184, 185, 186, 188, 189, 191, 192, 193, 194, 195, 196, 197, 199, 200};
static const int kTypes_11[] = {2, 3, 4, 10, 12, 13, 14, 15, 22, 23, 24, 25, 26, 31, 32, 33, 34, 37, 38, 39, 40, 41, 43, 46, 48, 49, 51, 52, 58, 63, 64, 66, 69, 72, 75, 77, 79, 81, 90, 92, 105, 111, 118, 121, 126, 127, 130, 131, 133, 134, 135, 143, 145, 149, 150, 157, 164, 165, 166, 170, 171, 174, 175, 177, 180, 183, 185, 188, 189, 191, 192, 195, 196, 197, 199, 200};
static const int kTypes_12[] = {3, 4, 14, 23, 26, 32, 33, 41, 43, 46, 49, 64, 69, 75, 77, 105, 118, 130, 131, 133, 145, 149, 150, 165, 166, 170, 175, 177, 180, 183, 185, 188, 191, 196, 197, 199, 200};
static const int kTypes_13[] = {3, 23, 41, 75, 130, 131, 133, 149, 170, 177, 180, 183, 185, 188, 191, 196, 197, 199, 200};
static const int kTypes_14[] = {41, 75, 177, 180, 188, 191, 196, 199, 200};
static const int kTypes_15[] = {177, 191, 196, 199, 200};
static const int kTypes_16[] = {191, 196, 200};
static const int kTypes_17[] = {9, 14, 16, 17, 20, 25, 37, 45, 48, 49, 55};
static const int kTypes_18[] = {9, 20, 49};
static const int kTypes_19[] = {20, 49};
static const int kTypes_20[] = {27, 35, 38, 39, 40, 47, 48, 50};
static const int kTypes_21[] = {35, 38, 40, 47, 48};
static const int kTypes_22[] = {38};
static const int kTypes_23[] = {1, 3, 6, 8, 20, 24, 25, 32, 35};
static const int kTypes_24[] = {1, 3, 6, 8, 35};
static const int kTypes_25[] = {6, 29};
static const int kTypes_26[] = {1, 2, 3, 4, 6, 7, 8, 10, 11, 12, 14, 15, 19, 23, 28, 29, 30, 33};
static const int kTypes_27[] = {1, 2, 3, 4, 6, 11, 12, 15, 19, 23, 29};
static const int kTypes_28[] = {1, 2, 3, 4, 6, 8, 9, 14, 16, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29, 31, 32, 33, 34, 35, 38, 39, 40, 41, 44, 45, 47, 48, 49, 50, 51, 55, 56, 57, 58, 59, 60, 61, 62};
static const int kTypes_29[] = {3, 4, 9, 14, 17, 19, 21, 25, 26, 33, 34, 35, 40, 44, 45, 47, 48, 49, 50, 51, 55, 56, 57, 58, 59, 60, 61, 62};
static const int kTypes_30[] = {4, 9, 17, 33, 34, 45, 49, 50, 51, 55, 56, 57, 58, 59, 60, 61, 62};
static const int kTypes_31[] = {8, 9, 10, 11, 17, 18, 19, 20, 28, 29, 30, 31, 32, 33, 35, 36, 37, 38, 39, 41, 42, 43, 44, 45, 47, 49, 50, 52, 53, 55, 56, 57, 58, 59, 60, 61, 62, 63, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 77, 79, 82, 84, 86, 87, 91, 93, 95, 96, 97, 100, 101, 102, 103, 104, 106, 107, 108, 109, 112, 113, 114, 115, 116, 117, 118, 120, 121, 122, 123, 124, 125, 132, 133, 134, 135, 136, 137, 141, 142, 144, 145, 146, 147, 148, 149, 150, 152, 154, 159, 160, 161, 162, 163, 164, 165, 168, 169, 171, 172, 175, 178, 181, 184, 187, 189, 190, 194, 195, 196, 199, 201, 202, 206, 208, 209, 211, 212, 215, 220, 221, 222, 223, 226, 227, 228, 231, 232, 233, 237, 238, 240, 243, 244, 245, 247, 248, 249, 250, 262, 264, 266, 267, 268, 269, 271, 272, 273, 278, 279, 281, 282, 283, 284, 285, 286, 288, 289, 290, 291, 292, 293, 294, 295, 296, 298, 299, 300, 302, 305, 307, 308};
static const int kTypes_32[] = {11, 17, 18, 31, 32, 41, 43, 44, 58, 59, 60, 61, 65, 67, 68, 69, 72, 73, 75, 82, 84, 87, 91, 95, 97, 100, 103, 104, 106, 109, 112, 115, 116, 118, 120, 123, 124, 125, 133, 134, 135, 136, 141, 142, 144, 149, 150, 154, 160, 168, 169, 171, 178, 189, 190, 194, 195, 199, 202, 208, 221, 248, 262, 271, 273, 285, 286, 291, 293, 294, 308};
static const int kTypes_33[] = {69, 84, 106, 109, 112, 118, 120, 124, 125, 133, 141, 149, 150, 160, 178, 195, 286, 308};
static const int kTypes_34[] = {109, 112, 118, 124, 150, 160, 308};
static const int kTypes_35[] = {109, 160};
static const int kTypes_36[] = {1, 2, 3, 4, 6, 8, 9, 14, 16, 17, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 29, 30, 32, 33, 34, 35, 39, 40};
static const int kTypes_37[] = {3, 4, 9, 14, 17, 19, 21, 25, 26, 33, 34, 40};
static const int kTypes_38[] = {4, 9, 17, 33, 34};
static const int kTypes_39[] = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 18, 20, 23, 24, 27};
static const int kTypes_40[] = {2, 6, 7, 8, 9, 10, 11, 14, 18, 20, 27};
static const int kTypes_41[] = {7, 8, 11, 18, 20};
static const int kTypes_42[] = {2, 4, 6, 7};
static const int kTypes_43[] = {2, 7};
static const int kTypes_44[] = {2, 7};
static const int kTypes_45[] = {2};
static const int kTypes_46[] = {6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 25, 26, 27, 28, 32};
static const int kTypes_47[] = {7, 15, 26};
static const int kTypes_48[] = {1, 2, 3, 4, 5, 6, 7, 13, 14, 16};
static const int kTypes_49[] = {13, 14, 16};
static const int kTypes_50[] = {5, 13};
static const int kTypes_51[] = {1, 2, 4, 5, 7, 8, 9, 10, 12, 14, 15, 16, 17};
static const int kTypes_52[] = {2, 4, 5, 7, 9, 12, 14, 15, 16, 17};
static const int kTypes_53[] = {16};
static const sMutationParamRule kMutationParamRules[] = {
	{ "jos", "spinbox_mutation_jos_factor", "label_jos_factor", nullptr, 0, 0, 0, true },
	{ "jos", "spinbox_mutation_jos_param_a", "label_jos_param_a", kJosParamA, 14 },
	{ "jos", "spinbox_mutation_jos_param_b", "label_jos_param_b", kJosParamB, 9 },
	{ "jos", "spinbox_mutation_jos_param_c", "label_jos_param_c", kJosParamC, 6 },
	{ "jos", "spinbox_mutation_jos_param_d", "label_jos_param_d", nullptr, 0 },
	{ "jos", "spinbox_mutation_jos_phase", "label_jos_phase", kJosPhaseFreq, 4 },
	{ "jos", "spinbox_mutation_jos_freq", "label_jos_freq", kJosPhaseFreq, 4 },
	{ "jos", "spinbox_mutation_jos_amp", "label_jos_amp", nullptr, 0 },
	{ "jos", "spinbox_mutation_jos_scale", "label_jos_scale", nullptr, 0 },
	{ "pk", "spinbox_mutation_pk_factor", "label_pk_factor", nullptr, 0, 0, 0, true },
	{ "pk", "spinbox_mutation_pk_param_a", "label_pk_param_a", nullptr, 0, 7, 29 },
	{ "pk", "spinbox_mutation_pk_param_b", "label_pk_param_b", kPkParamB, 6 },
	{ "pk", "spinbox_mutation_pk_param_c", "label_pk_param_c", kPkParamC, 3 },
	{ "pk", "spinbox_mutation_pk_param_d", "label_pk_param_d", nullptr, 0 },
	{ "pk", "spinbox_mutation_pk_phase", "label_pk_phase", kPkPhaseFreq, 4 },
	{ "pk", "spinbox_mutation_pk_freq", "label_pk_freq", kPkPhaseFreq, 4 },
	{ "pk", "spinbox_mutation_pk_amp", "label_pk_amp", nullptr, 0 },
	{ "pk", "spinbox_mutation_pk_scale", "label_pk_scale", nullptr, 0 },
	{ "mb", "spinbox_mutation_math_p2", "label_mb_param_b", kTypes_10, 125 },
	{ "mb", "spinbox_mutation_math_p3", "label_mb_param_c", kTypes_11, 76 },
	{ "mb", "spinbox_mutation_math_p4", "label_mb_param_d", kTypes_12, 37 },
	{ "mb", "spinbox_mutation_math_p5", "label_mb_param_e", kTypes_13, 19 },
	{ "mb", "spinbox_mutation_math_p6", "label_mb_param_f", kTypes_14, 9 },
	{ "mb", "spinbox_mutation_math_p7", "label_mb_param_g", kTypes_15, 5 },
	{ "mb", "spinbox_mutation_math_p8", "label_mb_param_h", kTypes_16, 3 },
	{ "wd", "spinbox_mutation_wd_param_b", "label_wd_param_b", kTypes_17, 11 },
	{ "wd", "spinbox_mutation_wd_param_c", "label_wd_param_c", kTypes_18, 3 },
	{ "wd", "spinbox_mutation_wd_param_d", "label_wd_param_d", kTypes_19, 2 },
	{ "sk", "spinbox_mutation_sk_param_b", "label_sk_param_b", kTypes_20, 8 },
	{ "sk", "spinbox_mutation_sk_param_c", "label_sk_param_c", kTypes_21, 5 },
	{ "sk", "spinbox_mutation_sk_param_d", "label_sk_param_d", kTypes_22, 1 },
	{ "noise", "spinbox_mutation_noise_param_b", "label_noise_param_b", kTypes_23, 9 },
	{ "noise", "spinbox_mutation_noise_param_c", "label_noise_param_c", kTypes_24, 5 },
	{ "noise", "spinbox_mutation_noise_param_d", "label_noise_param_d", kTypes_25, 2 },
	{ "orbit", "spinbox_mutation_orbit_param_b", "label_orbit_param_b", kTypes_26, 18 },
	{ "orbit", "spinbox_mutation_orbit_param_c", "label_orbit_param_c", kTypes_27, 11 },
	{ "torus", "spinbox_mutation_torus_param_b", "label_torus_param_b", kTypes_28, 45 },
	{ "torus", "spinbox_mutation_torus_param_c", "label_torus_param_c", kTypes_29, 28 },
	{ "torus", "spinbox_mutation_torus_param_d", "label_torus_param_d", kTypes_30, 17 },
	{ "ab", "spinbox_mutation_ab_param_c", "label_ab_param_c", kTypes_31, 182 },
	{ "ab", "spinbox_mutation_ab_param_d", "label_ab_param_d", kTypes_32, 71 },
	{ "ab", "spinbox_mutation_ab_param_e", "label_ab_param_e", kTypes_33, 18 },
	{ "ab", "spinbox_mutation_ab_param_f", "label_ab_param_f", kTypes_34, 7 },
	{ "ab", "spinbox_mutation_ab_param_g", "label_ab_param_g", kTypes_35, 2 },
	{ "as", "spinbox_mutation_as_param_b", "label_mutation_as_param_b_lbl", kTypes_36, 28 },
	{ "as", "spinbox_mutation_as_param_c", "label_mutation_as_param_c_lbl", kTypes_37, 12 },
	{ "as", "spinbox_mutation_as_param_d", "label_mutation_as_param_d_lbl", kTypes_38, 5 },
	{ "sm", "spinbox_mutation_sm_param_b", "label_mutation_sm_param_b_lbl", kTypes_39, 18 },
	{ "sm", "spinbox_mutation_sm_param_c", "label_mutation_sm_param_c_lbl", kTypes_40, 11 },
	{ "sm", "spinbox_mutation_sm_param_d", "label_mutation_sm_param_d_lbl", kTypes_41, 5 },
	{ "blockify", "spinbox_mutation_blockify_param_b", "label_mutation_blockify_param_b_lbl", kTypes_42, 4 },
	{ "blockify", "spinbox_mutation_blockify_param_c", "label_mutation_blockify_param_c_lbl", kTypes_43, 2 },
	{ "tile", "spinbox_mutation_tile_param_b", "label_mutation_tile_param_b_lbl", kTypes_44, 2 },
	{ "tile", "spinbox_mutation_tile_param_c", "label_mutation_tile_param_c_lbl", kTypes_45, 1 },
	{ "clamp", "spinbox_mutation_clamp_param_b", "label_mutation_clamp_clamp_param_b", kTypes_46, 15 },
	{ "clamp", "spinbox_mutation_clamp_param_c", "label_mutation_clamp_clamp_param_c", kTypes_47, 3 },
	{ "jb", "spinbox_mutation_jb_param_b", "label_mutation_jb_jb_param_b", kTypes_48, 10 },
	{ "jb", "spinbox_mutation_jb_param_c", "label_mutation_jb_jb_param_c", kTypes_49, 3 },
	{ "jb", "spinbox_mutation_jb_param_d", "label_mutation_jb_jb_param_d", kTypes_50, 2 },
	{ "md", "spinbox_mutation_md_param_b", "label_mutation_md_param_b", kTypes_51, 13 },
	{ "md", "spinbox_mutation_md_param_c", "label_mutation_md_param_c", kTypes_52, 10 },
	{ "md", "spinbox_mutation_md_param_d", "label_mutation_md_param_d", kTypes_53, 1 },
	{ "de", "spinbox_mutation_de_scale", "label_mutation_de_scale", nullptr, 0, 0, 0, true },
	{ "de", "spinboxInt_mutation_de_iter_start", nullptr, nullptr, 0, 0, 0, true },
	{ "de", "spinboxInt_mutation_de_iter_stop", nullptr, nullptr, 0, 0, 0, true },
	{ "de", nullptr, "label_mutation_de_iter", nullptr, 0, 0, 0, true },
	{ "de", nullptr, "label_mutation_de_iter_s", nullptr, 0, 0, 0, true },
	{ "de", nullptr, "label_mutation_de_iter_e", nullptr, 0, 0, 0, true },
	{ "de", "spinbox_mutation_de_tweak_p1", "label_mutation_de_tweak_p1", kDeP1, 2 },
	{ "de", "spinbox_mutation_de_tweak_p2", "label_mutation_de_tweak_p2", kDeP2, 1 },
};

static const sMutationSystemBinding kMutationSystemBindings[] = {
	{ "jos", "groupCheck_mutation_jos_leys_enabled", "comboBox_mutation_jos_de_type" },
	{ "pk", "groupCheck_mutation_pk_enabled", "comboBox_mutation_pk_de_type" },
	{ "mb", "groupCheck_mutation_mb_math_enabled", "comboBox_mutation_mb_math_type" },
	{ "wd", "groupCheck_mutation_warp_dist_enabled", "comboBox_mutation_warp_dist_type" },
	{ "sk", "groupCheck_mutation_symmetry_enabled", "comboBox_mutation_sym_kal_type" },
	{ "noise", "groupCheck_mutation_noise_enabled", "comboBox_mutation_noise_type" },
	{ "orbit", "groupCheck_mutation_orbit_trap_enabled", "comboBox_mutation_orbit_trap_type" },
	{ "torus", "groupCheck_mutation_torus_enabled", "comboBox_mutation_torus_type" },
	{ "ab", "groupCheck_mutation_abox_enabled", "comboBox_mutation_abox_type" },
	{ "as", "groupCheck_mutation_as_enabled", "comboBox_mutation_as_type" },
	{ "sm", "groupCheck_mutation_sm_enabled", "comboBox_mutation_sm_type" },
	{ "blockify", "groupCheck_mutation_blockify_enabled", "comboBox_mutation_blockify_type" },
	{ "tile", "groupCheck_mutation_tile_enabled", "comboBox_mutation_tile_type" },
	{ "clamp", "groupCheck_mutation_clamp_enabled", "comboBox_mutation_clamp_type" },
	{ "jb", "groupCheck_mutation_jb_enabled", "comboBox_mutation_jb_type" },
	{ "md", "groupCheck_mutation_md_enabled", "comboBox_mutation_md_type" },
};
} // namespace

const sMutationParamRule *cMutationUiRegistry::ParamRulesData() { return kMutationParamRules; }
int cMutationUiRegistry::ParamRulesCount() { return int(sizeof(kMutationParamRules)/sizeof(kMutationParamRules[0])); }
const sMutationSystemBinding *cMutationUiRegistry::SystemBindingsData() { return kMutationSystemBindings; }
int cMutationUiRegistry::SystemBindingsCount() { return int(sizeof(kMutationSystemBindings)/sizeof(kMutationSystemBindings[0])); }