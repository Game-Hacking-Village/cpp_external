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

## setup

```
git clone --recurse-submodules git@github.com:Game-Hacking-Village/cpp_external.git
```

### getting doom

```
cd doom
python download_doom.py doom_game
```

Now gzdoom will be ready to run in doom_game dir with freedoom.

### building

- Make sure the imgui submodule is pulled.

- If building outside of an IDE such as clion (https://www.jetbrains.com/clion/), follow the instruction below to properly install msys2:

Necessary Dependencies that will be installed within the msys2 environment:
```
mingw-w64
cmake
ninja
```

1) Navigate to the parent folder cpp_external

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
    pacman -S vim base-devel gcc cmake ninja python3
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
C:\msys64\usr\bin should be the last path on the Path Environmental Variable

If so the MSYS tooling can now be accessed using PowerShell and is ready to use!!!


### build

```
cmake .
cmake --build .
```

### clean

```
cmake --build . --target clean
```

## overview

dirs

```
./doom - dir with script to download and setup gzdoom + freedoom
./simple_game - a simple game to practice simple memory reading+writing
./external - the main source dir with the external trainer code
```

build targets

```
game - build the simple game
external_simple - build the simple external (write to an arbitrary address in a process)
external_gui_doom - a gui based external trainer for gzdoom
```

