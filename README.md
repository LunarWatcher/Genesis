# Genesis

Colony sim, because why not?

## Requirements

### Compile requirements

* A compiler that supports C++20
* Python 3 and Conan

### Runtime requirements

* GPU with support for OpenGL 4.0
* Operating system: Theoretically all, support guaranteed on Ubuntu 20.04 and derivatives

## Building

To install the python dependencies run
```bash
pip install -r requirements.txt
```

Then run cmake
```bash
cmake -B build && cd build && make -j $(nproc)
```

The binary should be in `build/bin/genesis`
