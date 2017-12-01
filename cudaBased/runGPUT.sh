#!/bin/csh

#$ -cwd
#$ -N gpuDetector
#$ -q mime4
#$ -pe mpich3i 40
#$ -R y
#$ -j y
#$ -l h='compute-e-[1-2]

sleep 10

echo $TMPDIR

echo $NSLOTS

echo "mpirun -n $NSLOTS -machinefile $TMPDIR/machines ./bin/gpuD"

mpirun -n $NSLOTS -machinefile $TMPDIR/machines ./bin/gpuD

