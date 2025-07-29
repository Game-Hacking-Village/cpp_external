# cpp_external

## setup

```
git clone --recurse-submodules git@github.com:Game-Hacking-Village/cpp_external.git
```

### getting doom

```
cd doom
python download_doom.py <output dir>
```

Now gzdoom will be ready to run in output dir with freedoom.

### building

- Make sure the imgui submodule is pulled.
- *(note: using an ide like clion will make it easiest, but setting up build tools with something like msys2 should work
  no problem as well.)*

### dependencies

```
mingw-w64
cmake
ninja
```

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

