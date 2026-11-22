# Setup: Visual Studio Code

VSCode is a general-purpose editor. Unlike Qt Creator it does not ship with a compiler, so you need a toolchain and two extensions. The simplest way to get the toolchain is the Qt installer (see [qtcreator.md](qtcreator.md), step 1), which installs MinGW, CMake and Ninja. Then VSCode and Qt Creator use the **same compiler**.

Tested on Windows 11 with VSCode, the C/C++ Extension Pack 1.5 and CMake Tools 1.24.

## 1. Install

1. Install **Visual Studio Code** from <https://code.visualstudio.com/>.
2. Install the extensions (Extensions view, `Ctrl+Shift+X`):
   - **C/C++ Extension Pack** (`ms-vscode.cpptools-extension-pack`)
   - **CMake Tools** (`ms-vscode.cmake-tools`)
3. Install the toolchain via the Qt installer as described in [qtcreator.md](qtcreator.md): MinGW 13.1.0 64-bit, CMake and Ninja.

### Optional: add the tools to PATH

The repository's `CMakePresets.json` already points at the Qt tools, so VSCode works without this. You only need `PATH` entries to run `g++`, `cmake` or `gdb` yourself in a terminal. Add these to your user `PATH` (*Start → Edit environment variables for your account → Path → Edit*):

```
C:\Qt\Tools\mingw1310_64\bin
C:\Qt\Tools\CMake_64\bin
C:\Qt\Tools\Ninja
```

Restart VSCode afterwards.

If Qt is installed somewhere else, or has a different MinGW version, edit the paths in `CMakePresets.json` (or put your own version in a `CMakeUserPresets.json`, which is git-ignored).

## 2. Open the project

1. **File → Open Folder...** and select the **root folder** of this repository (the one containing `CMakeLists.txt`).
2. CMake Tools finds `CMakePresets.json` and asks you to select a preset. Choose **MinGW Debug**. You can change it later by clicking the preset name in the blue status bar at the bottom.

## 3. Build and run

All controls are in the **blue status bar** at the bottom of the window:

| What | How |
|---|---|
| Choose the program to run | Click the target name in the status bar (it may show `[all]`) and choose e.g. `hello_world` |
| Build | **Build** button in the status bar, or `F7` |
| Run | **▶** icon in the status bar |
| Debug | **bug** icon next to ▶. Click left of a line number to set a breakpoint first |

Output appears in a terminal panel at the bottom. Because it is a real terminal, programs that read input (`std::cin`) work directly, with no extra setting.

All commands are also available in the Command Palette (`Ctrl+Shift+P`): `CMake: Build`, `CMake: Run Without Debugging`, `CMake: Debug`.

## 4. Using the command line instead

This works the same in every environment, and is a good fallback when an IDE misbehaves. From the repository root:

```powershell
cmake --preset mingw-debug
cmake --build --preset mingw-debug
.\build\mingw-debug\examples\01-hello\hello_world.exe
```

Or compile a single file without CMake:

```powershell
g++ -std=c++17 -Wall -Wextra examples\01-hello\hello_world.cpp -o hello_world
.\hello_world.exe
```

## 5. Troubleshooting

| Symptom | Likely cause |
|---|---|
| No preset offered | You opened a sub-folder. Open the repository root. |
| Status bar shows a Visual Studio kit, not a preset | Run `CMake: Select Configure Preset` and choose **MinGW Debug**. |
| `g++` is "not recognized" in a terminal | The tools are not on `PATH` (see the optional step) or VSCode was not restarted. |
| Red squiggles under `#include <iostream>` | The C/C++ extension has no configuration yet. Run `CMake: Configure` once and reload the window. |
