#!/usr/bin/env bash
# Golden-style regression: render Single Trap Lights scene on CPU and OpenCL, compare PNGs.
# Usage: from repo root, build ./mandelbulber2 then:
#   qmake/test_single_trap_lights_golden.sh
# Env:
#   MANDELBULBER_GOLDEN_SKIP_GPU=1 - only check that CPU render succeeds (no GPU / no OpenCL).
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
MB="$REPO_ROOT/mandelbulber2"
GOLDEN="$SCRIPT_DIR/golden_single_trap_lights"
COMPARE="$GOLDEN/compare_png.py"
export GOLDEN_COMPARE="$COMPARE"
WORKDIR=$(mktemp -d "${TMPDIR:-/tmp}/mb_stl_golden.XXXXXX")
cleanup() { rm -rf "$WORKDIR"; }
trap cleanup EXIT

if [[ ! -x "$MB" ]]; then
	echo "ERROR: mandelbulber binary not found or not executable: $MB"
	echo "Build from $REPO_ROOT first (make)."
	exit 2
fi

if [[ ! -f "$GOLDEN/scene.fract" ]]; then
	echo "ERROR: missing $GOLDEN/scene.fract"
	exit 2
fi

run_cpu() {
	local scene="$1"
	local out="$2"
	local extra="${3:-}"
	# Low iteration count; deterministic helpers; CPU path.
	"$MB" "$scene" -o "$out" --nogui -f png \
		--override "opencl_enabled=false#opencl_mode=0#${extra}"
}

run_gpu() {
	local scene="$1"
	local out="$2"
	local extra="${3:-}"
	"$MB" "$scene" -o "$out" --nogui -f png -g \
		--override "opencl_precision=1#${extra}"
}

compare_pair() {
	local cpu_png="$1"
	local gpu_png="$2"
	local limit="$3"
	python3 "$COMPARE" "$cpu_png" "$gpu_png" --rmse-max "$limit"
}

# Reject flat / black output (broken scene or render).
check_cpu_png_nonflat() {
	local png="$1"
	python3 -c "import importlib.util, os, sys
spec = importlib.util.spec_from_file_location('pngcmp', os.environ['GOLDEN_COMPARE'])
m = importlib.util.module_from_spec(spec); spec.loader.exec_module(m)
_, _, b = m.read_png_rgb(sys.argv[1])
mx = max(b)
if mx <= 8:
	sys.stderr.write('ERROR: PNG almost black (max channel %d): %s\n' % (mx, sys.argv[1]))
	sys.exit(4)
" "$png"
}

echo "=== Single Trap Lights golden (CPU vs OpenCL) ==="
echo "Work dir: $WORKDIR"

BASE_OVERRIDES="hdr=false#antialiasing_enabled=false"

SKIP_GPU="${MANDELBULBER_GOLDEN_SKIP_GPU:-0}"

# --- Surface-heavy scene (two layers, add combine, all layers) ---
echo ""
echo "Case: surface (add, all layers)"
run_cpu "$GOLDEN/scene.fract" "$WORKDIR/surf_cpu.png" "$BASE_OVERRIDES"
if [[ "$SKIP_GPU" == 1 ]]; then
	echo "SKIP GPU (MANDELBULBER_GOLDEN_SKIP_GPU=1) — CPU render: $WORKDIR/surf_cpu.png"
else
	GPU_LOG="$WORKDIR/gpu_surf.log"
	if ! run_gpu "$GOLDEN/scene.fract" "$WORKDIR/surf_gpu.png" "$BASE_OVERRIDES" >"$GPU_LOG" 2>&1; then
		if grep -q "Not compiled for opencl" "$GPU_LOG" || grep -qi "no opencl" "$GPU_LOG"; then
			echo "OpenCL not in this build — continuing with CPU-only smoke (compare on a GPU-enabled build)."
			SKIP_GPU=1
		else
			cat "$GPU_LOG" >&2
			echo "ERROR: OpenCL render failed. Fix GPU/OpenCL or set MANDELBULBER_GOLDEN_SKIP_GPU=1."
			exit 3
		fi
	fi
	if [[ "$SKIP_GPU" != 1 ]]; then
		compare_pair "$WORKDIR/surf_cpu.png" "$WORKDIR/surf_gpu.png" 0.028
	fi
fi

echo ""
echo "Case: surface solo layer 1"
run_cpu "$GOLDEN/scene.fract" "$WORKDIR/solo_cpu.png" \
	"${BASE_OVERRIDES}#single_trap_lights_solo_layer=1"
if [[ "$SKIP_GPU" != 1 ]]; then
	run_gpu "$GOLDEN/scene.fract" "$WORKDIR/solo_gpu.png" \
		"${BASE_OVERRIDES}#single_trap_lights_solo_layer=1"
	compare_pair "$WORKDIR/solo_cpu.png" "$WORKDIR/solo_gpu.png" 0.028
fi

echo ""
echo "Case: surface combine max per channel"
run_cpu "$GOLDEN/scene.fract" "$WORKDIR/max_cpu.png" \
	"${BASE_OVERRIDES}#single_trap_lights_combine_mode=1"
if [[ "$SKIP_GPU" != 1 ]]; then
	run_gpu "$GOLDEN/scene.fract" "$WORKDIR/max_gpu.png" \
		"${BASE_OVERRIDES}#single_trap_lights_combine_mode=1"
	compare_pair "$WORKDIR/max_cpu.png" "$WORKDIR/max_gpu.png" 0.03
fi

echo ""
echo "Case: volumetric fog + STL (looser RMSE)"
run_cpu "$GOLDEN/scene_volumetric.fract" "$WORKDIR/vol_cpu.png" "$BASE_OVERRIDES"
if [[ "$SKIP_GPU" != 1 ]]; then
	run_gpu "$GOLDEN/scene_volumetric.fract" "$WORKDIR/vol_gpu.png" "$BASE_OVERRIDES"
	compare_pair "$WORKDIR/vol_cpu.png" "$WORKDIR/vol_gpu.png" 0.055
fi

echo ""
for _f in surf_cpu solo_cpu max_cpu vol_cpu; do
	check_cpu_png_nonflat "$WORKDIR/${_f}.png"
done
if [[ "$SKIP_GPU" == 1 ]]; then
	echo "CPU smoke finished (OpenCL comparisons skipped)."
else
	echo "All golden checks passed (CPU vs OpenCL)."
fi
