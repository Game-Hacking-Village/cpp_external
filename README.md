# cpp_external

## TODO

- fix health pointer map (works inconsistent)
- add infinite ammo toggle
    - nop/restore instructions
- cleanup and document code

### if time allows

- fix pointer maps breaking when level changes, recalculating the addresses doesn't work.
    - may need to find different offsets or reverse to find out more
- investigate dockerizing and/or wine so build and testing can be done on linux.

### Building Code

- Make sure the imgui submodule is pulled.

Necessary Dependencies that need to be installed:
```
scoop
msys2
cheat engine
pyton3
clion-ide (optional)
```

1) Navigate back to the parent directory, cpp_external


2) Run PowerShell as Administrator (right click) and change execution policy to allow installation of Scoop
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```
3) Run installation Scoop Package Manager in a new non-Administrative PowerShell terminal:
```powershell
Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
```

4) Install MSYS2 Build Platform 
```powershell
scoop install msys2
```

5) Set up msys2 environment using PowerShell.
```powershell
msys2 -c "pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake"
```

6) In PowerShell and add MSYS to path and replace user with current Windows Username:
    ```powershell
    setx PATH "%PATH%;C:\Users\<user>\scoop\apps\msys2\current\mingw64\bin"
    ```

7) Close and Restart PowerShell and verify that the MSYS path is added to PATH VARIABLE:
    ```powershell
    $Env:Path
    ```
C:\Users\<user>\scoop\apps\msys2\current\mingw64\bin should be the last path of the Path Environmental Variable

If so the MSYS tooling can now be accessed using PowerShell and is ready to use!!!

8) Install CLion IDE in PowerShell (Optional), Python (if necessary) and Cheat Engine
```powershell
scoop update *
scoop bucket add extras
scoop install extras/clion
```

```powershell
scoop install python
```

```powershell
scoop install extras/cheat-engine
```

-or-

Visit website, Download and Install CLion IDE directly from JetBrains using traditional GUI installation:
```
https://www.jetbrains.com/clion/
```

9) Open clion-ide/PowerShell and clone external trainer repo: 
```powershell
git clone --recurse-submodules git@github.com:Game-Hacking-Village/cpp_external.git
```

10) Navigate to imgui directory into cpp_external dir:
```powershell
git clone https://github.com/ocornut/imgui.git
```

11) Download GZDoom
```
cd doom
python download_doom.py doom_game
```
Now GZDoom will be ready to run in doom_game dir with Freedoom.

12) Build External Trainer Executables (if using PowerShell instead of CLion)
```
cmake .
cmake --build .
```

Clean CMake-generated Build

```
cmake --build . --target clean
```

## Overview

### Key Directories

```
./doom - dir with script to download and setup gzdoom + freedoom
./doom/doom-game - dir that contains the binary code for gzdoom including gzdoom.exe
./simple_game - a simple game to practice simple memory reading+writing
./external - the main source dir with the external trainer code
```

### Build targets

```
game - build the simple game
external_simple - build the simple external (write to an arbitrary address in a process)
external_gui_doom - a gui based external trainer for gzdoom
```
### Key Files for Developing the Doom External Trainer 
(*** -> means user needs to edit the file):

#### Files in cpp_external/external:
```
*** external_doom_gui.cpp >>> main key file for building the interface for the GUI of the External Trainer

memory.cpp and memory.h >>> Contains resolve_PointerMap() function for traversing the chains of pointers to find destination address

CMakeLists.txt >>> cmake file for building and compiling the code

process.ccp and process.h >>> Contains functions to get the process handle, process id and base address of the process
```

#### Key files in cpp_external/external/doom:

```
*** doom.ccp and doom.h >>> Creates the DoomProc class and setters and getters need to be built for each target (Pistol Ammo, Health, etc.)
*** offsets.h contains PointerMap structures for each of the targets to hard code the base offset and vector of additional offsets (Pistol, Ammo, Health, etc.)
```



