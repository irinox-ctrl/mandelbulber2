#!/usr/bin/env python3
"""
Generate mutation UI gray-out registry from compute_fractal.cpp switch analysis.

Writes:
  src/mutation_ui_registry_data.cpp
  src/mutation_ui_registry_extended_data.cpp  (clip/inv rules; julia rules preserved)

Usage:
  python3 generate_mutation_ui_registry.py
"""

from __future__ import annotations

import re
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

ROOT = Path(__file__).resolve().parent.parent.parent
CPU_FILE = ROOT / "src" / "compute_fractal.cpp"
OUT_MAIN = ROOT / "src" / "mutation_ui_registry_data.cpp"
OUT_EXT = ROOT / "src" / "mutation_ui_registry_extended_data.cpp"

sys.path.insert(0, str(Path(__file__).resolve().parent))
import port_cpu_de_cases as port  # noqa: E402


@dataclass
class ParamSpec:
    local_patterns: Sequence[str]
    spin: str
    label: Optional[str] = None
    always_active: bool = False


@dataclass
class DeSystemSpec:
    system_id: str
    marker: str
    switch_pattern: str
    group: str
    combo: str
    params: List[ParamSpec] = field(default_factory=list)


@dataclass
class ClipInvSpec:
    system_id: str
    switch_pattern: str
    group: str
    combo: str
    params: List[ParamSpec] = field(default_factory=list)


def var_used(body: str, patterns: Sequence[str]) -> bool:
    for pat in patterns:
        if re.search(pat, body):
            return True
    return False


def types_for_patterns(cases: Dict[int, str], patterns: Sequence[str]) -> List[int]:
    return sorted(n for n, body in cases.items() if var_used(body, patterns))


def extract_switch_cases(cpu: str, switch_pattern: str, marker: Optional[str] = None) -> Dict[int, str]:
    start = 0
    if marker:
        start = port.find_marker_pos(cpu, marker)
    _, _, body = port.find_switch_body(cpu, switch_pattern, start)
    return port.extract_cases(body)


def fmt_type_array(name: str, types: Sequence[int]) -> str:
    if not types:
        return ""
    chunks = []
    line = f"static const int {name}[] = {{"
    for i, t in enumerate(types):
        sep = ", " if i else " "
        if i and i % 20 == 0:
            chunks.append(line)
            line = "    "
        line += f"{sep}{t}"
    line += " };"
    chunks.append(line)
    return "\n".join(chunks)


def fmt_rule(
    system_id: str,
    spin: Optional[str],
    label: Optional[str],
    types: Sequence[int],
    always: bool = False,
    min_t: int = 0,
    max_t: int = 0,
) -> str:
    spin_s = f'"{spin}"' if spin else "nullptr"
    label_s = f'"{label}"' if label else "nullptr"
    if always:
        return (
            f'\t{{ "{system_id}", {spin_s}, {label_s}, '
            f"nullptr, 0, 0, 0, true }},"
        )
    if types:
        arr = f"k_{system_id}_{spin or label or 'x'}".replace("-", "_")
        arr = re.sub(r"[^a-zA-Z0-9_]", "_", arr)
        return (
            f'\t{{ "{system_id}", {spin_s}, {label_s}, '
            f"{arr}, {len(types)} }},"
        )
    if max_t >= min_t and min_t > 0:
        return (
            f'\t{{ "{system_id}", {spin_s}, {label_s}, '
            f"nullptr, 0, {min_t}, {max_t}, false }},"
        )
    return f'\t{{ "{system_id}", {spin_s}, {label_s}, nullptr, 0 }},'


def de_param(prefix: str, letter: str, label_prefix: Optional[str] = None) -> ParamSpec:
    lp = label_prefix or prefix
    return ParamSpec(
        [rf"\b{letter}\b"],
        f"spinbox_mutation_{prefix}_param_{letter[-1]}",
        f"label_{lp}_param_{letter[-1]}",
    )


def standard_de_params(prefix: str, local_letters: str, label_prefix: Optional[str] = None) -> List[ParamSpec]:
    lp = label_prefix or prefix
    out: List[ParamSpec] = []
    for ch in local_letters:
        if ch == "f" and len(local_letters) > 1:
            # skip composite factor locals (mf, pf, jf, …)
            continue
        letter = {"a": "a", "b": "b", "c": "c", "d": "d", "e": "e", "f": "f", "g": "g", "h": "h"}[ch]
        if ch == "f" and prefix in ("mb",):
            continue
        loc = {"a": "a", "b": "b", "c": "c", "d": "d", "e": "e", "f": "ff", "g": "g", "h": "h"}.get(ch, ch)
        if prefix == "mb" and ch == "f":
            loc = "mff"
        elif prefix == "ab" and ch == "f":
            loc = "aff"
        out.append(
            ParamSpec(
                [rf"\b{loc}\b"],
                f"spinbox_mutation_{prefix}_param_{letter}",
                f"label_{lp}_param_{letter}" if lp != "mutation_as" else f"label_mutation_{prefix}_param_{letter}_lbl",
            )
        )
    return out


