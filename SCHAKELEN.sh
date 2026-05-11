#!/bin/bash
# SCHAKELEN tussen STABIEL en WIP
# Gebruik: ./SCHAKELEN.sh stabiel   (of: ./SCHAKELEN.sh wip)

set -e

cd "$(dirname "$0")/mandelbulber2"

MODE="${1:-help}"

if [ "$MODE" = "stabiel" ] || [ "$MODE" = "stable" ]; then
    echo "=== SCHAKELEN NAAR STABIEL ==="
    git stash push -m "auto-stash-voor-stabiel" 2>/dev/null || true
    git checkout backup-gradient-system-perfect-skeleton
    echo "Stabiele branch geladen."
    echo ""
    echo "OM TE BOUWEN:"
    echo "  cd mandelbulber2/build"
    echo "  make clean && qmake ../qmake/mandelbulber.pro && make -j\$(nproc)"
    
elif [ "$MODE" = "wip" ]; then
    echo "=== SCHAKELEN NAAR WIP ==="
    git checkout wip-2026-05-10
    git stash pop 2>/dev/null || true
    echo "WIP branch geladen."
    echo ""
    echo "OM TE BOUWEN:"
    echo "  cd mandelbulber2/build"
    echo "  make clean && qmake ../qmake/mandelbulber.pro && make -j\$(nproc)"
    
else
    echo "Gebruik: ./SCHAKELEN.sh stabiel   → stabiele auto-fog branch"
    echo "         ./SCHAKELEN.sh wip        → work-in-progress branch"
    echo ""
    echo "Huidige branch: $(git branch --show-current)"
fi
