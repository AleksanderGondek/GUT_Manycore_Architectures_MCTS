rm GUT_Manycore_Architectures_MCTS

source /opt/intel/composer_xe_2013_sp1.3.174/bin/compilervars.sh intel64
source /opt/intel/impi/4.1.3.048/intel64/bin/mpivars.sh
export I_MPI_MIC=on
export I_MPI_FABRICS=shm:tcp

# Enable hydra debug
export I_MPI_HYDRA_DEBUG=1

echo "The following dir has not student01 access"
echo $I_MPI_ROOT

cmake -D CMAKE_C_COMPILER=icc -D CMAKE_CXX_COMPILER=mpiicc ./
make

scp GUT_Manycore_Architectures_MCTS mic0:~
scp GUT_Manycore_Architectures_MCTS mic1:~

