# Orbital Engine

Orbital is the basis of a Game engine using C++ and OpenGL (uses Glad, GLFW and GLM as external libraries) supported on Linux and Windows (as well as WSL).

## Features
- Entity Component System
- C++ Scripts with hot compilation (press `<F2>` to reload scripts)
- Basic collision detections (for now, only spheres)
- ImGui Layer for developpment stage

## Requirements
The primary requirement of the project is `CMake > 3.0` and a decent `C++` compiler.
The project uses [`vcpkg`](https://github.com/microsoft/vcpkg) and will clone the repo as a submodule.
The [`invoke`]() python module can be used to configure, build and run the program, although this is not mandatory.

## Build
CMake is configured so that the binaries are exported to the `bin/` folder. This is required for now to allow the hot reloading of C++ scripts
### First steps
```bash
git clone https://github.com/LucLabarriere/Orbital.git
cd Orbital
git submodule init
git submodule update
```
### Build using `invoke`
To install the python dependencies:
Using `pip`:

```bash
cd pyorbital
python -m pip install .
```


Using `conda`:
```bash
cd pyorbital
conda env create -f environment.yaml
conda activate orbital
```

Then, in the main folder:
```bash
inv configure
inv build
inv run
```
The configuration of invoke can be customized using an invoke.yaml file at the root of the project for which the defaults are:
```yaml
build:
  config: Debug
configure:
  build_dir: ./build
  c_compiler: ''
  cxx_compiler: ''
  generator: Ninja
  source_dir: .
  vcpkg_install: true
run:
  executable: FPSDemo
```
## Build without `invoke`
- Configure
```bash
cmake ./ -B build \
-G "Ninja" \
-DCMAKE_TOOLCHAIN_FILE=./vendor/vcpkg/scripts/buildsystems/vcpkg.cmake" \
-DVCPKG_MANIFEST_INSTALL=ON \
-DCMAKE_BUILD_TYPE=DEBUG
```

- Build
```bash
cmake --build build --config=Debug
```

- Run (example of the FPSDemo project)
```bash
# if using a single config generator such as "Ninja"
./bin/FPSDemo
# if using a multi config generator such as "Ninja Multi-Config" or "MSVC"
./bin/Debug/FPSDemo
```

## Acknowledgements
- [https://learnopengl.com](https://learnopengl.com/)
- [The Cherno's youtube channel](https://www.youtube.com/watch?v=JxIZbV_XjAs)
- [Reducible's GJK algorithm video](https://www.youtube.com/watch?v=ajv46BSqcK4)
- [Winterdev's videos on physics engines](https://www.youtube.com/watch?v=-_IspRG548E)
