#!/bin/bash
# specify a partition
#SBATCH -p batch
# specify number of nodes
#SBATCH -N 1
# specify number of cores
#SBATCH -n 1
# specify memory pool for all cores in MBs
#SBATCH -- mem 100
# specify the wall clock time limit for the job
#SBATCH -t 00:50:00
# specify the job name
#SBATCH -J smark - job
# specify the filename to be used for writing output.
#SBATCH -o /home-mscluster/mmodupi/hpc/project/serial_results.%N.%j.out
# specify the filename for stderr
#SBATCH -e /home-mscluster/mmodupi/hpc/project/serial_results.%N.%j.err
# The following are shell commands -- which will be executed according to the settings specified above

echo ------------------------------------------------------
echo -n 'Job is running on node ' $SLURM_JOB_NODELIST
echo ------------------------------------------------------
echo SLURM: sbatch is running on $SLURM_SUBMIT_HOST
echo SLURM: job ID is $SLURM_JOB_ID
echo SLURM: submit directory is $SLURM_SUBMIT_DIR
echo SLURM: number of nodes allocated is $SLURM_JOB_NUM_NODES
echo SLURM: number of cores is $SLURM_NTASKS
echo SLURM: job name is $SLURM_JOB_NAME
echo ------------------------------------------------------

cd $SLURM_SUBMIT_DIR
make clean
make 
./program.o
