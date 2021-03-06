# Installation

The Ocean Tensor Package has a number of prerequisites:

1. CMake version 3.8 or higher (includes built-in support for CUDA)
2. Python (required for compilation of Solid), header files are required when compiling the Python interface
3. A compiler that is supported by CMake and NVCC (when GPU support is required)
4. The BLAS or CBLAS library (optional)

The compilation of the package proceeds in three simple steps:

1. From the top Ocean level, call `cmake .`
2. When successfully completed, call `make`
3. Update the environment variables (see below)

***NOTE***: Currently there is no support for `make install`. Parallel compilation of the files using the `-j` option to `make` is not supported and causes dependency problems when used. These issues are scheduled for future improvements (see [here](future_work.md#CMakeImprovements) for more details).

Running `cmake` in the first step will gather platform information and determine the compiler setting. When support for GPU is desired it is important to run `cmake` on a machine that has the GPU card(s) installed, to ensure that compilation is done for that particular card. If Cuda is detected but now GPU devices are found the package will be compiled for all compute capabilities in the list (30, 35, 50, 60, 70) that are supported by the provided version of `nvcc`. When the device compute capability does not match that of the compiled version, loading Ocean may take longer due to on-the-fly Cuda compilation.

The `cmake` command in the first step will output paths to add to the library search path (such as `LD_LIBRARY_PATH` in Linux), as well as paths to add to the Python search path (`PYTHONPATH`).

Ocean has been successfully compiled and tested on Linux (RedHat) for Intel and Power, as well as on MacOS. Compilation could not be tested on all platforms and settings, so please let us know if you have any problems compiling Ocean on your system. Installation has not yet been tested on Windows. On MacOS the choice of compiler version is important because `nvcc` is not compatible with all versions of `clang` (see known issues and troubleshooting section below).


## CMake configuration

It is possible to build Ocean from a directory other than the base directory. This can be done, for example by typing from the base directory:
```
mkdir build
cd build
cmake ..
make
```
Doing so causes most of the temporary build files to be generated in the `build` directory. However, in the current release the compiled libraries, automatically generated header files, and the Python build files will still be output in appropriate subdirectories of the Ocean directory.

### Python version

To specify a specific version of Python, use the following option prior to the compile path (`.`):
```
cmake -DPYTHON_EXECUTABLE=<Path to Python or Python 3> .
```
If needed, it is possible to run `cmake` and `make` for different Python versions from the `ocean/interfaces/python` directory to provide support for each of the different versions.


### CUDA version

To specify a specific version of `nvcc`, either update the `PATH` environment variable such that the path containing the desired version of `nvcc` precedes all other paths that contain `nvcc` (that is, `which nvcc` gives the desired version). Or run `cmake` using the `CMAKE_FIND_ROOT_PATH` option, for example:

```
cmake -DCMAKE_FIND_ROOT_PATH=/opt/share/cuda-9.0/x86_64/ .
```

Other documented solutions including:
```
export CUDA_BIN_PATH=/opt/share/cuda-9.0/x86_64/bin/
cmake -DCMAKE_CUDA_COMPILER=/opt/share/cuda-9.0/x86_64/bin/nvcc .
cmake -DCUDA_TOOLKIT_ROOT_DIR=/opt/share/cuda-9.0/x86_64/ .
```
do not seem to work because the cmake scripts used to detect CUDA are different from those that detect the compiler, leading to inconsistent values:
```
-- Found CUDA: /opt/share/cuda-9.0/x86_64 (found version "9.0") 
...
-- Check for working CUDA compiler: /opt/share/cuda-7.5/bin/nvcc
-- Check for working CUDA compiler: /opt/share/cuda-7.5/bin/nvcc -- works
```

### Blas and CBlas

The Ocean package includes a CMake script for detecting CBLAS and BLAS (in that order) to ensure that a valid library is found. If no compatible version is found, an internal fallback implementation is provided for the functions needed. In case the desired version of CBlas is not found (for example `/usr/lib64/atlas/libtatlas.so` with header file `/usr/include/cblas.h`), please provide the following option to `cmake`:

```
cmake -DCBlasInfo="/usr/lib64/atlas/libtatlas.so;/usr/include/cblas.h"
```

The library file and header file must be separated by a semicolon and the entire string must be in quotes. If a standard CBLas distribution cannot be found, please let us know so we can add it to the search script.


## Tested configurations

### Linux

Red Had Enterprise Linux version 7.4 on Power8 and Intel, with GCC 4.8.5. Cuda versions 7.5, 8.0, 9.0, and 9.1. Python versions 2.7.5 and 3.5.2.


### MacOS

The following configurations were tested on MacOS High Sierra, version 10.13.4, using CMake version 3.11. The machine does not have any GPU devices installed, so we could only test compilation using Cuda. In the table below "n.s." means that nvcc does not support the given version of clang.

| XCode version  | Clang | | No CUDA |  7.5  | 8.0 GA1 | 8.0 GA2 | 9.0   | 9.1   | 9.2   |
| -------------- | ----- |-| ------- | ----- | ------- | ------- | ----- | ----- | ----- |
| 7.1.1 (*)      | 7.0.0 | | OK      | OK    | OK      | OK      | OK    | OK    | OK    |
| 7.2 (*)        | 7.0.2 | | OK      | OK    | OK      | OK      | OK    | OK    | OK    |
| 7.3.1 (*)      | 7.3.0 | | OK      | OK    | OK      | OK      | OK    | OK    | OK    |
| 8.1            | 8.0.0 | | OK      | n.s.  | OK      | OK      | OK    | OK    | OK    |
| 8.2.1          | 8.0.0 | | OK      | n.s.  | OK      | OK      | OK    | OK    | OK    |
| 8.3.3          | 8.1.0 | | OK      | n.s.  | n.s.    | n.s.    | OK    | OK    | OK    |
| 9.1            | 9.0.0 | | OK      | n.s.  | n.s.    | n.s.    | n.s.  | OK    | OK    |
| 9.2            | 9.0.0 | | OK      | n.s.  | n.s.    | n.s.    | n.s.  | OK    | OK    |
| 9.3.1          | 9.1.0 | | OK      | n.s.  | n.s.    | n.s.    | n.s.  | n.s.  | n.s.  |
| 9.4            | 9.1.0 | | OK      | n.s.  | n.s.    | n.s.    | n.s.  | n.s.  | n.s.  |
| 9.4.1          | 9.1.0 | | OK      | n.s.  | n.s.    | n.s.    | n.s.  | n.s.  | n.s.  |

(*) Compilation warnings: `ld: warning: bad symbol action: $ld$weak$os10.12$_utimensat in dylib ...`



## Known issues and troubleshooting

If compilation fails because of some intermediate CMake files remain it may be best to type
```
make -f Makefile.clean
make -f Makefile.clean lib
```
from the Ocean base directory prior to running `cmake` again. These commands delete all intermediate CMake files as well as the compiled libraries and automatically generated header files.


### MacOS

* `clang` does not support OpenMP, and multi-threading on the CPU is therefore currently disabled on MacOS.
* `nvcc` is not compatible with `gcc` and only works with select version of `clang`. If needed, install a different version of XCode and move it to the `Applications` folder with version name appended (for example `XCode-8.3.3`). To activate a particular version type
```
sudo xcode-select -switch /Applications/Xcode-8.3.3.app/Contents/Developer
```
To switch back to the default version type
```
sudo xcode-select -switch /Applications/Xcode.app/Contents/Developer
```

Strange errors about header files, such as
```
/usr/include/string.h(170): error: extra text after expected end of number
```
may indicate the the command-line tools do not match the XCode version. In this case activate the desired version of XCode, and install the corresponding command-line tools, which can be found along with XCode on the Apple developer website.


It may also be necessary to install the corresponding version of the C

### Dependency tree

| ID | Path                             | Dependencies |
| -- | -------------------------------- | ------------ |
|  1 | `solid/src/base`                 |              |
|  2 | `solid/src/core/cpu`             | 1            |
|  3 | `solid/src/core/gpu`             | 1            |
|  4 | `src/ocean/base`                 |              |
|  5 | `src/ocean/external/ocean-solid` | 4            |
|  6 | `src/ocean/external/ocean-blas`  |              |
|  7 | `src/ocean/core/cpu`             | 2, 4, 5, 6   |
|  8 | `src/ocean/core/gpu`             | 3, 4, 5      |
|  9 | `interfaces/python/pyOcean/cpu`  | 7            |
| 10 | `interfaces/python/pyOcean/gpu`  | 8            |
| 11 | `interfaces/python/pyOceanNumpy` | 7            |
