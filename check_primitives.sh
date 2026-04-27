#!/bin/bash
# Complete Primitives Recovery Verification Tool

echo "=================================="
echo "PRIMITIVES RECOVERY VERIFICATION"
echo "=================================="
echo ""

ERRORS=0
WARNINGS=0

# Check extracted files
echo "[1] EXTRACTED FILES CHECK"
echo "------------------------"
EXTRACTED_DIR="$HOME/mandelbulber2_recovery/extracted/primitives"

if [ -d "$EXTRACTED_DIR" ]; then
    echo "✓ Extracted directory exists: $EXTRACTED_DIR"

    echo "  CPP files: $(ls $EXTRACTED_DIR/cpp/*.cpp $EXTRACTED_DIR/cpp/*.h* 2>/dev/null | wc -l)"
    echo "  OpenCL files: $(ls $EXTRACTED_DIR/opencl/*.cl 2>/dev/null | wc -l)"
    echo "  Qt UI files: $(ls $EXTRACTED_DIR/qt_ui/*.ui 2>/dev/null | wc -l)"
    echo "  Python files: $(ls $EXTRACTED_DIR/python/*.py 2>/dev/null | wc -l)"
else
    echo "✗ ERROR: Extracted directory not found!"
    ERRORS=$((ERRORS + 1))
fi
echo ""

# Check source files in v2_experiment
echo "[2] SOURCE FILES IN PROJECT"
echo "---------------------------"
PROJECT_DIR="$HOME/mandelbulber2_v2_experiment/mandelbulber2"

for file in primitive.cpp primitive.hpp primitive_item.h primitives.cpp primitives.h; do
    if [ -f "$PROJECT_DIR/src/$file" ]; then
        SIZE=$(stat -c%s "$PROJECT_DIR/src/$file")
        if [ $SIZE -gt 100 ]; then
            echo "✓ $file (${SIZE} bytes)"
        else
            echo "✗ WARNING: $file is too small (${SIZE} bytes)"
            WARNINGS=$((WARNINGS + 1))
        fi
    else
        echo "✗ ERROR: Missing $PROJECT_DIR/src/$file"
        ERRORS=$((ERRORS + 1))
    fi
done
echo ""

# Check Qt files
echo "[3] QT/DOCK FILES"
echo "-----------------"
for file in dock_object_tree.cpp dock_object_tree.h primitives_manager.cpp primitives_manager.h primitives_manager.ui; do
    if [ -f "$PROJECT_DIR/qt/$file" ]; then
        SIZE=$(stat -c%s "$PROJECT_DIR/qt/$file")
        echo "✓ $file (${SIZE} bytes)"
    else
        echo "✗ ERROR: Missing $PROJECT_DIR/qt/$file"
        ERRORS=$((ERRORS + 1))
    fi
done
echo ""

# Check OpenCL
echo "[4] OPENCL FILES"
echo "----------------"
if [ -f "$PROJECT_DIR/opencl/engines/primitives.cl" ]; then
    SIZE=$(stat -c%s "$PROJECT_DIR/opencl/engines/primitives.cl")
    echo "✓ primitives.cl (${SIZE} bytes)"
else
    echo "✗ ERROR: Missing primitives.cl"
    ERRORS=$((ERRORS + 1))
fi

if [ -f "$PROJECT_DIR/opencl/primitives_cl.h" ]; then
    SIZE=$(stat -c%s "$PROJECT_DIR/opencl/primitives_cl.h")
    echo "✓ primitives_cl.h (${SIZE} bytes)"
else
    echo "✗ ERROR: Missing primitives_cl.h"
    ERRORS=$((ERRORS + 1))
fi
echo ""

# Check UI files in formula/ui (source)
echo "[5] FORMULA UI FILES (source)"
echo "-----------------------------"
FORMULA_UI_SRC="$PROJECT_DIR/formula/ui"
PRIM_UI_COUNT=$(ls $FORMULA_UI_SRC/primitive_*.ui 2>/dev/null | wc -l)
echo "Primitive UI files: $PRIM_UI_COUNT"

if [ $PRIM_UI_COUNT -ge 16 ]; then
    echo "✓ Found $PRIM_UI_COUNT primitive UI files"
else
    echo "✗ WARNING: Only $PRIM_UI_COUNT primitive UI files (expected 16+)"
    WARNINGS=$((WARNINGS + 1))
fi
echo ""

# Check deploy structure
echo "[6] DEPLOY/SHARE STRUCTURE"
echo "---------------------------"
DEPLOY_DIR="$PROJECT_DIR/deploy/share/mandelbulber2"

# Check symlinks
if [ -L "$PROJECT_DIR/share" ]; then
    TARGET=$(readlink "$PROJECT_DIR/share")
    echo "✓ share symlink → $TARGET"
