with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "plotting";
    buildInputs = [ python38Packages.matplotlib python38Packages.numpy ];
}
