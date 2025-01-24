# rvz-convert

---

## Building

Use the provided Makefile to build the project. Make sure to pass in multithreading parameters, as Dolphin is a large project with many submodules of its own.
e.g.

```
make -j$(nproc)
sudo make install
```

## Usage

Please use after installing to PATH (`sudo make install`)

`rvz-convert path/to/Game.rvz`

### Dependencies:

Note: Most of these are dolphin dependencies. Still working on cutting out the Qt6 dependencies as it's a total PITA to compile the entirety of dolphin.

- Qt6 Base
- Qt6 SVG
- Qt6 qtbase private libraries
- Working compiler toolchain (build-essential)
- GNU Make
- CMake
- Xi
- LibXRandr
