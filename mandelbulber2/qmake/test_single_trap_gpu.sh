#!/bin/bash
# Test script for Single Trap Light GPU implementation
# Renders test scene with CPU and GPU, creates comparison screenshot

cd "$(dirname "$0")"

FRACT_FILE="../deploy/share/mandelbulber2/examples/hybrid 01.fract"
OUTPUT_DIR="/tmp"
CPU_OUTPUT="${OUTPUT_DIR}/test_single_trap_cpu.png"
GPU_OUTPUT="${OUTPUT_DIR}/test_single_trap_gpu.png"
COMP_OUTPUT="${OUTPUT_DIR}/test_single_trap_comparison.png"

echo "=== Single Trap Light GPU Test ==="
echo ""
echo "Step 1: CPU render (OpenCL disabled)"
./mandelbulber2 "$FRACT_FILE" -o "$CPU_OUTPUT" -r 400x300 -n 20 --override opencl_enabled=false --nogui
if [ $? -ne 0 ]; then
    echo "ERROR: CPU render failed"
    exit 1
fi
echo "✓ CPU render complete: $CPU_OUTPUT"
echo ""

echo "Step 2: GPU render (OpenCL enabled)"
./mandelbulber2 "$FRACT_FILE" -o "$GPU_OUTPUT" -r 400x300 -n 20 -g --nogui
if [ $? -ne 0 ]; then
    echo "ERROR: GPU render failed"
    exit 1
fi
echo "✓ GPU render complete: $GPU_OUTPUT"
echo ""

echo "Step 3: Create side-by-side comparison"
if command -v convert &> /dev/null; then
    convert "$CPU_OUTPUT" "$GPU_OUTPUT" +append "$COMP_OUTPUT"
    echo "✓ Comparison created: $COMP_OUTPUT"
    echo ""
    echo "Visual verification:"
    echo "  - Both images should show orange glow from Single Trap Light"
    echo "  - Pattern should match between CPU and GPU"
    echo "  - Any differences would indicate GPU implementation error"
else
    echo "⚠ ImageMagick not available, skipping side-by-side comparison"
    echo ""
    echo "Manual verification required:"
    echo "  CPU: $CPU_OUTPUT"
    echo "  GPU: $GPU_OUTPUT"
fi
echo ""
echo "=== Test complete ==="
