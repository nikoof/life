# life

![License](https://img.shields.io/github/license/nikoof/life)

A simple implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) in C++ using [SFML](https://www.sfml-dev.org/) and [TGUI](https://tgui.eu/). Currently a work-in-progress.

Planned features:

- Neater UI/UX
- Support for importing patterns in various formats ([plaintext](https://conwaylife.com/wiki/Plaintext), [RLE](https://conwaylife.com/wiki/Run_Length_Encoded), [Life 1.06](https://conwaylife.com/wiki/Life_1.06) etc.)

# Building with Nix

```shell
# build
nix build github:nikoof/life
./result/bin/life

# ...or run it directly
nix run github:nikoof/life
```

# Building manually

Alternatively, you can clone the repository and build manually. You need to install [SFML](https://www.sfml-dev.org/) and [TGUI](https://tgui.eu/) and make the libraries available to your compiler.

**Note: You need a compiler with support for C++23. I've only built this with `g++ (GCC) 12.3.0`.**

```shell
git clone https://github.com/nikoof/life
meson setup --buildtype release build
meson compile -C build
./build/life
```
