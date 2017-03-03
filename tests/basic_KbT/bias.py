import plumed

assert plumed.getKbT() == 0

def bias(cvs, force, extra):

    assert plumed.getKbT() == 0

    force[:] = 0.0
    return 0.0
