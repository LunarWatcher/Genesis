# Genesis

Colony sim, because why not?

## Requirements

### Compile requirements

* A compiler that supports C++20

### Runtime requirements

* GPU with support for OpenGL 4.6
* Operating system: Support guaranteed on Ubuntu 20.04 and derivatives based on 20.04 or later, and roughly maintained on Windows

## Building

To install the python dependencies run
```bash
pip install -r requirements.txt
```

Then run cmake
```bash
cmake -B build && cd build && make -j $(nproc)
```

The binary should be in `build/bin/genesis`. Note that you can also run `make run` to run the binary.

on Windows, you have to run
```
cmake -B build
cd build
cmake --build . --config Release
```
Because MSVC is trash. The path to the binary is `build\bin\genesis.exe`

Similar to Linux, there is a target called `run` that will run the game. However, because I don't use Windows enough to care, the command for doing so is left as an exercise to the reader. However, it's not required, and running the executable directly (as long as the correct working directory is set) will work fine.

Note that to run genesis, the current working directory _has_ to be the build folder. This is because I haven't figured out resource lookup paths, and I don't care enough to beeline it.
