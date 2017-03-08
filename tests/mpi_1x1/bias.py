import plumed
from mpi4py import MPI

intra = plumed.getComm()
assert isinstance(intra, MPI.Comm)
assert intra.size == 1
assert intra.rank == 0

inter = plumed.getMultiSimComm()
assert isinstance(inter, MPI.Comm)
assert inter.size == 1
assert inter.rank == 0

assert not intra is inter

def bias(coord, force, extra):

    intra = plumed.getComm()
    assert isinstance(intra, MPI.Comm)
    assert intra.size == 1
    assert intra.rank == 0

    inter_comm = plumed.getMultiSimComm()
    assert isinstance(inter, MPI.Comm)
    assert inter.size == 1
    assert inter.rank == 0

    assert not intra is inter

    force[:] = 0.0
    return 0.0
