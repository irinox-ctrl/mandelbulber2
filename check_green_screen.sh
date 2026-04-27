#!/bin/bash
# Complete Green Screen Diagnostic Tool for Mandelbulber2
# Checks all possible causes of green/blue/pink screen errors

echo "=========================================="
echo "MANDELBULBER2 GREEN SCREEN DIAGNOSTIC TOOL"
echo "=========================================="
echo ""

# Kill all running instances
echo "[1/10] Killing all Mandelbulber instances..."
pkill -9 mandelbulber2 2>/dev/null
sleep 2
echo "✓ Done"
echo ""

# Clear OpenCL cache
echo "[2/10] Clearing OpenCL cache..."
rm -rf ~/.mandelbulber/openclCache/*
echo "✓ OpenCL cache cleared"
echo ""

# Check for OpenCL compilation errors in shader files
echo "[3/10] Checking OpenCL shader syntax..."
SHADER_DIR="/home/joeri/mandelbulber2_v2_experiment/mandelbulber2/share/mandelbulber2/opencl"

# Check for common OpenCL syntax errors
echo "  Checking for undefined struct members..."
grep -n "\.rotation\." "$SHADER_DIR/engines/shader_fake_lights.cl" 2>/dev/null && echo "  ⚠ WARNING: Found .rotation. access in shader_fake_lights.cl"
grep -n "\.rotation\." "$SHADER_DIR/engines/shader_volumetric.cl" 2>/dev/null && echo "  ⚠ WARNING: Found .rotation. access in shader_volumetric.cl"

echo "  Checking for missing semicolons..."
grep -n "float3 [a-zA-Z_][a-zA-Z0-9_]* =" "$SHADER_DIR/engines/"*.cl | grep -v ";" | head -5

echo "✓ Syntax check complete"
echo ""

# Check for enum validation errors
echo "[4/10] Checking for enum validation issues..."
echo "  Checking old enum values in settings files..."

# Check for "follow fractal" in fract files
if grep -r "follow fractal" ~/.mandelbulber/ 2>/dev/null | grep -v "Binary file" | head -3; then
    echo "  ⚠ WARNING: Found 'follow fractal' in settings files"
else
    echo "  ✓ No 'follow fractal' references found"
fi

# Check for backwards compatibility in code
if grep -q "if (value == \"follow fractal\") return 3" /home/joeri/mandelbulber2_v2_experiment/mandelbulber2/src/one_parameter.cpp; then
    echo "  ✓ Backwards compatibility for 'follow fractal' is implemented"
else
    echo "  ⚠ WARNING: Backwards compatibility for 'follow fractal' NOT found"
fi

echo ""

# Check parameter initialization
echo "[5/10] Checking for uninitialized parameters..."
INIT_FILE="/home/joeri/mandelbulber2_v2_experiment/mandelbulber2/src/initparameters.cpp"

echo "  Checking fake_lights_position_mode parameter..."
if grep -q "fake_lights_position_mode" "$INIT_FILE"; then
    echo "  ✓ fake_lights_position_mode is defined"
else
    echo "  ⚠ WARNING: fake_lights_position_mode NOT defined in initparameters.cpp"
fi

echo "  Checking fake_lights_mode_X parameters..."
for i in {0..7}; do
    if ! grep -q "fake_lights_mode_${i}_offset" "$INIT_FILE"; then
        echo "  ⚠ WARNING: fake_lights_mode_${i}_offset NOT defined"
    fi
done
echo "  ✓ Mode parameters check complete"
echo ""

# Start Mandelbulber and capture startup
echo "[6/10] Starting Mandelbulber and capturing startup log..."
cd /home/joeri/mandelbulber2_v2_experiment/mandelbulber2/qmake
timeout 10s ./mandelbulber2 > /tmp/mandelbulber_startup_diagnostic.log 2>&1 &
MANDELBULBER_PID=$!
sleep 8

if ps -p $MANDELBULBER_PID > /dev/null; then
    echo "  ✓ Mandelbulber started successfully (PID: $MANDELBULBER_PID)"
else
    echo "  ⚠ WARNING: Mandelbulber crashed during startup"
fi
echo ""

# Check for errors in startup log
echo "[7/10] Analyzing startup log for errors..."
if [ -f /tmp/mandelbulber_startup_diagnostic.log ]; then
    echo "  --- ENUMERATION ERRORS ---"
    grep -i "enumeration not found" /tmp/mandelbulber_startup_diagnostic.log | head -5

    echo ""
    echo "  --- OPENCL COMPILATION ERRORS ---"
    grep -i "error during compilation\|compilation.*failed" /tmp/mandelbulber_startup_diagnostic.log | head -5

    echo ""
    echo "  --- OPENCL SHADER ERRORS ---"
    grep "\.cl:[0-9]*:[0-9]*: error:" /tmp/mandelbulber_startup_diagnostic.log | head -10

    echo ""
    echo "  --- MISSING PARAMETERS ---"
    grep "doesn't exists" /tmp/mandelbulber_startup_diagnostic.log | cut -d'"' -f2 | sort -u | head -10
else
    echo "  ⚠ WARNING: Could not read startup log"
fi
echo ""

# Check ~/.mandelbulber_log.txt for recent errors
echo "[8/10] Checking main log file for recent errors..."
if [ -f ~/.mandelbulber_log.txt ]; then
    echo "  --- LAST 5 ERRORS ---"
    grep -i "error" ~/.mandelbulber_log.txt | tail -5

    echo ""
    echo "  --- LAST 5 OPENCL ERRORS ---"
    grep -i "opencl.*error\|fout.*opencl" ~/.mandelbulber_log.txt | tail -5
else
    echo "  ⚠ WARNING: Main log file not found"
fi
echo ""

# Check OpenCL device status
echo "[9/10] Checking OpenCL device status..."
if command -v clinfo &> /dev/null; then
    echo "  --- OPENCL PLATFORMS ---"
    clinfo -l 2>/dev/null | head -10
else
    echo "  ⚠ clinfo not available, skipping OpenCL device check"
fi
echo ""

# Final summary
echo "[10/10] DIAGNOSTIC SUMMARY"
echo "==========================================="

# Count errors
ENUM_ERRORS=$(grep -c "enumeration not found" /tmp/mandelbulber_startup_diagnostic.log 2>/dev/null || echo "0")
OPENCL_ERRORS=$(grep -c "\.cl:[0-9]*:[0-9]*: error:" /tmp/mandelbulber_startup_diagnostic.log 2>/dev/null || echo "0")

echo "Enumeration errors found: $ENUM_ERRORS"
echo "OpenCL compilation errors found: $OPENCL_ERRORS"

if [ "$ENUM_ERRORS" -eq 0 ] && [ "$OPENCL_ERRORS" -eq 0 ]; then
    echo ""
    echo "✓ NO CRITICAL ERRORS DETECTED"
    echo "  If you still see a green screen, the issue may be:"
    echo "  - Framebuffer initialization issue"
    echo "  - Missing texture data"
    echo "  - GPU driver issue"
else
    echo ""
    echo "⚠ CRITICAL ERRORS DETECTED - See details above"
fi

echo ""
echo "Full startup log saved to: /tmp/mandelbulber_startup_diagnostic.log"
echo "Main log file location: ~/.mandelbulber_log.txt"
echo ""
echo "Mandelbulber is still running (PID: $MANDELBULBER_PID)"
echo "Check the UI to see if the green screen persists."
echo "To kill: pkill -9 mandelbulber2"
echo "==========================================="
