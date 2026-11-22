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


def michaelis_menten(exe_dir: Path) -> None:
    text = run(exe_dir / "michaelis_menten.exe")
    s_values, v_values = [], []
    for line in text.splitlines()[1:]:
        parts = line.split()
        if len(parts) != 3:  # the table ends at the first blank line
            break
        s_values.append(float(parts[0]))
        v_values.append(float(parts[1]))

    vmax, km = 100.0, 2.5  # the parameters used in the program
    curve_s = [0.05 * 1.05 ** k for k in range(0, 160)]
    curve_v = [vmax * s / (km + s) for s in curve_s]

    fig, ax = plt.subplots(figsize=(6, 3.6))
    ax.plot(curve_s, curve_v, color=BLUE, linewidth=1.5, label="formula")
    ax.plot(s_values, v_values, "o", color=ORANGE, markersize=5, label="program output")
    ax.axhline(vmax, color=GREY, linestyle="--", linewidth=1)
    ax.text(0.07, vmax + 2, "Vmax = 100", color=GREY, fontsize=9)
    ax.plot([km, km], [0, vmax / 2], color=GREY, linestyle=":", linewidth=1)
    ax.plot([0.05, km], [vmax / 2, vmax / 2], color=GREY, linestyle=":", linewidth=1)
    ax.text(km * 1.08, 6, "Km = 2.5 mM", color=GREY, fontsize=9)
    ax.set_xscale("log")
    ax.set_xlabel("substrate concentration S (mM, log scale)")
    ax.set_ylabel("rate v (umol/min)")
    ax.set_title("Michaelis-Menten kinetics")
    ax.set_ylim(0, 112)
    ax.legend(loc="center right", bbox_to_anchor=(1.0, 0.38), frameon=False)
    fig.savefig(OUT / "03_michaelis_menten.png")
    plt.close(fig)


def trapezoid_error(exe_dir: Path) -> None:
    text = run(exe_dir / "trapezoid.exe")
    ns, errors = [], []
    for line in text.splitlines():
        parts = line.split()
        if len(parts) == 4 and parts[0].isdigit():
            ns.append(int(parts[0]))
            errors.append(float(parts[2]))

    reference = [errors[0] * (ns[0] / n) ** 2 for n in ns]  # a line with slope -2
    fig, ax = plt.subplots(figsize=(6, 3.6))
    ax.loglog(ns, errors, "o-", color=BLUE, label="trapezoid rule (program output)")
    ax.loglog(ns, reference, "--", color=GREY, label="error shrinks like 1/n²")
    ax.set_xlabel("number of strips n")
    ax.set_ylabel("absolute error (mg·h/L)")
    ax.set_title("Doubling n divides the error by 4")
    ax.legend(frameon=False)
    ax.grid(True, which="both", alpha=0.2)
    fig.savefig(OUT / "03_trapezoid_error.png")
    plt.close(fig)


def measurements(exe_dir: Path) -> None:
    lines = run(exe_dir / "statistics.exe").splitlines()
    values = [float(v) for v in lines[0].split(":")[1].split()]
    m = re.search(r"mean = ([\d.]+).*median = ([\d.]+)", lines[1])
    mean_all, median_all = float(m.group(1)), float(m.group(2))

    fig, ax = plt.subplots(figsize=(6, 3.4))
    xs = list(range(1, len(values) + 1))
    colors = [ORANGE if v > 110 else BLUE for v in values]
    ax.scatter(xs, values, c=colors, s=45, zorder=3)
    ax.axhline(mean_all, color=ORANGE, linestyle="--", linewidth=1.3, label=f"mean = {mean_all:.2f}")
    ax.axhline(median_all, color=BLUE, linestyle="-", linewidth=1.3, label=f"median = {median_all:.2f}")
    ax.annotate("outlier", (xs[-1], values[-1]), xytext=(xs[-1] - 1.8, values[-1] - 3.5), color=ORANGE,
                arrowprops={"arrowstyle": "->", "color": ORANGE})
    ax.set_xlabel("replicate")
    ax.set_ylabel("rate (umol/min)")
    ax.set_title("One outlier pulls the mean, not the median")
    ax.set_xticks(xs)
    ax.legend(frameon=False, loc="upper left")
    fig.savefig(OUT / "04_measurements.png")
    plt.close(fig)


def logistic_growth_rate(exe_dir: Path) -> None:
    text = run(exe_dir / "logistic_v3.exe")
    gens, pops, growth = [], [], []
    for line in text.splitlines():
        parts = line.split()
        if len(parts) == 3 and parts[0].isdigit():
            gens.append(int(parts[0]))
            pops.append(float(parts[1]))
            growth.append(None if parts[2] == "-" else float(parts[2]))
    valid = [(g, v) for g, v in zip(gens, growth) if v is not None]
    fastest_gen = max(valid, key=lambda gv: gv[1])[0]

    fig, (top, bottom) = plt.subplots(2, 1, figsize=(6, 5), sharex=True, gridspec_kw={"height_ratios": [3, 2]})
    top.plot(gens, pops, marker="o", markersize=3.5, color=BLUE)
    top.axhline(1000, color=GREY, linestyle="--", linewidth=1)
    top.axhline(500, color=GREY, linestyle=":", linewidth=1)
    top.text(0.3, 515, "K/2 = 500", color=GREY, fontsize=9)
    top.set_ylabel("population N")
    top.set_title("Growth is fastest when the population is about K/2")

    bar_colors = [ORANGE if g == fastest_gen else BLUE for g, _ in valid]
    bottom.bar([g for g, _ in valid], [v for _, v in valid], color=bar_colors)
    bottom.set_xlabel("generation t")
    bottom.set_ylabel("growth to t + 1")
    fig.tight_layout()
    fig.savefig(OUT / "04_logistic_growth_rate.png")
    plt.close(fig)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--build-dir", default="build/mingw-debug",
                        help="CMake build directory (default: build/mingw-debug)")
    args = parser.parse_args()
    examples = ROOT / args.build_dir / "examples"

    logistic_growth(examples / "02-basics")
    logistic_rates(examples / "02-basics")
    logistic_bifurcation(examples / "02-basics")
    michaelis_menten(examples / "03-functions")
    trapezoid_error(examples / "03-functions")
    measurements(examples / "04-vectors")
    logistic_growth_rate(examples / "04-vectors")
    print("Figures written to", OUT)


if __name__ == "__main__":
    main()
