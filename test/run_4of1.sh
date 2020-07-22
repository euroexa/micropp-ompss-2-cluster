#! /bin/sh

# Assuming:
#
#  srun --nodes=4 --cpus-per-task=24 --ntasks=8 --time=01:00:00 --pty bash -I

# echo export NANOS6_COMMUNICATION=mpi-2sided
#echo "0 0 1 1 2 2 3 3" > .map
#export NANOS6_CLUSTER_SPLIT="0,3;2,5;4,7;6,1"

# srun --nodes=4 --cpus-per-task=24 --time=01:00:00 --pty bash -I
echo "0 1 2 3" > .map
export NANOS6_CLUSTER_SPLIT="0;1;2;3"
MV2_ENABLE_AFFINITY=0 mpirun -np 4 $*
