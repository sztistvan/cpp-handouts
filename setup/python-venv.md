# Setup: Python for plotting (optional)

The C++ programs print their results as text. For pictures, a small Python script ([`figures/make_figures.py`](../figures/make_figures.py)) runs the compiled programs and plots their output with **matplotlib**. This part is **optional**: every handout already contains its figures as PNG files, and every example is understandable from its text output.

To keep your system Python clean, the packages go into a **virtual environment**: a private folder (`.venv`) with its own Python packages, inside the repository.

Tested on Windows 11 with Python 3.13, pip 25 and matplotlib 3.11 (PowerShell and cmd.exe).

## 1. Install Python

1. Download Python from <https://www.python.org/downloads/> and run the installer.
2. On the first page tick **Add python.exe to PATH**, then install.
3. Open a **new** PowerShell window and check:

```powershell
python --version
```

It should print a version such as `Python 3.13.3`. If Windows instead says "Python was not found; run without arguments to install from the Microsoft Store", Python is not installed or not on `PATH`. Reinstall with the box ticked.

## 2. Create the virtual environment

In PowerShell, from the **root folder of the repository**:

```powershell
python -m venv .venv
```

This takes a few seconds and creates the `.venv` folder. It is listed in `.gitignore`, so it is never uploaded to GitHub.

## 3. Activate it

```powershell
.\.venv\Scripts\Activate.ps1
```

The prompt now starts with `(.venv)`. From here on, `python` and `pip` mean the ones inside `.venv`.

### If PowerShell refuses to activate

On some computers you get this error:

```text
.\.venv\Scripts\Activate.ps1 cannot be loaded because running scripts is disabled on this system.
    + CategoryInfo          : SecurityError: (:) [], PSSecurityException
    + FullyQualifiedErrorId : UnauthorizedAccess
```

PowerShell by default may not run script files. You have three options. Choose one:

1. **Allow local scripts for your own account** (a one-time change, affects only you):

   ```powershell
   Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
   ```

   then run the activation command again.
2. **Use cmd.exe instead.** Type `cmd`, then:

   ```text
   .venv\Scripts\activate.bat
   ```
3. **Skip activation.** Call the environment's Python by its full path every time (see below). This always works.

## 4. Install the packages

With the environment activated:

```powershell
pip install -r requirements.txt
```

`requirements.txt` lists what the figures need (currently matplotlib; pip installs its dependencies, such as numpy, automatically). Check with:

```powershell
python -c "import matplotlib; print(matplotlib.__version__)"
```

## 5. Draw the figures

First build the examples (see your IDE's setup page, or the command line in [vscode.md](vscode.md)). Then, from the repository root:

```powershell
python figures\make_figures.py
```

The script runs the compiled examples from `build\mingw-debug` and writes the PNG files into `figures\`. If your build folder has another name, use `--build-dir`, for example `python figures\make_figures.py --build-dir build\mingw-release`.

### Without activating

The same, with the full path of the environment's Python:

```powershell
.\.venv\Scripts\python.exe -m pip install -r requirements.txt
.\.venv\Scripts\python.exe figures\make_figures.py
```

## 6. Leaving and returning

| What | Command |
|---|---|
| Leave the environment | `deactivate` |
| Return to it later (new window) | `.\.venv\Scripts\Activate.ps1` again. Do not repeat `python -m venv`. |
| Start again from scratch | Delete the `.venv` folder, then repeat steps 2 to 4. |

## 7. Good to know

- **Do not move or rename the folder** that contains `.venv`. A virtual environment remembers its location. If you move the repository, delete `.venv` and create it again (steps 2 to 4).
- **Synced folders:** if the repository lives in OneDrive, Dropbox or a similar synced folder, `.venv` (thousands of small files) will be synced too. This is slow and pointless. Keep the repository in an unsynced folder (for example `C:\work\cpp-handouts`) or pause syncing.
- **In your IDE:** use the terminal, in VSCode ``Ctrl+` `` (Terminal panel), in Qt Creator any PowerShell window. Both build C++ without Python, so Python is never needed to run the examples.
- **Linux and macOS** (not tested for this page): the commands are `python3 -m venv .venv` and `source .venv/bin/activate`, then the same `pip` and `python` commands.

## 8. Troubleshooting

| Symptom | Likely cause |
|---|---|
| "Python was not found; run without arguments to install from the Microsoft Store" | Python is missing, or was installed without the PATH box ticked. |
| "running scripts is disabled on this system" | See the section above (PowerShell execution policy). |
| `ModuleNotFoundError: No module named 'matplotlib'` | The environment is not activated, or step 4 was skipped. The prompt must start with `(.venv)`. |
| `Missing ...exe. Build the examples first` | `make_figures.py` found no compiled programs. Build the examples first. |
| Error after moving the repository | Recreate `.venv` (see "Good to know"). |
