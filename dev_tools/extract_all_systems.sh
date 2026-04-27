#!/bin/bash
# Extract All Systems - Interactive Wrapper
# Runs all 4 extraction phases with manual confirmation per phase

set -e

cd "$(dirname "$0")/.."

echo "╔════════════════════════════════════════════════════════════════════╗"
echo "║              EXTRACT ALL SYSTEMS - 4 PHASES                        ║"
echo "╚════════════════════════════════════════════════════════════════════╝"
echo ""
echo "This will extract 4 transform systems in order:"
echo "  1. Pivot/World Space System"
echo "  2. Epic Repeat System"
echo "  3. Deformation System"
echo "  4. Emission System"
echo ""
echo "Each phase requires manual confirmation!"
echo ""

# Phase 1: Pivot
echo "══════════════════════════════════════════════════════════════════════"
echo "PHASE 1: PIVOT/WORLD SPACE SYSTEM"
echo "══════════════════════════════════════════════════════════════════════"
echo ""
read -p "Start Phase 1? (y/n): " -n 1 -r
echo ""
if [[ $REPLY =~ ^[Yy]$ ]]; then
    python3 dev_tools/safe_system_extractor.py pivot
    if [ $? -ne 0 ]; then
        echo "❌ Phase 1 failed! Stopping."
        exit 1
    fi
    echo ""
    echo "✅ Phase 1 complete!"
else
    echo "❌ Phase 1 skipped."
    exit 1
fi

echo ""
read -p "Continue to Phase 2? (y/n): " -n 1 -r
echo ""
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Stopped after Phase 1"
    exit 0
fi

# Phase 2: Repeat
echo ""
echo "══════════════════════════════════════════════════════════════════════"
echo "PHASE 2: EPIC REPEAT SYSTEM"
echo "══════════════════════════════════════════════════════════════════════"
echo ""
python3 dev_tools/safe_system_extractor.py repeat
if [ $? -ne 0 ]; then
    echo "❌ Phase 2 failed! Stopping."
    exit 1
fi
echo ""
echo "✅ Phase 2 complete!"

echo ""
read -p "Continue to Phase 3? (y/n): " -n 1 -r
echo ""
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Stopped after Phase 2"
    exit 0
fi

# Phase 3: Deform
echo ""
echo "══════════════════════════════════════════════════════════════════════"
echo "PHASE 3: DEFORMATION SYSTEM"
echo "══════════════════════════════════════════════════════════════════════"
echo ""
python3 dev_tools/safe_system_extractor.py deform
if [ $? -ne 0 ]; then
    echo "❌ Phase 3 failed! Stopping."
    exit 1
fi
echo ""
echo "✅ Phase 3 complete!"

echo ""
read -p "Continue to Phase 4 (final)? (y/n): " -n 1 -r
echo ""
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Stopped after Phase 3"
    exit 0
fi

# Phase 4: Emission
echo ""
echo "══════════════════════════════════════════════════════════════════════"
echo "PHASE 4: EMISSION SYSTEM (FINAL)"
echo "══════════════════════════════════════════════════════════════════════"
echo ""
python3 dev_tools/safe_system_extractor.py emission
if [ $? -ne 0 ]; then
    echo "❌ Phase 4 failed!"
    exit 1
fi
echo ""
echo "✅ Phase 4 complete!"

echo ""
echo "╔════════════════════════════════════════════════════════════════════╗"
echo "║              🎉 ALL 4 PHASES COMPLETE! 🎉                          ║"
echo "╚════════════════════════════════════════════════════════════════════╝"
echo ""
echo "All transform systems have been extracted successfully!"
echo ""
echo "Safety backups are in: SAFETY_BACKUPS/"
echo ""
echo "Next steps:"
echo "  1. Test the systems in Mandelbulber"
echo "  2. Run git status to see changes"
echo "  3. Commit the changes"
echo ""
