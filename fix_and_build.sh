#!/bin/bash
set -e

echo "=== STAP 1: Git reset naar laatste versie ==="
cd ~/mandelbulber2
git fetch --all
git reset --hard origin/clean-mutation-work
echo "OK: Code is up-to-date (commit $(git rev-parse --short HEAD))"

echo ""
echo "=== STAP 2: Clean build ==="
cd qmake
rm -f Makefile mandelbulber2
qmake mandelbulber-opencl.pro
make -j$(nproc)
echo "OK: Build succesvol"

echo ""
echo "=== STAP 3: Formula bestanden deployen ==="
cd ~/mandelbulber2
rm -rf deploy/share/mandelbulber2/formula
mkdir -p deploy/share/mandelbulber2/formula
cp -r formula/ui deploy/share/mandelbulber2/formula/
cp -r formula/opencl deploy/share/mandelbulber2/formula/
cp -r formula/definition deploy/share/mandelbulber2/formula/
echo "OK: $(ls deploy/share/mandelbulber2/formula/ui/*.ui | wc -l) .ui files gedeployed"
echo "OK: $(ls deploy/share/mandelbulber2/formula/opencl/*.cl | wc -l) .cl files gedeployed"

echo ""
echo "=== STAP 4: Verificatie ==="
ls deploy/share/mandelbulber2/formula/ui/amazing_surf.ui >/dev/null && echo "OK: amazing_surf.ui gevonden"
ls deploy/share/mandelbulber2/formula/opencl/amazing_surf.cl >/dev/null && echo "OK: amazing_surf.cl gevonden"
ls deploy/share/mandelbulber2/formula/ui/mandelbulb.ui >/dev/null && echo "OK: mandelbulb.ui gevonden"
ls deploy/share/mandelbulber2/formula/opencl/mandelbulb.cl >/dev/null && echo "OK: mandelbulb.cl gevonden"
grep -q "surfFoldPower" deploy/share/mandelbulber2/formula/ui/amazing_surf.ui && echo "OK: Extension params in .ui"
grep -q "surfFoldPower" deploy/share/mandelbulber2/formula/opencl/amazing_surf.cl && echo "OK: Extension params in .cl"
grep -q "surfFoldPower" deploy/share/mandelbulber2/formula/definition/fractal_amazing_surf.cpp && echo "OK: Extension params in .cpp"

echo ""
echo "=== KLAAR! Start Mandelbulber: ==="
echo "cd ~/mandelbulber2/qmake && ./mandelbulber2"
echo ""
echo "Test: Amazing Surf → scroll naar 'Amazing Surf Extensions' → vink AAN → Fold Power op 1.20 → Render"
