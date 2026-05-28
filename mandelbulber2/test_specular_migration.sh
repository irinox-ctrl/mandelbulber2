#!/bin/bash
set -e

REPO="/home/joeri/mandelbulber2_v2_experiment/mandelbulber2"
BACKUP="$REPO/backup_before_specular_fix"
TEST_FRACT="$REPO/test_specular.fract"
BUILD_CMD="make -j$(nproc)"

echo "=========================================="
echo "Specular Gradient Fix - A/B Test Script"
echo "=========================================="
echo ""

# Create test scene if it doesn't exist
cat > "$TEST_FRACT" << 'EOF'
# Mandelbulber settings file
# version 2.26
# Test scene: blue specular base + red gradient at 50% opacity
# OLD behavior: specular highlights would be white-ish (base=1.0 multiplier)
# NEW behavior: specular highlights should be purple (blue*0.5 + red*0.5)
[main_parameters]
ambient_occlusion_enabled true;
camera -2,13099957597042 -2,65981125399026 0,789064324930775;
camera_distance_to_target 3,21828805928671;
camera_rotation -31,5166776136377 -14,1925532903359 0;
camera_top 0,1281677670855954 0,2090141986028645 0,969477224210775;
detail_level 2;
fov 53,130102354156;
light1_is_defined true;
mat1_is_defined true;
mat1_specular 40;
mat1_specular_width 0,063;
mat1_specular_color 0 0 1;
mat1_specular_gradient_enable true;
mat1_specular_gradient 0 ff0000 9999 ff0000 |: 0:0.5 9999:0.5;
mat1_surface_color_gradient 0 fd6029 999 698403 1999 fff59b 2999 f5bd22 3999 0b5e87 5000 c68876 5999 a51c64 7000 3b9fee 7999 d4ffd4 9000 aba53c;
opencl_enabled false;
raytraced_reflections true;
target -0,5 0 0;
[fractal_1]
alpha_angle_offset 90;
beta_angle_offset 90;
power 2;
EOF

echo "Test scene created: $TEST_FRACT"
echo "  - Base specular color: BLUE (0,0,1)"
echo "  - Gradient color: RED (ff0000)"
echo "  - Gradient opacity: 50%"
echo ""

# Helper: copy files from source dir to repo src/
copy_files() {
    local src_dir="$1"
    for f in render_worker.hpp shader_specular_highlight.cpp shader_specular_highlight_combined.cpp shader_surface_color.cpp shader_light_shading.cpp shader_object.cpp; do
        cp "$src_dir/$f" "$REPO/src/$f"
    done
}

# Helper: build and render
build_and_render() {
    local label="$1"
    local output="$2"
    
    echo "--- Building $label version ---"
    cd "$REPO"
    $BUILD_CMD > /tmp/build_${label}.log 2>&1
    if [ $? -ne 0 ]; then
        echo "BUILD FAILED for $label!"
        tail -20 /tmp/build_${label}.log
        exit 1
    fi
    echo "Build OK"
    
    echo "--- Rendering with $label version ---"
    mkdir -p "$(dirname "$output")"
    "$REPO/mandelbulber2" --nogui --output "$output" "$TEST_FRACT" --res 400x300 > /tmp/render_${label}.log 2>&1
    if [ $? -ne 0 ]; then
        echo "RENDER FAILED for $label!"
        tail -20 /tmp/render_${label}.log
        exit 1
    fi
    echo "Render saved: $output"
    echo ""
}

# Step 1: Save current (fixed) files
echo "Saving current fixed files to /tmp/fixed_files/..."
mkdir -p /tmp/fixed_files
for f in render_worker.hpp shader_specular_highlight.cpp shader_specular_highlight_combined.cpp shader_surface_color.cpp shader_light_shading.cpp shader_object.cpp; do
    cp "$REPO/src/$f" /tmp/fixed_files/
done

# Step 2: Build OLD (backup) version
echo ""
echo ">>> TEST A: OLD CODE (backup before fix) <<<"
echo ""
copy_files "$BACKUP"
build_and_render "OLD" "/tmp/test_specular_OLD.jpg"

# Step 3: Build NEW (fixed) version
echo ">>> TEST B: NEW CODE (migrated fix) <<<"
echo ""
copy_files /tmp/fixed_files
build_and_render "NEW" "/tmp/test_specular_NEW.jpg"

# Step 4: Compare
echo "=========================================="
echo "COMPARING OUTPUTS"
echo "=========================================="
echo ""

python3 << 'PYEOF'
from PIL import Image
import numpy as np

img_old = Image.open('/tmp/test_specular_OLD.jpg')
img_new = Image.open('/tmp/test_specular_NEW.jpg')

arr_old = np.array(img_old)
arr_new = np.array(img_new)

# Compare overall stats
print(f"OLD image - Mean RGB: {arr_old.mean(axis=(0,1)).astype(int)}")
print(f"NEW image - Mean RGB: {arr_new.mean(axis=(0,1)).astype(int)}")
print("")

# Find brightest pixels (likely specular highlights)
# Brightness = max(R,G,B)
bright_old = np.max(arr_old, axis=2)
bright_new = np.max(arr_new, axis=2)

# Get top 1% brightest pixels
threshold_old = np.percentile(bright_old, 99)
threshold_new = np.percentile(bright_new, 99)

mask_old = bright_old >= threshold_old
mask_new = bright_new >= threshold_new

spec_old = arr_old[mask_old]
spec_new = arr_new[mask_new]

print(f"Top 1% brightest pixels (specular highlights):")
print(f"  OLD - Average color: {spec_old.mean(axis=0).astype(int)} (should be near-white ~255,255,255)")
print(f"  NEW - Average color: {spec_new.mean(axis=0).astype(int)} (should be purple-ish ~128,0,128)")
print("")

# Max diff
 diff = np.abs(arr_old.astype(float) - arr_new.astype(float))
max_diff = np.max(diff)
mean_diff = np.mean(diff)

print(f"Pixel difference between OLD and NEW:")
print(f"  Max difference: {max_diff:.0f}")
print(f"  Mean difference: {mean_diff:.2f}")
print("")

if max_diff < 10:
    print("❌ IMAGES ARE NEARLY IDENTICAL - FIX IS NOT ACTIVE!")
elif spec_new.mean(axis=0)[0] > spec_new.mean(axis=0)[2]:
    print("❌ NEW specular is MORE RED than BLUE - unexpected!")
elif spec_old.mean(axis=0)[0] > 200 and spec_old.mean(axis=0)[2] > 200:
    print("✅ OLD specular is white-ish (base=1.0 multiplier behavior)")
    if spec_new.mean(axis=0)[2] > 50 and spec_new.mean(axis=0)[0] > 50:
        print("✅ NEW specular is purple-ish (blue+red blend behavior)")
        print("")
        print("=== TEST PASSED ===")
        print("The specular gradient fix is working correctly!")
        print("Opacity 0.5 now blends between material color (blue)")
        print("and gradient color (red), giving purple highlights.")
    else:
        print("⚠️ NEW specular color doesn't show expected purple blend")
else:
    print("⚠️ Unexpected colors - manual inspection needed")

print("")
print("Images saved to:")
print("  /tmp/test_specular_OLD.jpg")
print("  /tmp/test_specular_NEW.jpg")
PYEOF

echo ""
echo "=========================================="
echo "TEST COMPLETE"
echo "=========================================="
