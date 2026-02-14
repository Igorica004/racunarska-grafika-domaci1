{
  description = "C++ development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    clion-flake.url = "path:/home/Igor/Programiranje/flakes/clion";
  };
  outputs = { self, nixpkgs, clion-flake }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in {
    devShells.${system}.default = pkgs.mkShell {
      packages = [
        pkgs.gcc
        pkgs.cmake
        pkgs.gdb
        pkgs.clang-tools
        pkgs.glfw
        clion-flake.clion
        pkgs.glslls
      ];
    };
  };
}
