{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  name = "myslstatus";
  nativeBuildInputs = with pkgs; [
    gnumake
    pkg-config
    xorg.libX11
  ];
  shellHook = ''
    echo "dev time!"
  '';
}
