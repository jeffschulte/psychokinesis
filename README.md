psychokinesis
=============

we will use this to get ... ART!

Setting up build environment
----------------------------
Mac:

`brew install sdl2`
`brew install SDL2_image`
`brew install sdl2_mixer --with-libvorbis`

### Installing liquidfun:

`brew install cmake`

Clone https://github.com/google/liquidfun somewhere

```shell
cd liquidfun/liquidfun/Box2D
cmake .
make
sudo make install
cp -r Box2D /usr/local/include/
cd Box2D/Release
cp libliquidfun.a /usr/local/lib/```

Building
--------

Compile with `make`
