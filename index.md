
**The site is still under construction!**

*PyBias* is a *PLUMED* plug-in with an embeded *Python* interpreter.

## Features

- All system *Python* modules can be used inside
- Built-in module to access information from PLUMED
- No PLUMED re-compilation needed

# Example

```
# plumed.dat

LOAD FILE=libpybias.so

d: DISTANCE ATOMS=1,2

PYBIAS ARG=d
```

```python
# bias.py

import numpy as np

def bias(position, force):

  force[:] = 0.

  return 0.
```

# Installation

If your are lucky (*i.e.* your system already has all dependencies), it is just
a 5-step process:
```bash
git clone https://github.com/raimis/plumed-pybias.git
cd plumed-pybias
cmake .
make
make install
```

## Dependencies

### Run-time
- Plumed
- Python
- Numpy
- MPI4Py

### Building
- g++
- cmake

# Tutorial



