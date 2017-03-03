import plumed
import numpy as np

assert plumed.getNumArgs() == 1
assert plumed.getNumExArgs() == 2

def bias(arg, force, extra):

    assert plumed.getNumArgs() == 1
    assert plumed.getNumExArgs() == 2

    assert isinstance(arg, np.ndarray)
    assert isinstance(force, np.ndarray)
    assert isinstance(extra, np.ndarray)

    assert arg.dtype == np.float64
    assert force.dtype == np.float64
    assert extra.dtype == np.float64

    assert arg.shape == (1,)
    assert force.shape == (1,)
    assert extra.shape == (2,)

    assert arg[0] == -1
    assert np.isnan(force[0])
    assert extra[0] == 0.001
    assert extra[1] == 42

    force[:] = 0.0
    return 0.0
