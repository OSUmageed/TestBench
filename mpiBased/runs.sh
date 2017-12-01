#!/bin/csh

# use current working directory for input and output
# default is to use the users home directory
#$ -cwd

# name this job
#$ -N Simple-Test

# send stdout and stderror to this file
#$ -o simple.out
#$ -j y

# select queue - if needed 
#$ -q mime4,share,share2,share3,share4

# see where the job is being run
hostname

# print date and time
date

# Sleep for 20 seconds
sleep 5

# print date and time again
./hwloc/utils/lstopo/lstopo

