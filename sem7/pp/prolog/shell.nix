{ pkgs ? import <nixpkgs> {} }:
let
    pkgs_old = import (builtins.fetchTarball {
        name = "nixpkgs-racket";
        url = "https://github.com/nixos/nixpkgs/archive/1bf0327ef6d7e0959f3250758b4d33b4066a732b.tar.gz";
        sha256 = "1pz4xaimpb1y8xmqz9c8a2g1nsr77jc7nxi6m8v4ph8q1r3c7pz9";
    }) {};
in
pkgs.mkShell {
    buildInputs = with pkgs; [
        pkgs_old.racket swiProlog
    ];
}
