#!/bin/bash

#Input:
# -M: mass of the neutriono in eV
# -D: distancte to SN in Mpc
# -N: number of events detected per SN on average (TODO)
# --nfits: number of fits to make for each configuration
# --noiseb: noise is approximated as an exponential function - this is the constant of the exponential

echo "Starting"

for a in 0.001 0.01 0.1 0.5 0.7 1.0 1.5 2.0
do 
   echo $a
   for b in 0.01 0.1 0.5 1.0 1.3
   do
      echo $b
      python calc_minimal_likelihood_combined.py \
      -N 10.0 \
      -M $b \
      -D 5.0 \
      --nfits 2 \
      --noiseb $a \

   done

done

exit 0
