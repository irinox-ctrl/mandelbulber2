#!/bin/bash
# Dark Shapes Individual Testing Script
# Tests the 15 dark shapes with varied parameters to find optimal settings

set -e

MANDELBULBER="/home/joeri/mandelbulber2_v2_experiment/mandelbulber2/qmake/mandelbulber2"
TEST_DIR="/home/joeri/mandelbulber2_v2_experiment/test_fake_lights_v2"
OUTPUT_DIR="$TEST_DIR/dark_shapes_output"
mkdir -p "$OUTPUT_DIR"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Dark shapes list with indices
DARK_SHAPES=(
    "47:Lattice"
    "53:Voronoi"
    "54:Mandelbrot2D"
    "55:Julia2D"
    "58:Dragon"
    "60:Gyroid"
    "61:SchwarzP"
    "62:SchwarzD"
    "63:Neovius"
    "86:Julia3D"
    "92:Newton"
    "94:Spider"
    "99:Apollonian"
    "102:Celtic"
    "104:Cactus"
)

make_test_fract() {
    local shape_idx=$1
    local intensity=$2
    local size=$3
    local visibility=$4

    cat << EOF
# Mandelbulber settings file
# version 2.35
[main_parameters]
ambient_occlusion_enabled false;
camera -2 -2 0;
camera_distance_to_target 2.828427;
camera_rotation -45 -45 0;
camera_top 0.5 0.5 0.707106781;
constant_DE_threshold true;
DE_thresh 0.01;
detail_level 0.3;
formula_1 2;
fov 1;
glow_intensity 0;
image_height 300;
image_width 400;
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
fake_lights_orbit_trap_shape ${shape_idx};
fake_lights_color ffff ffff ffff;
fake_lights_intensity ${intensity};
fake_lights_orbit_trap 0.0 0.0 0.0;
fake_lights_orbit_trap_size ${size};
fake_lights_visibility ${visibility};
fake_lights_visibility_size ${visibility};
fake_lights_thickness 1.0;
fake_lights_max_iter 250;
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

render_test() {
    local fract_file=$1
    local output_file=$2
    $MANDELBULBER -n "$fract_file" -o "$output_file" > /dev/null 2>&1
}

get_brightness() {
    local file=$1
    if [ ! -f "$file" ]; then
        echo "0"
        return
    fi
    python3 -c "
from PIL import Image
import numpy as np
a = np.array(Image.open('$file'))
print(f'{np.mean(a):.2f}')
"
}

test_shape_variants() {
    local shape_info=$1
    local idx=$(echo $shape_info | cut -d: -f1)
    local name=$(echo $shape_info | cut -d: -f2)

    echo -e "\n${BLUE}========================================${NC}"
    echo -e "${YELLOW}Testing Shape ${idx}: ${name}${NC}"
    echo -e "${BLUE}========================================${NC}"

    # Test matrix: intensity x size x visibility
    local intensities=(0.01 0.1 1.0 10.0)
    local sizes=(0.1 0.5 1.0 2.0 5.0)
    local visibilities=(5.0 10.0 20.0)

    local best_brightness=0
    local best_params=""
    local test_count=0

    # Smart testing: start with varied combinations
    for intensity in "${intensities[@]}"; do
        for size in "${sizes[@]}"; do
            for visibility in "${visibilities[@]}"; do
                test_count=$((test_count + 1))

                local fract_file="$OUTPUT_DIR/${name}_${test_count}.fract"
                local output_file="$OUTPUT_DIR/${name}_${test_count}.jpg"

                make_test_fract $idx $intensity $size $visibility > "$fract_file"
                render_test "$fract_file" "$output_file"

                local brightness=$(get_brightness "$output_file")

                # Only print if significant brightness found
                if python3 -c "exit(0 if $brightness > 1.0 else 1)"; then
                    echo -e "  ${GREEN}✓${NC} intensity=${intensity}, size=${size}, vis=${visibility} -> ${GREEN}${brightness}${NC}"

                    if python3 -c "exit(0 if $brightness > $best_brightness else 1)"; then
                        best_brightness=$brightness
                        best_params="intensity=${intensity}, size=${size}, visibility=${visibility}"
                    fi
                fi

                # Cleanup dark outputs to save space
                if python3 -c "exit(0 if $brightness < 1.0 else 1)"; then
                    rm -f "$output_file" "$fract_file"
                fi
            done
        done
    done

    echo ""
    if python3 -c "exit(0 if $best_brightness > 1.0 else 1)"; then
        echo -e "${GREEN}✓ FOUND WORKING PARAMETERS!${NC}"
        echo -e "  Shape: ${name}"
        echo -e "  Brightness: ${best_brightness}"
        echo -e "  Params: ${best_params}"
    else
        echo -e "${RED}✗ NO WORKING PARAMETERS FOUND${NC}"
        echo -e "  Shape: ${name} may require different approach"
    fi
}

# Main execution
echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║   DARK SHAPES PARAMETER DISCOVERY     ║${NC}"
echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
echo ""
echo "Testing 15 dark shapes with parameter variations..."
echo "This will test each shape with 60 parameter combinations"
echo "Total tests: 15 shapes × 60 variants = 900 renders"
echo "Estimated time: 30-45 minutes"
echo ""
read -p "Press ENTER to start, or Ctrl+C to cancel..."

# Test specific shape if argument given
if [ -n "$1" ]; then
    found=false
    for shape in "${DARK_SHAPES[@]}"; do
        name=$(echo $shape | cut -d: -f2)
        if [ "$name" = "$1" ]; then
            test_shape_variants "$shape"
            found=true
            break
        fi
    done
    if [ "$found" = false ]; then
        echo -e "${RED}Error: Shape '$1' not found in dark shapes list${NC}"
        exit 1
    fi
else
    # Test all dark shapes
    for shape in "${DARK_SHAPES[@]}"; do
        test_shape_variants "$shape"
    done

    echo ""
    echo -e "${GREEN}════════════════════════════════════════${NC}"
    echo -e "${GREEN}DARK SHAPES TESTING COMPLETE${NC}"
    echo -e "${GREEN}════════════════════════════════════════${NC}"
    echo ""
    echo "Results saved to: $OUTPUT_DIR"
    echo "Review successful renders to find optimal parameters"
fi