DE_SYSTEMS: List[DeSystemSpec] = [
    DeSystemSpec(
        "jos", "v7.7 — Jos Leys DE system", r"switch\s*\(\s*mut\.josLeysDeType\s*\)",
        "groupCheck_mutation_jos_leys_enabled", "comboBox_mutation_jos_de_type",
        [
            ParamSpec([], "spinbox_mutation_jos_factor", "label_jos_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_jos_iter_start", "label_jos_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_jos_iter_stop", "label_jos_iter_stop", always_active=True),
            ParamSpec([r"\bja\b"], "spinbox_mutation_jos_param_a", "label_jos_param_a"),
            ParamSpec([r"\bjb\b"], "spinbox_mutation_jos_param_b", "label_jos_param_b"),
            ParamSpec([r"\bjc\b"], "spinbox_mutation_jos_param_c", "label_jos_param_c"),
            ParamSpec([r"\bjd\b"], "spinbox_mutation_jos_param_d", "label_jos_param_d"),
            ParamSpec([r"\bjph\b"], "spinbox_mutation_jos_phase", "label_jos_phase"),
            ParamSpec([r"\bjfreq\b"], "spinbox_mutation_jos_freq", "label_jos_freq"),
            ParamSpec([r"\bjamp\b"], "spinbox_mutation_jos_amp", "label_jos_amp"),
            ParamSpec([r"\bjsc\b"], "spinbox_mutation_jos_scale", "label_jos_scale"),
        ],
    ),
    DeSystemSpec(
        "pk", "v7.7 — Pseudokleinian DE system", r"switch\s*\(\s*mut\.pseudoKleinianDeType\s*\)",
        "groupCheck_mutation_pk_enabled", "comboBox_mutation_pk_de_type",
        [
            ParamSpec([], "spinbox_mutation_pk_factor", "label_pk_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_pk_iter_start", "label_pk_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_pk_iter_stop", "label_pk_iter_stop", always_active=True),
            ParamSpec([r"\bpa\b"], "spinbox_mutation_pk_param_a", "label_pk_param_a"),
            ParamSpec([r"\bpb\b"], "spinbox_mutation_pk_param_b", "label_pk_param_b"),
            ParamSpec([r"\bpc\b"], "spinbox_mutation_pk_param_c", "label_pk_param_c"),
            ParamSpec([r"\bpd\b"], "spinbox_mutation_pk_param_d", "label_pk_param_d"),
            ParamSpec([r"\bpph\b"], "spinbox_mutation_pk_phase", "label_pk_phase"),
            ParamSpec([r"\bpfreq\b"], "spinbox_mutation_pk_freq", "label_pk_freq"),
            ParamSpec([r"\bpamp\b"], "spinbox_mutation_pk_amp", "label_pk_amp"),
            ParamSpec([r"\bpsc\b"], "spinbox_mutation_pk_scale", "label_pk_scale"),
        ],
    ),
    DeSystemSpec(
        "mb", "v7.8 — Mandelbox Math system", r"switch\s*\(\s*mut\.mbMathType\s*\)",
        "groupCheck_mutation_mb_math_enabled", "comboBox_mutation_mb_math_type",
        [
            ParamSpec([], "spinbox_mutation_mb_factor", "label_mb_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_mb_iter_start", "label_mb_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_mb_iter_stop", "label_mb_iter_stop", always_active=True),
            ParamSpec([r"\bma\b"], "spinbox_mutation_mb_param_a", "label_mb_param_a"),
            ParamSpec([r"\bmb\b"], "spinbox_mutation_mb_param_b", "label_mb_param_b"),
            ParamSpec([r"\bmc\b"], "spinbox_mutation_mb_param_c", "label_mb_param_c"),
            ParamSpec([r"\bmd\b"], "spinbox_mutation_mb_param_d", "label_mb_param_d"),
            ParamSpec([r"\bme\b"], "spinbox_mutation_mb_param_e", "label_mb_param_e"),
            ParamSpec([r"\bmff\b"], "spinbox_mutation_mb_param_f", "label_mb_param_f"),
            ParamSpec([r"\bmg\b"], "spinbox_mutation_mb_param_g", "label_mb_param_g"),
            ParamSpec([r"\bmh\b"], "spinbox_mutation_mb_param_h", "label_mb_param_h"),
        ],
    ),
    DeSystemSpec(
        "wd", "v7.9 — Warp Distortion system", r"switch\s*\(\s*mut\.warpDistType\s*\)",
        "groupCheck_mutation_warp_dist_enabled", "comboBox_mutation_warp_dist_type",
        [
            ParamSpec([], "spinbox_mutation_wd_factor", "label_wd_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_wd_iter_start", "label_wd_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_wd_iter_stop", "label_wd_iter_stop", always_active=True),
            ParamSpec([r"\bwa\b"], "spinbox_mutation_wd_param_a", "label_wd_param_a"),
            ParamSpec([r"\bwb\b"], "spinbox_mutation_wd_param_b", "label_wd_param_b"),
            ParamSpec([r"\bwc\b"], "spinbox_mutation_wd_param_c", "label_wd_param_c"),
            ParamSpec([r"\bwd\b"], "spinbox_mutation_wd_param_d", "label_wd_param_d"),
            ParamSpec([r"\bwfq\b"], "spinbox_mutation_wd_freq", "label_wd_freq"),
            ParamSpec([r"\bwam\b"], "spinbox_mutation_wd_amp", "label_wd_amp"),
            ParamSpec([r"\bwsc\b"], "spinbox_mutation_wd_scale", "label_wd_scale"),
            ParamSpec([r"\bwph\b"], "spinbox_mutation_wd_phase", "label_wd_phase"),
        ],
    ),
    DeSystemSpec(
        "sk", "v7.9 — Symmetry/Kaleidoscope system", r"switch\s*\(\s*mut\.symKalType\s*\)",
        "groupCheck_mutation_symmetry_enabled", "comboBox_mutation_sym_kal_type",
        [
            ParamSpec([], "spinbox_mutation_sk_factor", "label_sk_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_sk_iter_start", "label_sk_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_sk_iter_stop", "label_sk_iter_stop", always_active=True),
            ParamSpec([r"\bsa\b"], "spinbox_mutation_sk_param_a", "label_sk_param_a"),
            ParamSpec([r"\bsb\b"], "spinbox_mutation_sk_param_b", "label_sk_param_b"),
            ParamSpec([r"\bsc\b"], "spinbox_mutation_sk_param_c", "label_sk_param_c"),
            ParamSpec([r"\bsd\b"], "spinbox_mutation_sk_param_d", "label_sk_param_d"),
            ParamSpec([r"\bsfq\b"], "spinbox_mutation_sk_freq", "label_sk_freq"),
            ParamSpec([r"\bsam\b"], "spinbox_mutation_sk_amp", "label_sk_amp"),
            ParamSpec([r"\bsang\b"], "spinbox_mutation_sk_angle", "label_sk_angle"),
            ParamSpec([r"\bsoff\b"], "spinbox_mutation_sk_offset", "label_sk_offset"),
        ],
    ),
    DeSystemSpec(
        "ab", "v7.9 — Abox DE system", r"switch\s*\(\s*mut\.aboxType\s*\)",
        "groupCheck_mutation_abox_enabled", "comboBox_mutation_abox_type",
        [
            ParamSpec([], "spinbox_mutation_ab_factor", "label_ab_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_ab_iter_start", "label_ab_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_ab_iter_stop", "label_ab_iter_stop", always_active=True),
            ParamSpec([r"\baa\b"], "spinbox_mutation_ab_param_a", "label_ab_param_a"),
            ParamSpec([r"\bab\b"], "spinbox_mutation_ab_param_b", "label_ab_param_b"),
            ParamSpec([r"\bac\b"], "spinbox_mutation_ab_param_c", "label_ab_param_c"),
            ParamSpec([r"\bad\b"], "spinbox_mutation_ab_param_d", "label_ab_param_d"),
            ParamSpec([r"\bae\b"], "spinbox_mutation_ab_param_e", "label_ab_param_e"),
            ParamSpec([r"\baff\b"], "spinbox_mutation_ab_param_f", "label_ab_param_f"),
            ParamSpec([r"\bag\b"], "spinbox_mutation_ab_param_g", "label_ab_param_g"),
            ParamSpec([r"\bah\b"], "spinbox_mutation_ab_param_h", "label_ab_param_h"),
        ],
    ),
    DeSystemSpec(
        "noise", "v7.10 — Noise & Procedural DE system", r"switch\s*\(\s*mut\.noiseType\s*\)",
        "groupCheck_mutation_noise_enabled", "comboBox_mutation_noise_type",
        [
            ParamSpec([], "spinbox_mutation_noise_factor", "label_noise_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_noise_iter_start", "label_noise_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_noise_iter_stop", "label_noise_iter_stop", always_active=True),
            ParamSpec([r"\bna\b"], "spinbox_mutation_noise_param_a", "label_noise_param_a"),
            ParamSpec([r"\bnb\b"], "spinbox_mutation_noise_param_b", "label_noise_param_b"),
            ParamSpec([r"\bnc\b"], "spinbox_mutation_noise_param_c", "label_noise_param_c"),
            ParamSpec([r"\bnd\b"], "spinbox_mutation_noise_param_d", "label_noise_param_d"),
            ParamSpec([r"\bnfq\b"], "spinbox_mutation_noise_freq", "label_noise_freq"),
            ParamSpec([r"\bnam\b"], "spinbox_mutation_noise_amp", "label_noise_amp"),
        ],
    ),
    DeSystemSpec(
        "orbit", "v7.10 — Orbit Trap DE system", r"switch\s*\(\s*mut\.orbitTrapType\s*\)",
        "groupCheck_mutation_orbit_trap_enabled", "comboBox_mutation_orbit_trap_type",
        [
            ParamSpec([], "spinbox_mutation_orbit_factor", "label_orbit_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_orbit_iter_start", "label_orbit_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_orbit_iter_stop", "label_orbit_iter_stop2", always_active=True),
            ParamSpec([r"\boa\b"], "spinbox_mutation_orbit_param_a", "label_orbit_param_a"),
            ParamSpec([r"\bob\b"], "spinbox_mutation_orbit_param_b", "label_orbit_param_b"),
            ParamSpec([r"\boc\b"], "spinbox_mutation_orbit_param_c", "label_orbit_param_c"),
            ParamSpec([r"\bod\b"], "spinbox_mutation_orbit_param_d", "label_orbit_param_d"),
        ],
    ),
    DeSystemSpec(
        "torus", "v7.12 — MandelTorus DE system", r"switch\s*\(\s*mut\.torusType\s*\)",
        "groupCheck_mutation_torus_enabled", "comboBox_mutation_torus_type",
        [
            ParamSpec([], "spinbox_mutation_torus_factor", "label_torus_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_torus_iter_start", "label_torus_iter", always_active=True),
            ParamSpec([], "spinboxInt_mutation_torus_iter_stop", "label_torus_iter_stop2", always_active=True),
            ParamSpec([r"\bta\b"], "spinbox_mutation_torus_param_a", "label_torus_param_a"),
            ParamSpec([r"\btb\b"], "spinbox_mutation_torus_param_b", "label_torus_param_b"),
            ParamSpec([r"\btc\b"], "spinbox_mutation_torus_param_c", "label_torus_param_c"),
            ParamSpec([r"\btd\b"], "spinbox_mutation_torus_param_d", "label_torus_param_d"),
        ],
    ),
    DeSystemSpec(
        "as", "v7.13 — Amazing Surf 1-4 DE system", r"switch\s*\(\s*mut\.asType\s*\)",
        "groupCheck_mutation_as_enabled", "comboBox_mutation_as_type",
        [
            ParamSpec([], "spinbox_mutation_as_factor", "label_mutation_as_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_as_iter_start", "label_mutation_as_iter_start", always_active=True),
            ParamSpec([], "spinboxInt_mutation_as_iter_stop", "label_mutation_as_iter_stop", always_active=True),
            ParamSpec([r"\bta\b"], "spinbox_mutation_as_param_a", "label_mutation_as_param_a_lbl"),
            ParamSpec([r"\btb\b"], "spinbox_mutation_as_param_b", "label_mutation_as_param_b_lbl"),
            ParamSpec([r"\btc\b"], "spinbox_mutation_as_param_c", "label_mutation_as_param_c_lbl"),
            ParamSpec([r"\btd\b"], "spinbox_mutation_as_param_d", "label_mutation_as_param_d_lbl"),
        ],
    ),
]

