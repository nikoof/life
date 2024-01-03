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
You need a compiler with good support for C++23.

**Note: I am compiling with clang++ 17.0.6 and libc++/libcxx. It is also possible to compile with g++ >=13 and libstdc++, however this breaks clangd code completion ([because of incomplete support for concepts in clang](https://github.com/clangd/clangd/discussions/1876)).**
The way I made completion work with clangd is very hacky, but I am not sure how I can make it work in a less hacky way since clangd seems to literally ignore `-stdlib=libc++`.

```shell
git clone https://github.com/nikoof/life
meson setup --buildtype release build
meson compile -C build
./build/life
```
