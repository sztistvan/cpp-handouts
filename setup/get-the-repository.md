# Setup: Getting the repository

You need the files of this repository on your computer. **You do not need Git for this.** Choose one of the options.

| Option | Needs | Updates later | Best for |
|---|---|---|---|
| [1. ZIP download](#1-zip-download-nothing-to-install) | nothing | download again | following the course |
| [2. Git](#2-git-clone-and-update) | Git | `git pull` | getting every update easily |
| [3. GitHub Desktop](#3-github-desktop-no-commands) | GitHub Desktop | one click | people who prefer no commands |

---

## 1. ZIP download (nothing to install)

1. Open the repository page on GitHub in your browser.
2. Click the green **Code** button, then **Download ZIP**.
3. Unzip the file into a normal folder close to the drive root, for example `C:\work`. In Windows Explorer: right-click the ZIP → **Extract All...**
4. The folder is named like `<repository>-main`. Open **the folder that contains `CMakeLists.txt`** in Qt Creator or VSCode (see [qtcreator.md](qtcreator.md) or [vscode.md](vscode.md)).

Tips:

- **Extract first.** Do not run or open the project from inside the ZIP preview of Windows Explorer. Programs cannot be built from there.
- **Avoid OneDrive and other synced folders** (Desktop and Documents are often synced). Build folders contain thousands of files that do not need to be synced.
- **Keep the path short.** Very long folder paths can cause errors with some Windows tools.
- **Updates:** a ZIP is a snapshot. When the handouts change, download a new ZIP and unzip it into a new folder. Copy over any files of your own.

---

## 2. Git: clone and update

Git downloads the repository and later fetches only what changed.

**Install Git** (Windows 10 or 11), in PowerShell:

```powershell
winget install --id Git.Git -e
```

Without `winget`, download the installer from <https://git-scm.com/download/win>. The default choices in the installer are fine.

**Close and reopen PowerShell** (so that it finds the new program), and check:

```powershell
git --version
```

**Clone** (download) the repository into the folder where you are:

```powershell
cd C:\work
git clone https://github.com/<account>/<repository>.git
```

(Replace the address with the one on the repository's GitHub page: **Code** button, **HTTPS** tab.)

**Update later**, from inside the repository folder:

```powershell
git pull
```

If `git pull` complains about changes you made yourself, copy your changed files somewhere else first and ask for help. Do not worry about the details for this course.

---

## 3. GitHub Desktop (no commands)

GitHub Desktop is a program with buttons instead of commands.

1. Install it, in PowerShell: `winget install --id GitHub.GitHubDesktop -e`, or download it from <https://desktop.github.com/>.
2. Start it. **File → Clone repository...**, then choose the **URL** tab and paste the address of the repository.
3. Choose a local folder (for example `C:\work`) and click **Clone**.
4. To update later, open the repository in GitHub Desktop and click **Fetch origin**, then **Pull origin**.

Cloning a public repository should not need a GitHub account.

---

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| `git` is not recognized | PowerShell was open during the installation. Close it and open a new window. |
| `winget` is not recognized | Your Windows has no `winget`. Use the installer from git-scm.com instead. |
| Qt Creator or VSCode shows no project | You opened the wrong folder. Open the one that contains `CMakeLists.txt`. |
| "Path too long" errors | Move the repository to a short path such as `C:\work\cpp`. |

*Tested for this page:* the `winget` package IDs `Git.Git` and `GitHub.GitHubDesktop` exist. The installation steps were not run, because they need a computer without Git.