MORE_DE_SYSTEMS = [
    DeSystemSpec(
        "sm", "v7.13 — SphereTree/Menger DE system", r"switch\s*\(\s*mut\.smType\s*\)",
        "groupCheck_mutation_sm_enabled", "comboBox_mutation_sm_type",
        [
            ParamSpec([], "spinbox_mutation_sm_factor", "label_mutation_sm_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_sm_iter_start", "label_mutation_sm_iter_start", always_active=True),
            ParamSpec([], "spinboxInt_mutation_sm_iter_stop", "label_mutation_sm_iter_stop", always_active=True),
            ParamSpec([r"\bta\b"], "spinbox_mutation_sm_param_a", "label_mutation_sm_param_a_lbl"),
            ParamSpec([r"\btb\b"], "spinbox_mutation_sm_param_b", "label_mutation_sm_param_b_lbl"),
            ParamSpec([r"\btc\b"], "spinbox_mutation_sm_param_c", "label_mutation_sm_param_c_lbl"),
            ParamSpec([r"\btd\b"], "spinbox_mutation_sm_param_d", "label_mutation_sm_param_d_lbl"),
        ],
    ),
    DeSystemSpec(
        "blockify", "v7.15 — Blockify system", r"switch\s*\(\s*mut\.blockifyType\s*\)",
        "groupCheck_mutation_blockify_enabled", "comboBox_mutation_blockify_type",
        [
            ParamSpec([], "spinbox_mutation_blockify_factor", "label_mutation_blockify_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_blockify_iter_start", "label_mutation_blockify_iter_start", always_active=True),
            ParamSpec([], "spinboxInt_mutation_blockify_iter_stop", "label_mutation_blockify_iter_stop", always_active=True),
            ParamSpec([r"\bta\b"], "spinbox_mutation_blockify_param_a", "label_mutation_blockify_param_a_lbl"),
            ParamSpec([r"\btb\b"], "spinbox_mutation_blockify_param_b", "label_mutation_blockify_param_b_lbl"),
            ParamSpec([r"\btc\b"], "spinbox_mutation_blockify_param_c", "label_mutation_blockify_param_c_lbl"),
            ParamSpec([r"\btd\b"], "spinbox_mutation_blockify_param_d", "label_mutation_blockify_param_d_lbl"),
        ],
    ),
    DeSystemSpec(
        "tile", "v7.15 — Tile system", r"switch\s*\(\s*mut\.tileType\s*\)",
        "groupCheck_mutation_tile_enabled", "comboBox_mutation_tile_type",
        [
            ParamSpec([], "spinbox_mutation_tile_factor", "label_mutation_tile_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_tile_iter_start", "label_mutation_tile_iter_start", always_active=True),
            ParamSpec([], "spinboxInt_mutation_tile_iter_stop", "label_mutation_tile_iter_stop", always_active=True),
            ParamSpec([r"\bta\b"], "spinbox_mutation_tile_param_a", "label_mutation_tile_param_a_lbl"),
            ParamSpec([r"\btb\b"], "spinbox_mutation_tile_param_b", "label_mutation_tile_param_b_lbl"),
            ParamSpec([r"\btc\b"], "spinbox_mutation_tile_param_c", "label_mutation_tile_param_c_lbl"),
            ParamSpec([r"\btd\b"], "spinbox_mutation_tile_param_d", "label_mutation_tile_param_d_lbl"),
        ],
    ),
    DeSystemSpec(
        "clamp", "v7.14 — T Clamp system", r"switch\s*\(\s*mut\.clampType\s*\)",
        "groupCheck_mutation_clamp_enabled", "comboBox_mutation_clamp_type",
        [
            ParamSpec([], "spinbox_mutation_clamp_factor", "label_mutation_clamp_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_clamp_iter_start", "label_mutation_clamp_iter_start", always_active=True),
            ParamSpec([], "spinboxInt_mutation_clamp_iter_stop", "label_mutation_clamp_iter_stop", always_active=True),
            ParamSpec([r"\bta\b"], "spinbox_mutation_clamp_param_a", "label_mutation_clamp_clamp_param_a"),
            ParamSpec([r"\btb\b"], "spinbox_mutation_clamp_param_b", "label_mutation_clamp_clamp_param_b"),
            ParamSpec([r"\btc\b"], "spinbox_mutation_clamp_param_c", "label_mutation_clamp_clamp_param_c"),
            ParamSpec([r"\btd\b"], "spinbox_mutation_clamp_param_d", "label_mutation_clamp_clamp_param_d"),
        ],
    ),
    DeSystemSpec(
        "jb", "v7.14 — T Julia Box system", r"switch\s*\(\s*mut\.jbType\s*\)",
        "groupCheck_mutation_jb_enabled", "comboBox_mutation_jb_type",
        [
            ParamSpec([], "spinbox_mutation_jb_factor", "label_mutation_jb_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_jb_iter_start", "label_mutation_jb_iter_start", always_active=True),
            ParamSpec([], "spinboxInt_mutation_jb_iter_stop", "label_mutation_jb_iter_stop", always_active=True),
            ParamSpec([r"\bta\b"], "spinbox_mutation_jb_param_a", "label_mutation_jb_jb_param_a"),
            ParamSpec([r"\btb\b"], "spinbox_mutation_jb_param_b", "label_mutation_jb_jb_param_b"),
            ParamSpec([r"\btc\b"], "spinbox_mutation_jb_param_c", "label_mutation_jb_jb_param_c"),
            ParamSpec([r"\btd\b"], "spinbox_mutation_jb_param_d", "label_mutation_jb_jb_param_d"),
        ],
    ),
    DeSystemSpec(
        "md", "v7.14 — T Mandalay system", r"switch\s*\(\s*mut\.mdType\s*\)",
        "groupCheck_mutation_md_enabled", "comboBox_mutation_md_type",
        [
            ParamSpec([], "spinbox_mutation_md_factor", "label_mutation_md_factor", always_active=True),
            ParamSpec([], "spinboxInt_mutation_md_iter_start", "label_mutation_md_iter_start", always_active=True),
            ParamSpec([], "spinboxInt_mutation_md_iter_stop", "label_mutation_md_iter_stop", always_active=True),
            ParamSpec([r"\bta\b"], "spinbox_mutation_md_param_a", "label_mutation_md_param_a"),
            ParamSpec([r"\btb\b"], "spinbox_mutation_md_param_b", "label_mutation_md_param_b"),
            ParamSpec([r"\btc\b"], "spinbox_mutation_md_param_c", "label_mutation_md_param_c"),
            ParamSpec([r"\btd\b"], "spinbox_mutation_md_param_d", "label_mutation_md_param_d"),
        ],
    ),
]

