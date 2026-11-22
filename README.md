# C++ for Researchers and Engineers

Handouts with fully solved, runnable examples that teach C++ to people who are not programmers but work in biology, chemistry, mathematics or engineering. The handouts assume only basic programming knowledge (variables, `if`/`else`, loops) from another language, and are written for readers who need C++ in their research or engineering work.

- **Solved examples, not exercises.** Every handout works through real problems (population growth, enzyme kinetics, sequence analysis, search, simulation, statistics, classification) with complete code, real output and an explanation.
- **Same problem, new tool.** A few problems return in later handouts, solved with the tool of that handout, so you can see what each new feature makes easier.
- **Idea / Trouble / In practice.** Every language topic is explained in three short blocks: what it is, where it causes problems, and what to do in practice.
- **Works in Qt Creator and VSCode**, and from the command line. Every example is a CMake target.

## Handouts

Each handout is designed for about 60 minutes. *Core* examples fit the session, *Extra* examples are for self-study.

| # | Topic | Status |
|---|---|---|
| 1 | [Hello, C++](handouts/01-hello.md): program anatomy, compile and run, formatted output, reading compiler errors | available |
| 2 | [The basics in a nutshell](handouts/02-basics.md): types, operators, conditions, loops, arrays. Logistic growth, linear search | available |
| 3 | Functions, references, `const` | planned |
| 4 | `vector`, `string`, range-`for` | planned |
| 5 | Files and CSV | planned |
| 6 | `map`, `set`, STL algorithms | planned |
| 7 | Numerics | planned |
| 8 | Randomness, Monte Carlo, statistical tests | planned |
| 9 | Classes and encapsulation | planned |
| 10 | Inheritance, polymorphism, capstone | planned |

Side material: [glossary](notes/glossary.md). More notes (pointers, floating-point pitfalls, templates, advanced object-oriented topics) are planned.

## Quick start

Install a toolchain and an IDE first: see [setup/qtcreator.md](setup/qtcreator.md) or [setup/vscode.md](setup/vscode.md). Both use the compiler (MinGW), CMake and Ninja from the Qt installer.

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

[MIT](LICENSE)
