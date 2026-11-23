# C++ for Researchers and Engineers

Handouts with fully solved, runnable examples that teach C++ to people who are not programmers but work in biology, chemistry, mathematics or engineering. The handouts assume only basic programming knowledge (variables, `if`/`else`, loops) from another language, and are written for readers who need C++ in their research or engineering work.

- **Solved examples, not exercises.** Every handout works through real problems (population growth, enzyme kinetics, sequence analysis, search, simulation, statistics, classification) with complete code, real output and an explanation.
- **Same problem, new tool.** A few problems return in later handouts, solved with the tool of that handout, so you can see what each new feature makes easier.
- **Idea / Trouble / In practice.** Every language topic is explained in three short blocks: what it is, where it causes problems, and what to do in practice.
- **Works in Qt Creator and VSCode**, and from the command line. Every example is a CMake target.

## Handouts

Each handout is designed for about 60 minutes. *Core* examples fit the session, *Extra* examples are for self-study.

The middle column lists the **C++ concepts** a handout teaches. The last column lists the **examples** (applications) that use them.

| # | Handout | C++ concepts | Examples | Status |
|---|---|---|---|---|
| 1 | [Hello, C++](handouts/01-hello.md) | program structure, `#include`, namespace `std`, `main` and its return value, streams (`cout`, `cin`, `cerr`), output formatting, compile and link, reading compiler errors | element table, molar mass of water, reading a name and numbers, table of squares and roots | available |
| 2 | [The basics](handouts/02-basics.md) | types and variables, initialisation, `const`, operators, integer division, conditions, loops, fixed-size arrays | logistic growth (with chaos), linear search, Fibonacci rabbits, half-life, Collatz | available |
| 3 | [Functions](handouts/03-functions.md) | declaration and definition, parameters and return values, pass by value / reference / `const` reference, default arguments, overloading, scope | Michaelis-Menten kinetics, trapezoid integration, binary search, area under a concentration curve, pH, Newton's method, ideal gas law | available |
| 4 | [Vectors and strings](handouts/04-vectors.md) | `std::vector`, `std::string`, range-`for`, size and indexing, `at()`, vectors in functions | statistics of measurements (mean, SD, median), GC content, simulation history, maze as a table, counting TP/TN/FP/FN and accuracy, reverse complement, restriction sites, moving average, histogram, correlation | available |
| 5 | [Files](handouts/05-files.md) | file streams (`ifstream`, `ofstream`), reading line by line, splitting text, converting text to numbers, checking stream state | messy CSV measurements, simulation output for plotting, maze from file, classifier scores with precision / recall / F1, FASTA reader, log parser, parameter file | available |
| 6 | [Containers and algorithms](handouts/06-containers.md) | `struct` as a record, `std::map`, `std::set`, `std::queue`, `std::priority_queue`, `std::sort` and other algorithms, lambda basics | k-mer counting, breadth-first search in a maze, Dijkstra on a terrain, word and codon frequencies, translating DNA, sorting records, shortest path in a metabolic network, multi-class precision / recall / F1 | available |
| 7 | Numerical methods in C++ | floating-point behavior in practice, `<cmath>`, passing a function to a function (lambda, `std::function`) | float pitfalls, Euler vs. RK4 for a decay chain, bisection and Newton root finding, Lotka-Volterra and SIR models, ROC curve and AUC, gradient descent | planned |
| 8 | Random numbers | `<random>` (engines, distributions, seeding, reproducibility), repeated experiments in loops | estimating π, random walk and diffusion, bootstrap confidence interval, permutation test, t-test and chi-square test, Gillespie simulation, train/test split | planned |
| 9 | Classes | `class` vs. `struct`, encapsulation (`private` / `public`), constructors, member functions, `const` member functions, operator overloading | molecule and molar mass, particles in a box, `Model` class, `Grid` and `Node`, `ConfusionMatrix`, `Vec3` | planned |
| 10 | Inheritance and polymorphism | inheritance, `virtual` functions and abstract classes, composition vs. inheritance, smart pointers (just enough), templates (a glimpse) | one ODE solver for several models, A* search with a choice of heuristic, `Classifier` interface, small neural network, capstone (heat diffusion or Game of Life) | planned |

Side material: [glossary](notes/glossary.md). More notes (pointers, floating-point pitfalls, templates, advanced object-oriented topics) are planned.

## Quick start

Get the files first: see [setup/get-the-repository.md](setup/get-the-repository.md). A ZIP download is enough, Git is not required.

Then install a toolchain and an IDE: see [setup/qtcreator.md](setup/qtcreator.md) or [setup/vscode.md](setup/vscode.md). Both use the compiler (MinGW), CMake and Ninja from the Qt installer.

Then, from the repository root:

```powershell
cmake --preset mingw-debug
cmake --build --preset mingw-debug
.\build\mingw-debug\examples\01-hello\hello_world.exe
```

In **Qt Creator** open the root `CMakeLists.txt`. In **VSCode** open the root folder and select the *MinGW Debug* preset. Details are in the setup pages. The presets assume the default Qt install location (`C:\Qt\Tools`). Edit `CMakePresets.json` if yours differs.

### Optional: figures with Python

The handouts contain their figures as PNG files. To redraw them from the real program output, see [setup/python-venv.md](setup/python-venv.md) (a virtual environment with matplotlib).

## Repository layout

```
handouts/    the handouts (Markdown)
notes/       short side documents (glossary, ...)
setup/       IDE and Python setup pages
examples/    one folder per handout, one CMake target per program
figures/     generated figures and the script that draws them
data/        small input files used by examples (added when needed)
```

## Reading the handouts

GitHub renders the Markdown, the formulas and the Mermaid diagrams directly. In VSCode the Markdown preview (`Ctrl+Shift+V`) shows formulas. Mermaid diagrams need a Mermaid preview extension there.

## Tested with

Windows 11, g++ 13.1 (MinGW-Builds, via Qt installer), CMake 3.30, Ninja 1.12, Qt Creator, and VSCode with the C/C++ and CMake Tools extensions. The examples of handouts 1 and 2 were also compiled with MSVC (Visual Studio 2022) and give identical output. Linux and macOS have not been tested yet.

## License

Released under the [MIT License](LICENSE). Copyright (c) 2026 István Szatmári.

These handouts are personal teaching material. You are welcome to use, adapt and share them, including in your own courses.