ALL_DE = DE_SYSTEMS + MORE_DE_SYSTEMS

CLIP_PARAMS = [
    ParamSpec([], "spinbox_mutation_clip_center_ax", "label_clip_center", always_active=True),
    ParamSpec([], "spinbox_mutation_clip_center_ay", "label_clip_center_y", always_active=True),
    ParamSpec([], "spinbox_mutation_clip_center_az", "label_clip_center_z", always_active=True),
    ParamSpec([], "spinboxInt_mutation_clip_boolean_op", "label_clip_bool", always_active=True),
    ParamSpec([], "spinboxInt_mutation_clip_iter_start", "label_clip_iter_start", always_active=True),
    ParamSpec([], "spinboxInt_mutation_clip_iter_stop", "label_clip_iter_stop", always_active=True),
    ParamSpec([], "spinbox_mutation_clip_pre_rot_ax", "label_clip_prerot_x", always_active=True),
    ParamSpec([], "spinbox_mutation_clip_pre_rot_ay", "label_clip_prerot_y", always_active=True),
    ParamSpec([], "spinbox_mutation_clip_pre_rot_az", "label_clip_prerot_z", always_active=True),
    ParamSpec([r"\bsx\b"], "spinbox_mutation_clip_size_ax", "label_clip_size"),
    ParamSpec([r"\bsy\b"], "spinbox_mutation_clip_size_ay", "label_clip_size_y"),
    ParamSpec([r"\bsz\b"], "spinbox_mutation_clip_size_az", "label_clip_size_z"),
    ParamSpec([r"\bcr\b"], "spinbox_mutation_clip_radius", "label_clip_radius"),
    ParamSpec([r"\bcR\b"], "spinbox_mutation_clip_major_radius", "label_clip_major_r"),
    ParamSpec([r"mut\.clipAngle"], "spinbox_mutation_clip_angle", "label_clip_angle"),
    ParamSpec([r"mut\.clipFrequency"], "spinbox_mutation_clip_frequency", "label_clip_freq"),
    ParamSpec([r"mut\.clipAmplitude"], "spinbox_mutation_clip_amplitude", "label_clip_amp"),
    ParamSpec([r"mut\.clipSmoothK"], "spinbox_mutation_clip_smooth_k", "label_clip_smooth"),
    ParamSpec([r"mut\.clipNPoints"], "spinboxInt_mutation_clip_n_points", "label_clip_npoints"),
    ParamSpec([r"\bca\b"], "spinbox_mutation_clip_param_a", "label_clip_param"),
    ParamSpec([r"\bcb\b"], "spinbox_mutation_clip_param_b", "label_clip_param_b"),
    ParamSpec([r"\bcc\b"], "spinbox_mutation_clip_param_c", "label_clip_param_c"),
    ParamSpec([r"mut\.clipThreshold"], "spinbox_mutation_clip_threshold", "label_clip_threshold"),
]

