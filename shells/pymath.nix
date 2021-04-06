{ pkgs ? import <nixpkgs> {}, pythonPackages ? pkgs.python38Packages }:

pkgs.mkShell {
    buildInputs = with pythonPackages; [
        jupyterlab
        jupyter-c-kernel
        numpy
        scipy
        matplotlib
    ];

    shellHook = ''
        echo Lets do some python
        alias start="jupyter lab"
        '';
}
