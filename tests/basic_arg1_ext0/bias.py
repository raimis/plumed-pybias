import plumed
import numpy as np

assert plumed.getNumArgs() == 1
assert plumed.getNumExArgs() == 0

def bias(arg, force, extra):

    assert isinstance(arg, np.ndarray)
    assert isinstance(force, np.ndarray)
    assert isinstance(extra, np.ndarray)

    assert arg.dtype == np.float64
    assert force.dtype == np.float64
    assert extra.dtype == np.float64

    assert arg.shape == (1,)
    assert force.shape == (1,)
    assert extra.shape == (0,)

    assert arg[0] == 42
    assert np.isnan(force[0])

    force[:] = 0.0
    return 0.0
