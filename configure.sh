git submodule init
git submodule update

cmake . -B./build/ \
    -DCMAKE_CXX_COMPILER=clang++-15 \
    -DCMAKE_C_COMPILER=clang-15 \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -G "Ninja Multi-Config" \
	-DCMAKE_TOOLCHAIN_FILE=/opt/lucla/vcpkg/scripts/buildsystems/vcpkg.cmake \
    $@
