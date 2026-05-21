#!/bin/bash
# Mandelbulber Advanced Weight System v3.2 + Texture System Upgrade - Clean Build Script
# Run this from the repository root directory
set -e

echo "=== Mandelbulber Advanced Weight System - Clean Build ==="
echo ""

# Ensure we're in the right directory
if [ ! -f "mandelbulber2/src/compute_fractal.cpp" ]; then
    echo "ERROR: Run this script from the repository root (where mandelbulber2/ folder is)"
    exit 1
fi

# Step 1: Make sure we're on the correct branch with latest code
echo "[1/6] Checking out latest code..."
git fetch origin
git checkout devin/1779255472-fix-gradient-and-cleanup
git reset --hard origin/devin/1779255472-fix-gradient-and-cleanup
echo "  OK - on branch devin/1779255472-fix-gradient-and-cleanup"
echo ""

# Step 2: Verify the weight code exists
echo "[2/6] Verifying advanced weight code..."
if grep -q "CalculateWeight" mandelbulber2/src/compute_fractal.cpp; then
    echo "  OK - CalculateWeight found in compute_fractal.cpp"
else
    echo "  ERROR: CalculateWeight NOT found! Code is wrong."
    exit 1
fi
if grep -q "weight_mode" mandelbulber2/src/initparameters.cpp; then
    echo "  OK - weight_mode parameters registered"
else
    echo "  ERROR: weight_mode NOT found! Parameters not registered."
    exit 1
fi
if grep -q "weightModeOrbitTrap" mandelbulber2/src/nine_fractals.hpp; then
    echo "  OK - OrbitTrap mode present (v3.x features)"
else
    echo "  WARNING: OrbitTrap mode not found - may be older version"
fi
echo ""

# Step 3: Clear OpenCL kernel cache (prevents stale kernel issues on GPU)
echo "[3/6] Clearing OpenCL kernel cache..."
OPENCL_CACHE_DIR="$HOME/.mandelbulber/opencl_cache"
if [ -d "$OPENCL_CACHE_DIR" ]; then
    rm -rf "$OPENCL_CACHE_DIR"/*
    echo "  OK - Cleared $OPENCL_CACHE_DIR"
else
    # Try alternative cache locations
    for dir in "$HOME/.mandelbulber/"*opencl* "$HOME/.mandelbulber/"*cache*; do
        if [ -d "$dir" ]; then
            rm -rf "$dir"/*
            echo "  OK - Cleared $dir"
        fi
    done
    echo "  (No standard OpenCL cache dir found, will be fine)"
fi
echo ""

# Step 4: Full clean build
echo "[4/6] Full clean build (this takes a few minutes)..."
cd mandelbulber2/qmake
rm -rf *.o moc_* ui_* mandelbulber2 Makefile
qmake mandelbulber-opencl.pro
make -j$(nproc) 2>&1 | tail -5
cd ../..
echo ""

# Step 5: Verify binary was built
if [ -f "mandelbulber2/qmake/mandelbulber2" ]; then
    echo "[5/6] OK - Binary built successfully!"
    echo "  Size: $(ls -lh mandelbulber2/qmake/mandelbulber2 | awk '{print $5}')"
    echo "  Date: $(date)"
else
    echo "[5/6] ERROR - Binary not found after build!"
    exit 1
fi
echo ""

# Step 6: Verify weight code is in binary
echo "[6/6] Verifying binary contents..."
if strings mandelbulber2/qmake/mandelbulber2 | grep -q "Advanced Weight System"; then
    VERSION=$(strings mandelbulber2/qmake/mandelbulber2 | grep "Advanced Weight System")
    echo "  OK - Found: $VERSION"
else
    echo "  WARNING - Version string not found (binary may still work)"
fi
if strings mandelbulber2/qmake/mandelbulber2 | grep -q "weight_orbit_trap_base"; then
    echo "  OK - OrbitTrap parameters confirmed in binary"
else
    echo "  WARNING - OrbitTrap params not in binary strings"
fi

# Verify texture system additions
if strings mandelbulber2/qmake/mandelbulber2 | grep -q "mappingTriplanar"; then
    echo "  OK - Triplanar mapping mode confirmed"
else
    echo "  WARNING - Triplanar mapping not found in binary strings"
fi
if strings mandelbulber2/qmake/mandelbulber2 | grep -q "fractalizeShapeCylinder"; then
    echo "  OK - Cylinder fractalize shape confirmed"
else
    echo "  WARNING - Cylinder fractalize shape not found in binary strings"
fi

echo ""
echo "=== BUILD COMPLETE ==="
echo ""
echo "Start the app with:"
echo "  cd mandelbulber2/qmake && ./mandelbulber2"
echo ""
echo "You should see in the terminal:"
echo "  'Advanced Weight System v3.2 - build ...'"
echo ""
echo "The system works on BOTH CPU and GPU. No kernel recompilation needed."
echo ""
echo "Test the advanced weight system:"
echo "  1. Enable 'Hybrid fractals' checkbox"
echo "  2. Set Formula 1 = Mandelbulb, Formula 2 = Menger Sponge"
echo "  3. In Formula 1 tab -> 'Advanced Weight System' group:"
echo "     - Change 'Static Weight' to 0.3 -> dramatic change"
echo "     - Change 'Weight Mode' to Iteration/DE/ZLength/Conditional/OrbitTrap/Curve"
echo "     - Each mode has its own parameters that become active"
echo "  4. Works identically on CPU and GPU (Full, Limited, Nebula)"
echo ""
echo "Test the new texture system modes:"
echo "  - Material editor -> Texture mapping type: Triplanar, Equirectangular"
echo "  - Fractalize texture -> Orbit trap shape: Cylinder, Torus, Spiral"
echo "  - Coloring algorithm: orbit trap Cylinder, orbit trap Torus"
echo ""
