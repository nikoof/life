{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    utils.url = "github:numtide/flake-utils";

    tgui = {
      url = "github:texus/TGUI";
      flake = false;
    };
  };

  outputs = inputs@{ self, nixpkgs, utils, ... }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            (final: prev: {
              sfml = prev.sfml.override {
                stdenv = prev.llvmPackages_17.libcxxStdenv;
              };
              tgui = with prev;
                llvmPackages_17.libcxxStdenv.mkDerivation {
                  pname = "tgui";
                  version = "1.1.0";
                  src = inputs.tgui;

                  buildInputs = [ xorg.libX11 sfml ];
                  nativeBuildInputs = [ pkg-config cmake ];

                  patches = [
                    ./patches/tgui-pc-fix-paths.patch
                    ./patches/tgui-cmake-fix-paths.patch
                  ];

                  cmakeFlags = [
                    "-DTGUI_CXX_STANDARD=20"
                    "-DTGUI_BACKEND=SFML_GRAPHICS"
                    "-DTGUI_BUILD_GUI_BUILDER=0"
                    "-DTGUI_SHARED_LIBS=1"
                    "-DTGUI_INSTALL_PKGCONFIG_FILES=1"
                  ];
                };
            })
          ];
        };
      in
      with pkgs; rec {
        packages.tgui = tgui;
        defaultPackage = llvmPackages_17.libcxxStdenv.mkDerivation {
          pname = "life";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = [
            pkg-config
            meson
            ninja
          ];

          buildInputs = [
            sfml
            tgui
          ];

          installPhase = ''
            mkdir -p $out/bin
            mv life $out/bin
          '';
        };

        defaultApp = utils.lib.mkApp {
          drv = defaultPackage;
        };

        devShell = mkShell.override { stdenv = llvmPackages_17.libcxxStdenv; } {
          inputsFrom = [ defaultPackage ];
          packages = [
            llvmPackages_17.libcxx
            gdb
            lazygit
            cmake
          ];

          shellHook = ''
            export CLANGD_FLAGS="--query-driver=$(which clang++)"
          '';
        };
      }
    );
}
