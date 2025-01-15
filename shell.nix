{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  name = "myslstatus";
  nativeBuildInputs = with pkgs; [
    gnumake
    xorg.libX11
  ];
  shellHook = ''
    echo "dev time!"
  '';
}
