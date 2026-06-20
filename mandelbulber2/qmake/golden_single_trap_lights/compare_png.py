#!/usr/bin/env python3
"""Compare two 8-bit RGB or RGBA PNGs; exit 0 if RMSE (per channel, 0–1 scale) is within limit."""
from __future__ import annotations

import argparse
import struct
import sys
import zlib


def read_png_rgb(path: str) -> tuple[int, int, bytes]:
    """Return (width, height, rgb_bytes) with len = width*height*3."""
    with open(path, "rb") as f:
        data = f.read()
    if data[:8] != b"\x89PNG\r\n\x1a\n":
        raise ValueError(f"not a PNG: {path}")
    pos = 8
    width = height = None
    bpp = 0
    idat = b""
    while pos < len(data):
        if pos + 12 > len(data):
            break
        length = struct.unpack(">I", data[pos : pos + 4])[0]
        pos += 4
        ctype = data[pos : pos + 4]
        pos += 4
        chunk = data[pos : pos + length]
        pos += length
        pos += 4
        if ctype == b"IHDR":
            width, height, bit_depth, color_type, comp, filt, inter = struct.unpack(
                ">IIBBBBB", chunk
            )
            if bit_depth != 8 or inter != 0:
                raise ValueError(f"unsupported PNG format in {path}")
            if color_type == 2:
                bpp = 3
            elif color_type == 6:
                bpp = 4
            else:
                raise ValueError(f"unsupported PNG color type {color_type} in {path}")
        elif ctype == b"IDAT":
            idat += chunk
        elif ctype == b"IEND":
            break
    if width is None or bpp == 0:
        raise ValueError(f"missing IHDR in {path}")
    raw = zlib.decompress(idat)
    stride = width * bpp
    out = bytearray(height * stride)
    i = 0
    prev = bytearray(stride)

    def paeth(a: int, b: int, c: int) -> int:
        p = a + b - c
        pa = abs(p - a)
        pb = abs(p - b)
        pc = abs(p - c)
        if pa <= pb and pa <= pc:
            return a
        if pb <= pc:
            return b
        return c

    for _y in range(height):
        filt_type = raw[i]
        i += 1
        scan = bytearray(raw[i : i + stride])
        i += stride
        if filt_type == 0:
            pass
        elif filt_type == 1:
            for x in range(stride):
                left = scan[x - bpp] if x >= bpp else 0
                scan[x] = (scan[x] + left) & 0xFF
        elif filt_type == 2:
            for x in range(stride):
                scan[x] = (scan[x] + prev[x]) & 0xFF
        elif filt_type == 3:
            for x in range(stride):
                left = scan[x - bpp] if x >= bpp else 0
                up = prev[x]
                scan[x] = (scan[x] + ((left + up) // 2)) & 0xFF
        elif filt_type == 4:
            for x in range(stride):
                a = scan[x - bpp] if x >= bpp else 0
                b = prev[x]
                c = prev[x - bpp] if x >= bpp else 0
                scan[x] = (scan[x] + paeth(a, b, c)) & 0xFF
        else:
            raise ValueError(f"unsupported filter {filt_type}")
        out[_y * stride : (_y + 1) * stride] = scan
        prev = scan

    raw_bytes = bytes(out)
    if bpp == 3:
        return width, height, raw_bytes
    rgb = bytearray(width * height * 3)
    j = 0
    for pix in range(width * height):
        o = pix * 4
        rgb[j] = raw_bytes[o]
        rgb[j + 1] = raw_bytes[o + 1]
        rgb[j + 2] = raw_bytes[o + 2]
        j += 3
    return width, height, bytes(rgb)


def rmse_rgb(a: bytes, b: bytes, w: int, h: int) -> float:
    if len(a) != len(b):
        raise ValueError("buffer size mismatch")
    n = w * h * 3
    s = 0.0
    for i in range(n):
        d = int(a[i]) - int(b[i])
        s += d * d
    return (s / n) ** 0.5 / 255.0


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("a")
    ap.add_argument("b")
    ap.add_argument("--rmse-max", type=float, default=0.028)
    args = ap.parse_args()
    w1, h1, p1 = read_png_rgb(args.a)
    w2, h2, p2 = read_png_rgb(args.b)
    if (w1, h1) != (w2, h2):
        print(f"size mismatch {(w1,h1)} vs {(w2,h2)}", file=sys.stderr)
        return 1
    r = rmse_rgb(p1, p2, w1, h1)
    print(f"RMSE (RGB, 0–1 scale): {r:.6f} (limit {args.rmse_max})")
    if r > args.rmse_max:
        print("FAIL: RMSE above limit", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
