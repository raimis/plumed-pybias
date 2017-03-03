import plumed
import numpy as np

assert plumed.getNumArgs() == 2
assert plumed.getNumExArgs() == 0

def bias(cvs, force, extra):

    assert plumed.getNumArgs() == 2
    assert plumed.getNumExArgs() == 0

    assert isinstance(cvs, np.ndarray)
    assert isinstance(force, np.ndarray)
    assert isinstance(extra, np.ndarray)

    assert cvs.dtype == np.float64
    assert force.dtype == np.float64
    assert extra.dtype == np.float64

    assert cvs.shape == (2,)
    assert force.shape == (2,)
    assert extra.shape == (0,)

    assert cvs[0] == 42
    assert cvs[1] == -1

    assert np.isnan(force[0])
    assert np.isnan(force[1])

    force[:] = 0.0
    return 0.0
