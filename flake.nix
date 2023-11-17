{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = inputs@{ self, nixpkgs, utils, ... }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      with pkgs; rec {
        defaultPackage = stdenv.mkDerivation {
          pname = "life";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = [
            meson
            ninja
            pkg-config
            gcc
          ];

          buildInputs = [
            raylib
          ];

          installPhase = ''
            mkdir -p $out/bin
            mv life $out/bin
          '';
        };

        defaultApp = utils.lib.mkApp {
          drv = defaultPackage;
        };

        devShell = mkShell {
          inherit (defaultPackage) buildInputs nativeBuildInputs;
        };
      }
    );
}
