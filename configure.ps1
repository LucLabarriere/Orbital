git submodule init
git submodule update

cmake . -B./build/ `
    -DCMAKE_CXX_COMPILER="clang++.exe" `
    -DCMAKE_C_COMPILER="clang.exe" `
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON `
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON `
    -G "Ninja" `
	-DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT"/scripts/buildsystems/vcpkg.cmake `
	-DVCPKG_MANIFEST_INSTALL=ON
