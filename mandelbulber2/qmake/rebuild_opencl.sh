#!/usr/bin/env bash
# Canonical full rebuild: avoids stale .o / divergent qmake vs other build dirs.
set -euo pipefail
cd "$(dirname "$0")"
echo "[rebuild_opencl] distclean + qmake + make"
make distclean
qmake mandelbulber-opencl.pro
make -j"$(nproc)"
echo "[rebuild_opencl] OK: $(pwd)/mandelbulber2"
