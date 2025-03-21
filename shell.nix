{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  name = "myslstatus";
  nativeBuildInputs = with pkgs; [
    gnumake
    wayland
  ];
  shellHook = ''
    echo "dev time!"
  '';
}
