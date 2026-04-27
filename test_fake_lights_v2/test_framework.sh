#!/bin/bash
# Fake Lights Test Framework (updated for current Mandelbulber2 code)
# Tests CPU and OpenCL fake lights with various orbit trap shapes and modifiers.
# Usage: ./test_framework.sh [test_name]

set -e

MANDELBULBER="/home/joeri/mandelbulber2_v2_experiment/mandelbulber2/qmake/mandelbulber2"
TEST_DIR="/home/joeri/mandelbulber2_v2_experiment/test_fake_lights_v2"
OUTPUT_DIR="$TEST_DIR/output"
mkdir -p "$OUTPUT_DIR"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

cleanup_cache() {
    rm -rf ~/.mandelbulber/openclCache/*
}

render() {
    local input="$1"
    local output="$2"
    local use_opencl="${3:-false}"
    local tmpfile="$(mktemp)"
    cp "$input" "$tmpfile"
    if [ "$use_opencl" = "true" ]; then
        sed -i 's/opencl_enabled false;/opencl_enabled true;/' "$tmpfile"
    fi
    $MANDELBULBER -n "$tmpfile" -o "$output" > /dev/null 2>&1
    rm -f "$tmpfile"
}

compare_images() {
    local a="$1"
    local b="$2"
    if [ ! -f "$a" ] || [ ! -f "$b" ]; then
        echo "MISSING"
        return
    fi
    python3 -c "
from PIL import Image
import numpy as np, sys
a = np.array(Image.open('$a'))
b = np.array(Image.open('$b'))
if a.shape != b.shape:
    sys.exit(1)
diff = np.abs(a.astype(float) - b.astype(float))
maxdiff = np.max(diff)
avgdiff = np.mean(diff)
print(f'{maxdiff:.1f} {avgdiff:.2f}')
"
}

image_avg() {
    local f="$1"
    if [ ! -f "$f" ]; then
        echo "0"
        return
    fi
    python3 -c "
from PIL import Image
import numpy as np
a = np.array(Image.open('$f'))
print(np.mean(a))
"
}

make_base_fract() {
    cat << 'EOF'
# Mandelbulber settings file
# version 2.35
# all parameters
[main_parameters]
ambient_occlusion_enabled false;
camera -2 -2 0;
camera_distance_to_target 2.828427;
camera_rotation -45 -45 0;
camera_top 0.5 0.5 0.707106781;
constant_DE_threshold true;
DE_thresh 0.01;
detail_level 0.3;
file_background ;
file_lightmap ;
formula_1 2;
fov 1;
glow_intensity 0;
image_height 150;
image_width 200;
legacy_coordinate_system false;
light1_enabled false;
mat1_is_defined true;
mat1_surface_color ffff ffff ffff;
N 100;
opencl_enabled false;
perspective_type 0;
smoothness 1;
target 0 0 0;
view_distance_max 50;
fake_lights_enabled true;
fake_lights_orbit_trap_shape 1;
fake_lights_color ffff 0000 0000;
fake_lights_color_2 0000 ffff 0000;
fake_lights_color_3 0000 0000 ffff;
fake_lights_color_2_enabled false;
fake_lights_color_3_enabled false;
fake_lights_intensity 0.01;
fake_lights_orbit_trap 2.0 0.0 0.0;
fake_lights_orbit_trap_size 0.5;
fake_lights_visibility 10.0;
fake_lights_visibility_size 10.0;
fake_lights_thickness 1.0;
fake_lights_shape_mask_radius 0.0;
fake_lights_shape_mask_softness 0.1;
fake_lights_shape_falloff 1.0;
fake_lights_max_iter 100;
[fractal_1]
mandelbox_scale -1.5;
mandelbox_folding_limit 1;
mandelbox_folding_value 2;
mandelbox_color 0000 0000 0000;
mandelbox_rotation_main 0 0 0;
mandelbox_solid 0;
mandelbox_melt 0;
EOF
}

test_basic_on_off() {
    echo -e "\n${YELLOW}Test: Basic fake lights on/off${NC}"
    make_base_fract > "$TEST_DIR/_base.fract"

    sed 's/fake_lights_enabled true;/fake_lights_enabled false;/' "$TEST_DIR/_base.fract" > "$TEST_DIR/_off.fract"
    render "$TEST_DIR/_off.fract" "$OUTPUT_DIR/basic_off.jpg"

    render "$TEST_DIR/_base.fract" "$OUTPUT_DIR/basic_on.jpg"

    local avg_off=$(image_avg "$OUTPUT_DIR/basic_off.jpg")
    local avg_on=$(image_avg "$OUTPUT_DIR/basic_on.jpg")
    echo "  avg OFF=$avg_off  ON=$avg_on"

    if python3 -c "exit(0 if $avg_on > $avg_off + 5 else 1)"; then
        echo -e "${GREEN}  PASS: fake lights produce visible output${NC}"
    else
        echo -e "${RED}  FAIL: no visible difference${NC}"
        return 1
    fi
}

test_shape_variants() {
    echo -e "\n${YELLOW}Test: Shape variants${NC}"
    make_base_fract > "$TEST_DIR/_base.fract"
    local shapes=(0 1 8 21 41)
    local names=(Point Line Torus TorusKnot Helix)
    local prev_avg=""
    local all_same=true
    for i in "${!shapes[@]}"; do
        local shape=${shapes[$i]}
        local name=${names[$i]}
        sed "s/fake_lights_orbit_trap_shape 1;/fake_lights_orbit_trap_shape ${shape};/" "$TEST_DIR/_base.fract" > "$TEST_DIR/_shape.fract"
        render "$TEST_DIR/_shape.fract" "$OUTPUT_DIR/shape_${name}.jpg"
        local avg=$(image_avg "$OUTPUT_DIR/shape_${name}.jpg")
        echo "  Shape $name (idx=$shape): avg=$avg"
        if [ -n "$prev_avg" ]; then
            if python3 -c "exit(0 if abs($avg - $prev_avg) > 1 else 1)"; then
                all_same=false
            fi
        fi
        prev_avg=$avg
    done
    if [ "$all_same" = "false" ]; then
        echo -e "${GREEN}  PASS: different shapes produce different output${NC}"
    else
        echo -e "${RED}  FAIL: all shapes look identical${NC}"
        return 1
    fi
}

test_mask_falloff() {
    echo -e "\n${YELLOW}Test: Mask + Falloff modifiers${NC}"
    make_base_fract > "$TEST_DIR/_base.fract"

    # baseline
    render "$TEST_DIR/_base.fract" "$OUTPUT_DIR/mod_baseline.jpg"
    local avg_base=$(image_avg "$OUTPUT_DIR/mod_baseline.jpg")

    # mask on
    sed 's/fake_lights_shape_mask_radius 0.0;/fake_lights_shape_mask_radius 1.0;/' "$TEST_DIR/_base.fract" > "$TEST_DIR/_mask.fract"
    render "$TEST_DIR/_mask.fract" "$OUTPUT_DIR/mod_mask.jpg"
    local avg_mask=$(image_avg "$OUTPUT_DIR/mod_mask.jpg")

    # falloff 2.0
    sed 's/fake_lights_shape_falloff 1.0;/fake_lights_shape_falloff 2.0;/' "$TEST_DIR/_base.fract" > "$TEST_DIR/_falloff.fract"
    render "$TEST_DIR/_falloff.fract" "$OUTPUT_DIR/mod_falloff.jpg"
    local avg_falloff=$(image_avg "$OUTPUT_DIR/mod_falloff.jpg")

    echo "  baseline=$avg_base  mask=$avg_mask  falloff=$avg_falloff"

    local pass=true
    if python3 -c "exit(0 if $avg_mask < $avg_base - 1 else 1)"; then
        echo -e "${GREEN}  PASS: mask reduces output${NC}"
    else
        echo -e "${RED}  FAIL: mask has no effect${NC}"
        pass=false
    fi

    if python3 -c "exit(0 if abs($avg_falloff - $avg_base) > 1 else 1)"; then
        echo -e "${GREEN}  PASS: falloff changes output${NC}"
    else
        echo -e "${RED}  FAIL: falloff has no effect${NC}"
        pass=false
    fi

    if [ "$pass" = "false" ]; then
        return 1
    fi
}

test_line_length() {
    echo -e "\n${YELLOW}Test: Line length / thickness${NC}"
    make_base_fract > "$TEST_DIR/_base.fract"
    sed -i 's/fake_lights_orbit_trap_shape 1;/fake_lights_orbit_trap_shape 1;\nfake_lights_shape_line_length 0.0;/' "$TEST_DIR/_base.fract"

    render "$TEST_DIR/_base.fract" "$OUTPUT_DIR/line_base.jpg"
    local avg_base=$(image_avg "$OUTPUT_DIR/line_base.jpg")

    sed 's/fake_lights_shape_line_length 0.0;/fake_lights_shape_line_length 5.0;/' "$TEST_DIR/_base.fract" > "$TEST_DIR/_line_long.fract"
    render "$TEST_DIR/_line_long.fract" "$OUTPUT_DIR/line_long.jpg"
    local avg_long=$(image_avg "$OUTPUT_DIR/line_long.jpg")

    echo "  base=$avg_base  long=$avg_long"
    if python3 -c "exit(0 if abs($avg_long - $avg_base) > 1 else 1)"; then
        echo -e "${GREEN}  PASS: line length changes output${NC}"
    else
        echo -e "${RED}  FAIL: line length has no effect${NC}"
        return 1
    fi
}

test_tube_radius() {
    echo -e "\n${YELLOW}Test: Tube radius (Torus)${NC}"
    make_base_fract > "$TEST_DIR/_base.fract"
    # Fix: Use much larger orbit_trap_size (5.0) and wide tube_radius range
    sed -i 's/fake_lights_orbit_trap_shape 1;/fake_lights_orbit_trap_shape 8;/' "$TEST_DIR/_base.fract"
    sed -i 's/fake_lights_orbit_trap_size 0.5;/fake_lights_orbit_trap_size 5.0;\nfake_lights_shape_tube_radius 0.1;/' "$TEST_DIR/_base.fract"

    render "$TEST_DIR/_base.fract" "$OUTPUT_DIR/torus_base.jpg"
    local avg_base=$(image_avg "$OUTPUT_DIR/torus_base.jpg")

    sed 's/fake_lights_shape_tube_radius 0.1;/fake_lights_shape_tube_radius 1.5;/' "$TEST_DIR/_base.fract" > "$TEST_DIR/_torus_tr.fract"
    render "$TEST_DIR/_torus_tr.fract" "$OUTPUT_DIR/torus_tr.jpg"
    local avg_tr=$(image_avg "$OUTPUT_DIR/torus_tr.jpg")

    echo "  base=$avg_base (tube_radius=0.1)  large=$avg_tr (tube_radius=1.5)"
    if python3 -c "exit(0 if abs($avg_tr - $avg_base) > 1 else 1)"; then
        echo -e "${GREEN}  PASS: tube radius changes output${NC}"
    else
        echo -e "${RED}  FAIL: tube radius has no effect${NC}"
        return 1
    fi
}

test_opencl() {
    echo -e "\n${YELLOW}Test: OpenCL compilation${NC}"
    cleanup_cache
    make_base_fract > "$TEST_DIR/_base.fract"
    render "$TEST_DIR/_base.fract" "$OUTPUT_DIR/opencl_test.jpg" true
    local avg=$(image_avg "$OUTPUT_DIR/opencl_test.jpg")
    echo "  OpenCL avg=$avg"
    if python3 -c "exit(0 if $avg > 1 else 1)"; then
        echo -e "${GREEN}  PASS: OpenCL renders correctly${NC}"
    else
        echo -e "${RED}  FAIL: OpenCL render is black${NC}"
        return 1
    fi
}

case "${1:-all}" in
    basic)      test_basic_on_off ;;
    shapes)     test_shape_variants ;;
    mask)       test_mask_falloff ;;
    line)       test_line_length ;;
    tube)       test_tube_radius ;;
    opencl)     test_opencl ;;
    all)
        test_basic_on_off
        test_shape_variants
        test_mask_falloff
        test_line_length
        test_tube_radius
        test_opencl
        echo -e "\n${GREEN}========================================${NC}"
        echo -e "${GREEN}All tests passed!${NC}"
        echo -e "${GREEN}Output in: $OUTPUT_DIR${NC}"
        echo -e "${GREEN}========================================${NC}"
        ;;
    *)
        echo "Usage: $0 [basic|shapes|mask|line|tube|opencl|all]"
        exit 1
        ;;
esac
