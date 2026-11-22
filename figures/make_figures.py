"""Generate the figures of the handouts from the output of the example programs.

Usage (from the repository root, after building with the mingw-debug preset):

    .venv\\Scripts\\python.exe figures\\make_figures.py [--build-dir build\\mingw-debug]

Each figure is produced from the real output of a compiled example, so text and
pictures cannot drift apart. The PNG files are committed, so nobody needs Python
just to read the handouts.
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

import matplotlib

matplotlib.use("Agg")  # draw to files, no window
import matplotlib.pyplot as plt  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
OUT = Path(__file__).resolve().parent

# One small palette used everywhere (colour-blind friendly).
BLUE = "#1f77b4"
ORANGE = "#d55e00"
GREY = "#6b6b6b"

plt.rcParams.update({
    "figure.dpi": 150,
    "savefig.dpi": 150,
    "savefig.bbox": "tight",
    "font.size": 10,
    "axes.spines.top": False,
    "axes.spines.right": False,
    "axes.grid": True,
    "grid.alpha": 0.25,
})


def run(exe: Path) -> str:
    """Run an example program and return what it printed."""
    if not exe.exists():
        sys.exit(f"Missing {exe}. Build the examples first (cmake --build --preset mingw-debug).")
    result = subprocess.run([str(exe)], capture_output=True, text=True, check=True)
    return result.stdout


def logistic_growth(exe_dir: Path) -> None:
    text = run(exe_dir / "logistic_growth.exe")
    gens, pops = [], []
    for line in text.splitlines()[1:]:  # skip the header line
        g, n = line.split()
        gens.append(int(g))
        pops.append(float(n))

    fig, ax = plt.subplots(figsize=(6, 3.4))
    ax.axhline(1000, color=GREY, linestyle="--", linewidth=1)
    ax.text(0.3, 1015, "carrying capacity K = 1000", color=GREY, fontsize=9, va="bottom")
    ax.plot(gens, pops, marker="o", markersize=3.5, color=BLUE)
    ax.set_xlabel("generation t")
    ax.set_ylabel("population N")
    ax.set_title("Logistic growth (r = 0.4, N0 = 10)")
    ax.set_ylim(0, 1100)
    fig.savefig(OUT / "02_logistic_growth.png")
    plt.close(fig)


def logistic_rates(exe_dir: Path) -> None:
    text = run(exe_dir / "logistic_rates.exe")
    rows = []
    for line in text.splitlines():
        m = re.match(r"r = (\S+): generations 200\.\.207:(.*)", line)
        rows.append((float(m.group(1)), [float(v) for v in m.group(2).split()]))

    fig, axes = plt.subplots(len(rows), 1, figsize=(6, 7), sharex=True)
    gens = list(range(200, 208))
    for ax, (r, values) in zip(axes, rows):
        ax.axhline(1000, color=GREY, linestyle="--", linewidth=1)
        ax.plot(gens, values, marker="o", markersize=4, color=ORANGE)
        ax.set_ylim(300, 1400)
        ax.set_ylabel("N")
        ax.text(0.01, 0.82, f"r = {r}", transform=ax.transAxes, fontweight="bold")
    axes[-1].set_xlabel("generation t")
    axes[0].set_title("Same model, different growth rates (generations 200 to 207)")
    fig.tight_layout()
    fig.savefig(OUT / "02_logistic_rates.png")
    plt.close(fig)


def logistic_bifurcation(exe_dir: Path) -> None:
    text = run(exe_dir / "logistic_bifurcation.exe")
    rs, ns = [], []
    for line in text.splitlines()[1:]:
        r, n = line.split(",")
        rs.append(float(r))
        ns.append(float(n))

    fig, ax = plt.subplots(figsize=(7, 4))
    ax.scatter(rs, ns, s=0.3, color=BLUE, alpha=0.35, linewidths=0)
    ax.axvline(2.0, color=GREY, linestyle=":", linewidth=1)
    ax.axvline(2.57, color=GREY, linestyle=":", linewidth=1)
    ax.text(2.02, 80, "cycles begin\n(r = 2)", fontsize=8, color=GREY)
    ax.text(2.59, 80, "chaos\n(r ≈ 2.57)", fontsize=8, color=GREY)
    ax.set_xlabel("growth rate r")
    ax.set_ylabel("population N (last 100 of 600 generations)")
    ax.set_title("Where does the logistic model settle?")
    ax.set_xlim(0.5, 2.9)
    ax.set_ylim(0, 1400)
    fig.savefig(OUT / "02_logistic_bifurcation.png")
    plt.close(fig)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--build-dir", default="build/mingw-debug",
                        help="CMake build directory (default: build/mingw-debug)")
    args = parser.parse_args()
    exe_dir = ROOT / args.build_dir / "examples" / "02-basics"

    logistic_growth(exe_dir)
    logistic_rates(exe_dir)
    logistic_bifurcation(exe_dir)
    print("Figures written to", OUT)


if __name__ == "__main__":
    main()
