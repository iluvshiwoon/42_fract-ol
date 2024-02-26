with (import <nixpkgs> {});
  mkShell {
    buildInputs =  [ 
      zlib.dev
      xorg.libXmu.dev
      xorg.libXft.dev
      xorg.libX11.dev
      xorg.libXext.dev
      xorg.libXau.dev
      xorg.xorgproto
      libbsd
      ];
}
