#!/bin/csh

#$ -cwd
#$ -N gpuImprove
#$ -q mime4
#$ -pe mpich2 32-40
#$ -j y
#$ -R y
#$ -l h='compute-e-[1-2]

hostname

ls $TMPDIR

echo $NSLOTS

which cuda

sleep 1

echo "mpirun -n $NSLOTS -machinefile $TMPDIR/machines ./bin/newgpuD"

$MPIPATH/bin/mpirun -np $NSLOTS -machinefile $TMPDIR/machines ./bin/newgpuD

