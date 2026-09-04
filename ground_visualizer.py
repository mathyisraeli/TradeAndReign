#!/usr/bin/env python3
"""3D terrain visualizer for a world/gN.txt ground file.

Usage: python3 ground_visualizer.py world/g1.txt

Reads only a ground file (no map/character file). Each grid cell is a stack
of textured layers ("wat5soi3..."); the last layer written is the current
top texture (see serv/ground.c: create_array() prepends each parsed layer,
so the last-read layer ends up as the head / visible surface), and the
altitude plotted is the sum of every layer's altitude (matches serv's
altitude() helper).

Units: 1 grid unit right (x) = 1 m, 1 grid unit forward (y) = 1 m, but
1 altitude unit (z) = 1/38 m. Altitudes are converted to meters and the
plot's box aspect is locked to the real x/y/z extents so the render is
not vertically exaggerated.
"""
import argparse
import re
import sys

import numpy as np
import matplotlib.pyplot as plt

CELL_RE = re.compile(r'([A-Za-z]{3})(\d+)')

# Texture -> RGB color, grouped by material family so related textures
# (e.g. all shale variants) read as visually related.
TEXTURE_COLORS = {
    "wat": "#2b6cb0",  # water = blue
    "soi": "#8b5a2b",  # soil/dirt = brown

    "lim": "#e0d8c3", "lii": "#d9cfb8", "lis": "#cfc3a8",  # limestone = pale beige

    "qua": "#9a9a9a", "qui": "#8f8f8f", "qug": "#a6a6a6", "qus": "#b5b5b5",
    "quz": "#c2c2c2", "qzc": "#7f7f7f", "qzg": "#747474", "qzs": "#6a6a6a",  # quartz/rock = gray

    "bas": "#4a4a4a", "bai": "#3f3f3f", "bac": "#353535", "bal": "#2a2a2a",  # basalt = dark gray

    "gra": "#8c8c8c", "gri": "#7d7d7d", "grc": "#93938a", "grt": "#726f68",
    "grd": "#5c5c52", "grs": "#a3a396",  # granite (not grass) = gray

    "san": "#e6c589", "sai": "#e0bb78", "sag": "#d9ae63",  # sand = tan

    "sha": "#8d7b68", "shv": "#96856f", "shs": "#7a6a58", "shg": "#836f5c",
    "sht": "#6f5f4e", "shl": "#a08e78", "shc": "#665849", "shi": "#8a7862",  # shale = grayish brown

    "mar": "#f2f2f2", "mai": "#e8e8e8",  # marble = white

    "gys": "#e8dfc8", "gyp": "#ddd3b8",  # gypsum = pale tan

    "coa": "#1c1c1c",  # coal = near black
    "sal": "#f7f7f7",  # salt = white
    "snd": "#d9c07a",  # dune sand = darker tan
    "dus": "#c2b280",  # dust = khaki
    "sno": "#ffffff",  # snow = white

    # "g"-prefixed = grass growing over the base texture (e.g. "ggr" = grass
    # over granite): tinted green.
    "gLi": "#8fae5c", "gqa": "#7fae6b", "gqz": "#6fae7b", "gba": "#5f9e6b",
    "ggr": "#4caf50", "gsa": "#9fae5c", "gsh": "#7f9e5c", "gma": "#a3b58a",
    "ggy": "#a9b58a",
}
DEFAULT_COLOR = "#ff00ff"  # unknown texture -> obvious magenta

ALTITUDE_UNITS_PER_METER = 38  # 1 altitude unit = 1/38 m; x/y units are already 1 m


def load_ground(path):
    with open(path, "r") as f:
        content = f.read()
    tokens = content.split()
    if len(tokens) < 2:
        sys.exit(f"error: {path} is empty or missing its 'max_x max_y' header")
    max_x = int(tokens[0])
    max_y = int(tokens[1])
    cells = tokens[2:2 + max_x * max_y]
    if len(cells) != max_x * max_y:
        sys.exit(f"error: expected {max_x * max_y} cells, found {len(cells)}")
    return max_x, max_y, cells


def main():
    parser = argparse.ArgumentParser(description="3D terrain visualizer for a ground file")
    parser.add_argument("ground_file", help="path to a world/gN.txt ground file")
    args = parser.parse_args()

    max_x, max_y, cells = load_ground(args.ground_file)

    n = max_x * max_y
    xs = np.empty(n, dtype=np.int32)
    ys = np.empty(n, dtype=np.int32)
    zs = np.empty(n, dtype=np.float64)
    colors = np.empty(n, dtype=object)

    idx = 0
    for i in range(max_y):
        for j in range(max_x):
            layers = CELL_RE.findall(cells[idx])
            if not layers:
                sys.exit(f"error: unparseable cell at row {i} col {j}: {cells[idx]!r}")
            top_texture = layers[-1][0]
            total_alt = sum(int(a) for _, a in layers)
            xs[idx] = j
            ys[idx] = i
            zs[idx] = total_alt / ALTITUDE_UNITS_PER_METER  # -> meters
            colors[idx] = TEXTURE_COLORS.get(top_texture, DEFAULT_COLOR)
            idx += 1

    fig = plt.figure(figsize=(12, 10))
    ax = fig.add_subplot(111, projection="3d")
    ax.scatter(xs, ys, zs, c=colors, marker="s", s=6, depthshade=False, linewidths=0)

    # True-to-scale proportions: x and y are already in meters (1 unit = 1 m),
    # z was just converted to meters, so the box aspect uses the real extents
    # directly instead of an arbitrary vertical exaggeration factor.
    z_extent = float(zs.max() - zs.min()) or 1.0
    ax.set_box_aspect((max_x, max_y, z_extent))
    ax.set_xlabel("x (m)")
    ax.set_ylabel("y (m)")
    ax.set_zlabel("altitude (m)")
    ax.set_title(f"{args.ground_file} ({max_x}x{max_y})")
    ax.view_init(elev=25, azim=-60)

    unknown = sorted({c for c in colors if c == DEFAULT_COLOR})
    if unknown:
        print(f"warning: {len(unknown)} unmapped texture color(s) shown in magenta", file=sys.stderr)

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
