{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  name = "myslstatus";
  nativeBuildInputs = with pkgs; [
    gnumake
    xorg.libX11
    wayland
  ];
  shellHook = ''
    echo "dev time!"
  '';
}
