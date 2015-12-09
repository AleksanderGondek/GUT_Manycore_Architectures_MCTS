#!/bin/bash

source /opt/intel/composer_xe_2013_sp1.3.174/bin/compilervars.sh intel64
source /opt/intel/impi/4.1.3.048/intel64/bin/mpivars.sh
export I_MPI_MIC=on
export I_MPI_FABRICS=shm:tcp

# Uncomment this line to enable mpi hydra debug
export I_MPI_HYDRA_DEBUG=1

echo "The following should point to i_mpi directory: $I_MPI_ROOT"
