BINARIES=./mpi-load-balance

all:${BINARIES}

# for MVAPICH2
# %:%.c
# 	mcc --ompss-2  -I/apps/MVAPICH2/2.3rc1/INTEL/include -L/apps/MVAPICH2/2.3rc1/INTEL/lib -Wl,-rpath -Wl,/apps/MVAPICH2/2.3rc1/INTEL/lib -Wl,--enable-new-dtags -lmp -c $<
# 	mcc --ompss-2  -I/apps/MVAPICH2/2.3rc1/INTEL/include -L/apps/MVAPICH2/2.3rc1/INTEL/lib -Wl,-rpath -Wl,/apps/MVAPICH2/2.3rc1/INTEL/lib -Wl,--enable-new-dtags -lmpi $@.o -o $@

%:%.cpp ../build/libmicropp.a
	mcxx --ompss-2 -I/apps/INTEL/2018.1.038/impi/2018.1.163/intel64/include -L/apps/INTEL/2018.1.038/impi/2018.1.163/intel64/lib/release_mt -L/apps/INTEL/2018.1.038/impi/2018.1.163/intel64/lib -Xlinker --enable-new-dtags -Xlinker -rpath -Xlinker /apps/INTEL/2018.1.038/impi/2018.1.163/intel64/lib/release_mt -Xlinker -rpath -Xlinker /apps/INTEL/2018.1.038/impi/2018.1.163/intel64/lib -Xlinker -rpath -Xlinker /opt/intel/mpi-rt/2107.0.0/intel64/lib/release_mt -Xlinker -rpath -Xlinker /opt/intel/mpi-rt/2017.0.0/intel64/lib -lmpifort -lmpi -lmpigi -ldl -lrt -lpthread  -I/home/bsc28/bsc28600/scratch/work/20200720_correctmodules/MicroPP/load_balance_micropp/Micropp/include -I/home/bsc28/bsc28600/scratch/work/20200720_correctmodules/MicroPP/load_balance_micropp/Micropp/build --ompss-2 -k -DNANOS6 -g --ompss-2 -k -DNANOS6 -std=gnu++11 -o $<.o -c $<
	mcxx --ompss-2 -I/apps/INTEL/2018.1.038/impi/2018.1.163/intel64/include -L/apps/INTEL/2018.1.038/impi/2018.1.163/intel64/lib/release_mt -L/apps/INTEL/2018.1.038/impi/2018.1.163/intel64/lib -Xlinker --enable-new-dtags -Xlinker -rpath -Xlinker /apps/INTEL/2018.1.038/impi/2018.1.163/intel64/lib/release_mt -Xlinker -rpath -Xlinker /apps/INTEL/2018.1.038/impi/2018.1.163/intel64/lib -Xlinker -rpath -Xlinker /opt/intel/mpi-rt/2107.0.0/intel64/lib/release_mt -Xlinker -rpath -Xlinker /opt/intel/mpi-rt/2017.0.0/intel64/lib -lmpifort -lmpi -lmpigi -ldl -lrt -lpthread  -DNANOS6 -g -rdynamic $<.o -o $@ ../build/libmicropp.a -lgfortran -lquadmath 

	# Works without MPI: mcxx -I/home/bsc28/bsc28600/scratch/work/20200720_correctmodules/MicroPP/load_balance_micropp/Micropp/include -I/home/bsc28/bsc28600/scratch/work/20200720_correctmodules/MicroPP/load_balance_micropp/Micropp/build --ompss-2 -k -DNANOS6 -g --ompss-2 -k -DNANOS6 -std=gnu++11 -o $<.o -c $<
	# mcxx --ompss-2 -k -DNANOS6 -g --ompss-2 -rdynamic $<.o -o $@ ../build/libmicropp.a -lgfortran -lquadmath


clean:
	rm -rf ${BINARIES}