INV_PARAMS = [
    ParamSpec([], "spinbox_mutation_inv_center_ax", "label_inv_center", always_active=True),
    ParamSpec([], "spinbox_mutation_inv_center_ay", None, always_active=True),
    ParamSpec([], "spinbox_mutation_inv_center_az", None, always_active=True),
    ParamSpec([], "spinboxInt_mutation_inv_iter_start", "label_inv_iter", always_active=True),
    ParamSpec([], "spinboxInt_mutation_inv_iter_stop", "label_inv_iter_stop", always_active=True),
    ParamSpec([], "spinbox_mutation_inv_pre_rot_ax", "label_inv_prerot_x", always_active=True),
    ParamSpec([], "spinbox_mutation_inv_pre_rot_ay", "label_inv_prerot_y", always_active=True),
    ParamSpec([], "spinbox_mutation_inv_pre_rot_az", "label_inv_prerot_z", always_active=True),
    ParamSpec([r"\biR\b"], "spinbox_mutation_inv_radius", "label_inv_radius"),
    ParamSpec([r"\bia\b"], "spinbox_mutation_inv_param_a", "label_inv_param_a"),
    ParamSpec([r"\bib\b"], "spinbox_mutation_inv_param_b", "label_inv_param_b"),
    ParamSpec([r"\bic\b"], "spinbox_mutation_inv_param_c", "label_inv_param_c"),
    ParamSpec([r"mut\.invAngle"], "spinbox_mutation_inv_angle", "label_inv_angle"),
    ParamSpec([r"mut\.invFrequency"], "spinbox_mutation_inv_frequency", "label_inv_freq"),
    ParamSpec([r"mut\.invAmplitude"], "spinbox_mutation_inv_amplitude", "label_inv_amp"),
    ParamSpec([r"mut\.invScale"], "spinbox_mutation_inv_scale", "label_inv_scale"),
    ParamSpec([r"mut\.invWeight"], "spinbox_mutation_inv_weight", "label_inv_weight"),
    ParamSpec([r"mut\.invNSteps"], "spinboxInt_mutation_inv_n_steps", "label_inv_nsteps"),
    ParamSpec([r"mut\.invThreshold"], "spinbox_mutation_inv_threshold", "label_inv_threshold"),
    ParamSpec([r"mut\.invColorFactor"], "spinbox_mutation_inv_color_factor", "label_inv_colorfactor"),
    ParamSpec([r"mut\.invCenter2X"], "spinbox_mutation_inv_center2_ax", "label_inv_center2"),
    ParamSpec([r"mut\.invCenter2Y"], "spinbox_mutation_inv_center2_ay", None),
    ParamSpec([r"mut\.invCenter2Z"], "spinbox_mutation_inv_center2_az", None),
    ParamSpec([r"mut\.invRadius2"], "spinbox_mutation_inv_radius2", "label_inv_radius2"),
    ParamSpec([r"mut\.invMinR"], "spinbox_mutation_inv_min_r", "label_inv_minr"),
    ParamSpec([r"mut\.invMaxR"], "spinbox_mutation_inv_max_r", "label_inv_maxr"),
]

