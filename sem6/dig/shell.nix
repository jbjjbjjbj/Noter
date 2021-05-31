{ pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
    buildInputs = with pkgs; [
        ghdl-llvm zlib
    ];
}
