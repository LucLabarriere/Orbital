#!/usr/bin/zsh
./configure.sh -G Ninja -DCMAKE_BUILD_TYPE=Release
./build.sh --config=Release
patchelf --set-rpath \$ORIGIN bin/FPSDemo
patchelf --set-rpath \$ORIGIN bin/Demo
mkdir release
cp bin/FPSDemo release/
cp bin/Demo release/
cp -r bin/assets release/
cp build/**/*.so release/
cd release
zip -r orbital_linux_x64_VER.zip *