INLINE_DE_RULES = [
    ("de", [
        ParamSpec([], "spinbox_mutation_de_scale", "label_mutation_de_scale", always_active=True),
        ParamSpec([], "spinboxInt_mutation_de_iter_start", "label_mutation_de_iter", always_active=True),
        ParamSpec([], "spinboxInt_mutation_de_iter_stop", "label_mutation_de_iter_e", always_active=True),
        ParamSpec([r"mut\.deTweakP1"], "spinbox_mutation_de_tweak_p1", "label_mutation_de_tweak_p1"),
        ParamSpec([r"mut\.deTweakP2"], "spinbox_mutation_de_tweak_p2", "label_mutation_de_tweak_p2"),
    ]),
]

DE_P1_TYPES = [3, 4]
DE_P2_TYPES = [4]

HEADER_FILE = ROOT / "src" / "nine_fractals.hpp"


def parse_enum_lines(enum_name: str, header: Optional[str] = None) -> Dict[str, int]:
    text = header if header is not None else HEADER_FILE.read_text(encoding="utf-8")
    m = re.search(rf"enum {enum_name}\s*\{{(.*?)\n\}};", text, re.S)
    if not m:
        raise ValueError(f"Enum not found: {enum_name}")
    out: Dict[str, int] = {}
    next_val = 0
    for line in m.group(1).splitlines():
        line = line.split("//")[0].strip().rstrip(",")
        if not line:
            continue
        mm = re.match(r"(\w+)(?:\s*=\s*(\d+))?", line)
        if not mm:
            continue
        key = mm.group(1)
        if mm.group(2) is not None:
            next_val = int(mm.group(2))
        out[key] = next_val
        next_val += 1
    return out


def enum_switch_cases_v2(body: str, enum_map: Dict[str, int]) -> Dict[int, str]:
    cases: Dict[int, str] = {}
    positions: List[Tuple[int, Optional[str]]] = []
    for m in re.finditer(r"case\s+(\w+)\s*:", body):
        positions.append((m.start(), m.group(1)))
    positions.append((len(body), None))
    for i in range(len(positions) - 1):
        name = positions[i][1]
        chunk = body[positions[i][0] : positions[i + 1][0]]
        chunk = re.sub(r"^case\s+\w+\s*:", "", chunk, count=1)
        if name and name in enum_map:
            cases[enum_map[name]] = chunk
    return cases


