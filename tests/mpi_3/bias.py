import plumed
from mpi4py import MPI

intra = plumed.getComm()
assert isinstance(intra, MPI.Comm)
assert intra.size == 3
assert MPI.COMM_WORLD.allgather(intra.rank) == [0, 1, 2]

inter = plumed.getMultiSimComm()
assert isinstance(inter, MPI.Comm)
assert inter.size == 1
assert inter.rank == 0

assert not intra is inter

def bias(coord, force, extra):

    intra = plumed.getComm()
    assert isinstance(intra, MPI.Comm)
    assert intra.size == 3
    assert MPI.COMM_WORLD.allgather(intra.rank) == [0, 1, 2]

    inter = plumed.getMultiSimComm()
    assert isinstance(inter, MPI.Comm)
    assert inter.size == 1
    assert inter.rank == 0

    assert not intra is inter

    force[:] = 0.0
    return 0.0
