#!/bin/bash
# Mandelbulber Advanced Weight System v3.0 - Clean Build Script
# Run this from the repository root directory
set -e

echo "=== Mandelbulber Advanced Weight System v3.0 - Clean Build ==="
echo ""

# Ensure we're in the right directory
if [ ! -f "mandelbulber2/src/compute_fractal.cpp" ]; then
    echo "ERROR: Run this script from the repository root (where mandelbulber2/ folder is)"
    exit 1
fi

# Step 1: Make sure we're on the correct branch
echo "[1/5] Checking out latest code..."
git fetch origin
git checkout devin/1779255472-fix-gradient-and-cleanup
git reset --hard origin/devin/1779255472-fix-gradient-and-cleanup
echo "  OK - on branch devin/1779255472-fix-gradient-and-cleanup"
echo ""

# Step 2: Verify the weight code exists
echo "[2/5] Verifying advanced weight code..."
if grep -q "CalculateWeight" mandelbulber2/src/compute_fractal.cpp; then
    echo "  OK - CalculateWeight found in compute_fractal.cpp"
else
    echo "  ERROR: CalculateWeight NOT found! Code is wrong."
    exit 1
fi
if grep -q "weight_mode" mandelbulber2/src/initparameters.cpp; then
    echo "  OK - weight_mode found in initparameters.cpp"
else
    echo "  ERROR: weight_mode NOT found! Code is wrong."
    exit 1
fi
if grep -q "weightModeOrbitTrap" mandelbulber2/src/nine_fractals.hpp; then
    echo "  OK - OrbitTrap mode found (v3.0 features present)"
else
    echo "  WARNING: OrbitTrap mode not found - may be older version"
fi
echo ""

# Step 3: Full clean build
echo "[3/5] Full clean build (this takes a few minutes)..."
cd mandelbulber2/qmake
rm -rf *.o moc_* ui_* mandelbulber2 Makefile
qmake mandelbulber-opencl.pro
make -j$(nproc) 2>&1 | tail -3
cd ../..
echo ""

# Step 4: Verify binary was built
if [ -f "mandelbulber2/qmake/mandelbulber2" ]; then
    echo "[4/5] OK - Binary built successfully!"
    echo "  Size: $(ls -lh mandelbulber2/qmake/mandelbulber2 | awk '{print $5}')"
    echo "  Date: $(date)"
else
    echo "[4/5] ERROR - Binary not found after build!"
    exit 1
fi
echo ""

# Step 5: Verify weight code is in binary
if strings mandelbulber2/qmake/mandelbulber2 | grep -q "weight_mode"; then
    echo "[5/5] OK - Advanced weight parameters confirmed in binary!"
else
    echo "[5/5] WARNING - Could not verify weight params in binary (may still work)"
fi

echo ""
echo "=== BUILD COMPLETE ==="
echo ""
echo "Start the app with:"
echo "  cd mandelbulber2/qmake && ./mandelbulber2"
echo ""
echo "You should see in the terminal:"
echo "  'Advanced Weight System v3.0 - build 20250520'"
echo ""
echo "Test the advanced weight system:"
echo "  1. Enable 'Hybrid fractals' checkbox"
echo "  2. Set Formula 1 = Mandelbulb, Formula 2 = Menger Sponge"
echo "  3. Render with CPU"
echo "  4. In Formula 1 tab -> 'Advanced Weight System' -> change parameters:"
echo "     - Weight Mode: Static/Iteration/DE/ZLength/Conditional/OrbitTrap/Curve"
echo "     - Mod Types: Linear/Smooth/Exponential/Inverse/Sigmoid"
echo "  5. You should see changes in the render"
echo ""