def extract_balanced_body(text: str, open_brace: int) -> str:
    depth = 0
    for i in range(open_brace, len(text)):
        ch = text[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                return text[open_brace + 1 : i]
    raise ValueError("Balanced brace body not found")


def extract_fold_cases(cpu: str) -> Dict[int, str]:
    pos = cpu.find("switch (foldType)")
    if pos < 0:
        raise ValueError("fold switch not found")
    brace = cpu.find("{", pos)
    body = extract_balanced_body(cpu, brace)
    return enum_switch_cases_v2(body, parse_enum_lines("enumMutationFoldType"))


def extract_warp_cases(cpu: str) -> Dict[int, str]:
    enum_map = parse_enum_lines("enumMutationWarpType")
    block_start = cpu.find("if (mut.warpType == mutWarpSine)")
    block_end = cpu.find("} // end warp iteration", block_start)
    block = cpu[block_start:block_end]
    cases: Dict[int, str] = {}
    for enum_name, type_id in enum_map.items():
        if type_id == 0:
            continue
        m = re.search(
            rf"(?:if|else if)\s*\(\s*mut\.warpType\s*==\s*{enum_name}\s*\)\s*\{{",
            block,
        )
        if not m:
            continue
        brace = m.end() - 1
        cases[type_id] = extract_balanced_body(block, brace)
    return cases


def extract_math_cases(cpu: str) -> Dict[int, str]:
    pos = cpu.find("switch (mut.mathType)")
    _, _, body = port.find_switch_body(cpu, r"switch\s*\(\s*mut\.mathType\s*\)", max(0, pos - 20))
    return enum_switch_cases_v2(body, parse_enum_lines("enumMutationMathType"))


def extract_trap_cases(cpu: str) -> Dict[int, str]:
    pos = cpu.find("switch (mut.orbitTrap)")
    brace = cpu.find("{", pos)
    body = extract_balanced_body(cpu, brace)
    return enum_switch_cases_v2(body, parse_enum_lines("enumMutationOrbitTrap"))


INLINE_SYSTEM_SPECS: List[Tuple[str, List[ParamSpec]]] = [
    ("fold", [
        ParamSpec([], "spinboxInt_mutation_fold_iter_start", "label_mutation_fold_iter", always_active=True),
        ParamSpec([], "spinboxInt_mutation_fold_iter_stop", "label_mutation_fold_iter_e", always_active=True),
        ParamSpec([], None, "label_mutation_fold_iter_s", always_active=True),
        ParamSpec([], None, "label_mutation_fold_position", always_active=True),
        ParamSpec([r"\bfoldLimit\b"], "spinbox_mutation_fold_limit", "label_mutation_fold_limit"),
        ParamSpec([r"\bfoldValue\b"], "spinbox_mutation_fold_value", "label_mutation_fold_value"),
        ParamSpec([r"\bkaleidoscopeSides\b"], "spinboxInt_mutation_kaleidoscope_sides", "label_mutation_kaleidoscope_sides"),
    ]),
    ("warp", [
        ParamSpec([], "spinboxInt_mutation_warp_iter_start", "label_mutation_warp_iter", always_active=True),
        ParamSpec([], "spinboxInt_mutation_warp_iter_stop", "label_mutation_warp_iter_e", always_active=True),
        ParamSpec([], None, "label_mutation_warp_iter_s", always_active=True),
        ParamSpec([r"effectiveWarpAmp"], "spinbox_mutation_warp_amplitude", "label_mutation_warp_amp", always_active=True),
        ParamSpec([r"mut\.warpFrequency"], "spinbox_mutation_warp_frequency", "label_mutation_warp_freq"),
    ]),
    ("math", [
        ParamSpec([], "spinboxInt_mutation_math_iter_start", "label_mutation_math_iter", always_active=True),
        ParamSpec([], "spinboxInt_mutation_math_iter_stop", "label_mutation_math_iter_e", always_active=True),
        ParamSpec([], None, "label_mutation_math_iter_s", always_active=True),
        ParamSpec([], "spinbox_mutation_math_mix", "label_mutation_math_mix", always_active=True),
        ParamSpec([r"effectiveMathP1"], "spinbox_mutation_math_p1", "label_mutation_math_p1"),
        ParamSpec([r"effectiveMathP2"], "spinbox_mutation_math_p2", "label_mutation_math_p2"),
        ParamSpec([r"mut\.mathP3"], "spinbox_mutation_math_p3", "label_mutation_math_p3"),
        ParamSpec([r"mut\.mathP4"], "spinbox_mutation_math_p4", None),
        ParamSpec([r"mut\.mathP5"], "spinbox_mutation_math_p5", "label_mutation_math_p5"),
        ParamSpec([r"mut\.mathP6"], "spinbox_mutation_math_p6", "label_mutation_math_p6"),
        ParamSpec([r"mut\.mathP7"], "spinbox_mutation_math_p7", "label_mutation_math_p7"),
        ParamSpec([r"mut\.mathP8"], "spinbox_mutation_math_p8", None),
    ]),
    ("trap", [
        ParamSpec([r"mut\.trapRadius"], "spinbox_mutation_trap_radius", "label_mutation_trap_radius"),
    ]),
]

INLINE_CASE_EXTRACTORS = {
    "fold": extract_fold_cases,
    "warp": extract_warp_cases,
    "math": extract_math_cases,
    "trap": extract_trap_cases,
}


def append_param_rules(
    system_id: str,
    cases: Dict[int, str],
    params: List[ParamSpec],
    arrays: List[str],
    rules: List[str],
) -> None:
    seen_arrays: Dict[str, str] = {}
    for param in params:
        if param.always_active:
            rules.append(fmt_rule(system_id, param.spin, param.label, [], always=True))
            continue
        types = types_for_patterns(cases, param.local_patterns)
        if not types:
            rules.append(fmt_rule(system_id, param.spin, param.label, []))
            continue
        arr_name = unique_array_name(system_id, param.spin or param.label or "x")
        if arr_name not in seen_arrays:
            seen_arrays[arr_name] = fmt_type_array(arr_name, types)
            arrays.append(seen_arrays[arr_name])
        spin_s = f'"{param.spin}"' if param.spin else "nullptr"
        label_s = f'"{param.label}"' if param.label else "nullptr"
        rules.append(f'\t{{ "{system_id}", {spin_s}, {label_s}, {arr_name}, {len(types)} }},')


def unique_array_name(system_id: str, spin: str) -> str:
    base = f"k_{system_id}_{spin}".replace("spinbox_mutation_", "").replace("spinboxInt_mutation_", "")
    base = re.sub(r"[^a-zA-Z0-9_]", "_", base)
    return base


def generate_rules_for_system(
    cpu: str, spec: DeSystemSpec
) -> Tuple[List[str], List[str], List[str]]:
    cases = extract_switch_cases(cpu, spec.switch_pattern, spec.marker)
    arrays: List[str] = []
    rules: List[str] = []
    seen_arrays: Dict[str, str] = {}

    for param in spec.params:
        if param.always_active:
            rules.append(fmt_rule(spec.system_id, param.spin, param.label, [], always=True))
            continue
        types = types_for_patterns(cases, param.local_patterns)
        if not types:
            rules.append(fmt_rule(spec.system_id, param.spin, param.label, []))
            continue
        arr_name = unique_array_name(spec.system_id, param.spin)
        if arr_name not in seen_arrays:
            seen_arrays[arr_name] = fmt_type_array(arr_name, types)
            arrays.append(seen_arrays[arr_name])
        spin_s = f'"{param.spin}"' if param.spin else "nullptr"
        label_s = f'"{param.label}"' if param.label else "nullptr"
        rules.append(
            f'\t{{ "{spec.system_id}", {spin_s}, {label_s}, {arr_name}, {len(types)} }},'
        )
    binding = f'\t{{ "{spec.system_id}", "{spec.group}", "{spec.combo}" }},'
    return arrays, rules, [binding]


def extract_julia_rules() -> str:
    ext = OUT_EXT.read_text(encoding="utf-8")
    m = re.search(r"(static const sMutationJuliaUiRule kJuliaUiRules\[\].*?^};)", ext, re.S | re.M)
    if not m:
        raise RuntimeError("Could not extract Julia rules from extended registry")
    return m.group(1)


def main() -> int:
    cpu = CPU_FILE.read_text(encoding="utf-8")
    all_arrays: List[str] = []
    all_rules: List[str] = []
    all_bindings: List[str] = []

    for spec in ALL_DE:
        arrays, rules, bindings = generate_rules_for_system(cpu, spec)
        all_arrays.extend(arrays)
        all_rules.extend(rules)
        all_bindings.extend(bindings)

    # Inline DE tweak (enum combo indices from nine_fractals.hpp)
    all_arrays.append(fmt_type_array("kDeP1", DE_P1_TYPES))
    all_arrays.append(fmt_type_array("kDeP2", DE_P2_TYPES))
    for _sid, params in INLINE_DE_RULES:
        for param in params:
            if param.always_active:
                all_rules.append(fmt_rule("de", param.spin, param.label, [], always=True))
            elif param.spin == "spinbox_mutation_de_tweak_p1":
                all_rules.append(
                    f'\t{{ "de", "spinbox_mutation_de_tweak_p1", "label_mutation_de_tweak_p1", kDeP1, {len(DE_P1_TYPES)} }},'
                )
            elif param.spin == "spinbox_mutation_de_tweak_p2":
                all_rules.append(
                    f'\t{{ "de", "spinbox_mutation_de_tweak_p2", "label_mutation_de_tweak_p2", kDeP2, {len(DE_P2_TYPES)} }},'
                )
            else:
                all_rules.append(fmt_rule("de", param.spin, param.label, []))

    # Inline dock systems: fold, warp, math, orbit trap
    for system_id, params in INLINE_SYSTEM_SPECS:
        cases = INLINE_CASE_EXTRACTORS[system_id](cpu)
        append_param_rules(system_id, cases, params, all_arrays, all_rules)

    # Clip / inversion (extended file)
    clip_cases = extract_switch_cases(cpu, r"switch\s*\(\s*mut\.clipType\s*\)")
    inv_cases = extract_switch_cases(cpu, r"switch\s*\(\s*mut\.inversionType\s*\)")
    ext_arrays: List[str] = []
    ext_rules: List[str] = []

    def add_ext_rules(system_id: str, cases: Dict[int, str], params: List[ParamSpec]) -> None:
        for param in params:
            if param.always_active:
                ext_rules.append(fmt_rule(system_id, param.spin, param.label, [], always=True))
                continue
            types = types_for_patterns(cases, param.local_patterns)
            if not types:
                ext_rules.append(fmt_rule(system_id, param.spin, param.label, []))
                continue
            arr = unique_array_name(system_id, param.spin)
            ext_arrays.append(fmt_type_array(arr, types))
            spin_s = f'"{param.spin}"'
            label_s = f'"{param.label}"' if param.label else "nullptr"
            ext_rules.append(f'\t{{ "{system_id}", {spin_s}, {label_s}, {arr}, {len(types)} }},')

    add_ext_rules("clip", clip_cases, CLIP_PARAMS)
    add_ext_rules("inv", inv_cases, INV_PARAMS)

    julia_block = extract_julia_rules()

    main_cpp = f"""// Auto-generated by mutations/codegen/generate_mutation_ui_registry.py — do not edit manually
#include "mutation_ui_registry.hpp"

namespace {{

{chr(10).join(all_arrays)}

static const sMutationParamRule kMutationParamRules[] = {{
{chr(10).join(all_rules)}
}};

static const sMutationSystemBinding kMutationSystemBindings[] = {{
{chr(10).join(all_bindings)}
}};
}} // namespace

const sMutationParamRule *cMutationUiRegistry::ParamRulesData() {{ return kMutationParamRules; }}
int cMutationUiRegistry::ParamRulesCount() {{ return int(sizeof(kMutationParamRules)/sizeof(kMutationParamRules[0])); }}
const sMutationSystemBinding *cMutationUiRegistry::SystemBindingsData() {{ return kMutationSystemBindings; }}
int cMutationUiRegistry::SystemBindingsCount() {{ return int(sizeof(kMutationSystemBindings)/sizeof(kMutationSystemBindings[0])); }}
"""

    ext_cpp = f"""// Auto-generated by mutations/codegen/generate_mutation_ui_registry.py — do not edit manually
// Extended mutation UI registry data (clip, inversion, julia)
#include "mutation_ui_registry.hpp"

namespace {{
{chr(10).join(ext_arrays)}

static const sMutationParamRule kExtendedParamRules[] = {{
{chr(10).join(ext_rules)}
}};
{julia_block}
static const sMutationSystemBinding kExtendedSystemBindings[] = {{
\t{{ "clip", "groupCheck_mutation_clip_enabled", "comboBox_mutation_clip_type" }},
\t{{ "inv", "groupCheck_mutation_inversion_enabled", "comboBox_mutation_inv_type" }},
}};
}} // namespace

const sMutationParamRule *cMutationUiRegistry::ExtendedParamRulesData() {{ return kExtendedParamRules; }}
int cMutationUiRegistry::ExtendedParamRulesCount() {{ return int(sizeof(kExtendedParamRules)/sizeof(kExtendedParamRules[0])); }}
const sMutationJuliaUiRule *cMutationUiRegistry::JuliaRulesData() {{ return kJuliaUiRules; }}
int cMutationUiRegistry::JuliaRulesCount() {{ return int(sizeof(kJuliaUiRules)/sizeof(kJuliaUiRules[0])); }}
const sMutationSystemBinding *cMutationUiRegistry::ExtendedSystemBindingsData() {{ return kExtendedSystemBindings; }}
int cMutationUiRegistry::ExtendedSystemBindingsCount() {{ return int(sizeof(kExtendedSystemBindings)/sizeof(kExtendedSystemBindings[0])); }}
"""

    OUT_MAIN.write_text(main_cpp, encoding="utf-8")
    OUT_EXT.write_text(ext_cpp, encoding="utf-8")
    print(f"Wrote {OUT_MAIN} ({len(all_rules)} rules, {len(all_bindings)} bindings)")
    print(f"Wrote {OUT_EXT} ({len(ext_rules)} extended rules)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
