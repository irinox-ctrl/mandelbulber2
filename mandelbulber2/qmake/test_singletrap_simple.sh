#!/bin/bash
# Simple CPU vs GPU test for Single Trap Light

cd "$(dirname "$0")"

echo "=== Single Trap Light CPU vs GPU Test ==="
echo ""

# Use simple mandelbulb with Single Trap Light enabled
OVERRIDES="--override single_trap_light_0_enabled=true \
--override single_trap_light_0_center_x=0.0 \
--override single_trap_light_0_center_y=0.0 \
--override single_trap_light_0_center_z=2.0 \
--override single_trap_light_0_size=1.0 \
--override single_trap_light_0_radius=0.5 \
--override single_trap_light_0_intensity=5.0 \
--override single_trap_light_0_color_R=1.0 \
--override single_trap_light_0_color_G=0.5 \
--override single_trap_light_0_color_B=0.0"

echo "Step 1: CPU render (20 iterations, 400x300)"
./mandelbulber2 -o /tmp/test_trap_cpu.png -r 400x300 -n 20 \
  --override opencl_enabled=false $OVERRIDES --nogui 2>&1 | tail -5

echo ""
echo "Step 2: GPU render (20 iterations, 400x300)"
./mandelbulber2 -o /tmp/test_trap_gpu.png -r 400x300 -n 20 \
  -g $OVERRIDES --nogui 2>&1 | tail -5

echo ""
echo "✓ Test complete!"
echo "  CPU output: /tmp/test_trap_cpu.png"
echo "  GPU output: /tmp/test_trap_gpu.png"
echo ""
echo "Both images should show orange glow from Single Trap Light"
