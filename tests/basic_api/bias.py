import plumed
import inspect

assert plumed.__name__ == 'plumed'
#assert plumed.__version__ == '0.0.0'

assert inspect.isbuiltin(plumed.getComm)
assert inspect.isbuiltin(plumed.getKbT)
assert inspect.isbuiltin(plumed.getMultiSimComm)
assert inspect.isbuiltin(plumed.getNumArgs)
assert inspect.isbuiltin(plumed.getNumExArgs)
assert inspect.isbuiltin(plumed.getStep)

def bias(cvs, force, extra):
    force[:] = 0.0
    return 0.0
