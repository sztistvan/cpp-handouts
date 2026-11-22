# Setup: Qt Creator

Qt Creator is a free IDE with excellent C++ support. For these handouts you only need its editor, its build tools and its debugger. The Qt libraries are not used until the optional GUI part.

Tested on Windows 11 with Qt Online Installer 4.11, MinGW 13.1.0 (g++), CMake 3.30, Ninja 1.12 and gdb 11.2.

## 1. Install

1. Download the **Qt Online Installer** from <https://www.qt.io/download-qt-installer-oss> and sign in with a (free) Qt account.
2. Choose **Custom installation**.
3. Select only what you need:
   - **Qt Creator**
   - Under *Developer and Designer Tools*: **MinGW 13.1.0 64-bit** (the compiler and its debugger), **CMake**, **Ninja**
   - A Qt library version (e.g. *Qt 6.x → MinGW 64-bit*) is only needed for GUI work later. You can add it any time with the *Maintenance Tool*.
4. Skip documentation, examples, sources and other platforms (Android, WebAssembly, ...). They add several GB.
5. When the installer asks whether to **associate common file types** (`.cpp`, `.h`, ...) with Qt Creator, answer **No** if you also use another editor.

The download is large and can be slow on university or company networks. Be patient, and avoid cancelling halfway.

## 2. Open the project

1. Start Qt Creator: **File → Open File or Project...** and select the `CMakeLists.txt` in the **root folder** of this repository.
2. On the *Configure Project* page, tick the kit whose name contains **MinGW 64-bit** (for example *Desktop Qt 6.x.x MinGW 64-bit*, or *Desktop (x86-64, MinGW...)*). Untick other kits. Click **Configure Project**.
3. All examples now appear as targets in the *Projects* panel on the left.

## 3. Build and run

| What | How |
|---|---|
| Choose the program to run | Click the **kit/target selector** (computer icon, bottom left) and choose the target, e.g. `hello_world` |
| Build | Hammer icon, or `Ctrl+B` |
| Build and run | Green **▶** (`Ctrl+R`) |
| Debug | Green **▶ with bug** (`F5`). Click left of a line number to set a breakpoint first |

Program output appears in the **Application Output** pane at the bottom.

### Programs that read input (`std::cin`)

The Application Output pane cannot send keyboard input to your program. For examples that ask for input (such as `greeting`):

1. Open **Projects** (left sidebar) → **Build & Run** → your kit → **Run**.
2. Tick **Run in terminal**.

The program then opens its own console window where you can type. This is the most common surprise in the first session.

## 4. Troubleshooting

| Symptom | Likely cause |
|---|---|
| No MinGW kit offered | The MinGW component was not installed. Re-run the *Maintenance Tool* and add it. |
| "No compiler found" | In **Edit → Preferences → Kits**, check that the kit's compiler is `C:\Qt\Tools\mingw...\bin\g++.exe`. |
| Program closes immediately | You ran an `.exe` by double-clicking. Run from the IDE or a terminal instead. |
| Program waits for input but nothing can be typed | Tick **Run in terminal** (see above). |
