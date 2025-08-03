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

## Setup

```
git clone --recurse-submodules git@github.com:Game-Hacking-Village/cpp_external.git
```

### Getting Doom

```
cd doom
python download_doom.py doom_game
```

Now gzdoom will be ready to run in doom_game dir with freedoom.

### Building

- Make sure the imgui submodule is pulled.

- If building outside of an IDE such as clion (https://www.jetbrains.com/clion/), follow the instruction below to properly install msys2:

Necessary Dependencies that will be installed within the msys2 environment:
```
mingw-w64
cmake
ninja
```

1) Navigate back to the parent directory, cpp_external

    ```powershell
    cd ..
    ```
2) Open PowerShell and run:
    ```powershell
    ./bootstrap.bat 
    ```


3) Follow the MSYS2 installation and keep suggested installation directory of C:\msys64.


4) Open the MSYS UCRT64 terminal as suggested and run:
    ```bash
    pacman -S vim base-devel gcc cmake ninja python3 mingw-w64-x86_64-toolchain mingw-w64-x86_64-windows-default-manifest
    ```
    Once the packages are finished installing, close the MSYS UCRT64 terminal. 


5) In PowerShell and add MSYS to path:
    ```powershell
    setx PATH "%PATH%;C:\msys64\usr\bin"
    ```

6) Close and Restart PowerShell and verify that the MSYS path is added to PATH VARIABLE:
    ```powershell
    $Env:Path
    ```
    C:\msys64\usr\bin should be the last path of the Path Environmental Variable

    If so the MSYS tooling can now be accessed using PowerShell and is ready to use!!!


7) Open new PowerShell as Administer(right click) and Install Chocolately
    ```powershell
    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    ```

8) Install Cheat Engine
    ```
    choco install cheatengine
    ``` 

### Build External Trainer Executables

```
cmake .
cmake --build .
```

### Clean

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