else
    echo "✗ ERROR: Missing share symlink!"
    ERRORS=$((ERRORS + 1))
fi

if [ -L "$DEPLOY_DIR/opencl" ]; then
    TARGET=$(readlink "$DEPLOY_DIR/opencl")
    echo "✓ opencl symlink → $TARGET"
else
    echo "✗ ERROR: Missing opencl symlink in deploy!"
    ERRORS=$((ERRORS + 1))
fi
echo ""

# Check formula files in deploy
echo "[7] FORMULA FILES IN DEPLOY"
echo "----------------------------"
DEPLOY_FORMULA="$DEPLOY_DIR/formula"

UI_COUNT=$(ls $DEPLOY_FORMULA/ui/*.ui 2>/dev/null | wc -l)
echo "UI files in deploy: $UI_COUNT"
if [ $UI_COUNT -ge 470 ]; then
    echo "✓ Found $UI_COUNT UI files"
else
    echo "✗ WARNING: Only $UI_COUNT UI files (expected 472)"
    WARNINGS=$((WARNINGS + 1))
fi

CL_COUNT=$(ls $DEPLOY_FORMULA/opencl/*.cl 2>/dev/null | wc -l)
echo "OpenCL files in deploy: $CL_COUNT"
if [ $CL_COUNT -ge 450 ]; then
    echo "✓ Found $CL_COUNT OpenCL files"
else
    echo "✗ WARNING: Only $CL_COUNT OpenCL files (expected 458)"
    WARNINGS=$((WARNINGS + 1))
fi

# Check specific primitive UI files in deploy
echo ""
echo "Checking specific primitive UI files in deploy:"
for prim in box sphere torus cone cylinder; do
    if [ -f "$DEPLOY_FORMULA/ui/primitive_${prim}.ui" ]; then
        SIZE=$(stat -c%s "$DEPLOY_FORMULA/ui/primitive_${prim}.ui")
        echo "  ✓ primitive_${prim}.ui (${SIZE} bytes)"
    else
        echo "  ✗ ERROR: Missing primitive_${prim}.ui"
        ERRORS=$((ERRORS + 1))
    fi
done
echo ""

# Check binary
echo "[8] BINARY STATUS"
echo "-----------------"
BINARY="$PROJECT_DIR/qmake/mandelbulber2"
if [ -f "$BINARY" ]; then
    SIZE=$(stat -c%s "$BINARY")
    MTIME=$(stat -c%y "$BINARY" | cut -d' ' -f1-2)
    echo "✓ Binary exists: $SIZE bytes"
    echo "  Last modified: $MTIME"
else
    echo "✗ ERROR: Binary not found!"
    ERRORS=$((ERRORS + 1))
fi
echo ""

# Check if files are actually readable
echo "[9] FILE CONTENT VERIFICATION"
echo "------------------------------"
# Check if primitive.cpp contains expected code
if grep -q "sPrimitiveBasic" "$PROJECT_DIR/src/primitive.cpp" 2>/dev/null; then
    echo "✓ primitive.cpp contains expected code"
else
    echo "✗ ERROR: primitive.cpp missing expected code!"
    ERRORS=$((ERRORS + 1))
fi

# Check if primitives.cl contains expected code
if grep -q "PrimitiveDistance\|CalculatePrimitives" "$PROJECT_DIR/opencl/engines/primitives.cl" 2>/dev/null; then
    echo "✓ primitives.cl contains expected code"
else
    echo "✗ ERROR: primitives.cl missing expected code!"
    ERRORS=$((ERRORS + 1))
fi

# Check if dock_object_tree exists
if grep -q "cDockObjectTree\|object.*tree" "$PROJECT_DIR/qt/dock_object_tree.cpp" 2>/dev/null; then
    echo "✓ dock_object_tree.cpp contains expected code"
else
    echo "✗ ERROR: dock_object_tree.cpp missing expected code!"
    ERRORS=$((ERRORS + 1))
fi
echo ""

# Summary
echo "=================================="
echo "SUMMARY"
echo "=================================="
echo "Errors:   $ERRORS"
echo "Warnings: $WARNINGS"
echo ""

if [ $ERRORS -eq 0 ] && [ $WARNINGS -eq 0 ]; then
    echo "✓✓✓ ALL CHECKS PASSED ✓✓✓"
    echo ""
    echo "Primitives should be visible in Mandelbulber!"
    echo "Look for: Objects menu → Add Primitive"
    exit 0
elif [ $ERRORS -eq 0 ]; then
    echo "⚠ PASSED WITH WARNINGS ⚠"
    exit 1
else
    echo "✗✗✗ FAILED - ERRORS FOUND ✗✗✗"
    echo ""
    echo "Please fix the errors above before running Mandelbulber."
    exit 2
fi
