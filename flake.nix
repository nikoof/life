{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    utils.url = "github:numtide/flake-utils";

    raygui = {
      url = "github:raysan5/raygui";
      flake = false;
    };
  };

  outputs = inputs@{ self, nixpkgs, utils, ... }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        raygui = with pkgs; stdenv.mkDerivation {
          name = "raygui";
          src = inputs.raygui;
          propagatedBuildInputs = [ pkgs.raylib ];
          installPhase = ''
            mkdir -p $out/include
            cp -r src/raygui.h $out/include
            cp -r icons $out/include
            cp -r icons $out/include
          '';
        };
      in
      with pkgs; rec {
        defaultPackage = stdenv.mkDerivation {
          pname = "life";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = [
            pkg-config
            meson
            ninja
          ];

          buildInputs = [
            raylib
            raygui
          ];

          installPhase = ''
            mkdir -p $out/bin
            mv life $out/bin
          '';
        };

        defaultApp = utils.lib.mkApp {
          drv = defaultPackage;
        };

        devShell = pkgs.mkShell {
          inputsFrom = [ defaultPackage ];
          packages = [
            gdb
            clang-tools
          ];
        };
      }
    );
}
