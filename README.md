# FHE Performance Library – Project
The repository contains the initial stages of the development of a fully homomorphic library for testing.
The files are as follows:
- testBITS_ALL.txt and testNumbers.txt are sample data.
- testALL_predetermined.cpp (taking as input testBITS_ALL.txt) and testALL_random.cpp perform a series of simulations to find the average time for one fully homomorphic operation
- gatesData-06-08.txt and gatesData-10-08.txt are the results of the programs above computed on two separate dates
- testENC.py summarizes the gathered data (used for the graph in Appendix A)
- testTempLib.cpp and testTempLib_Bootstrapping.cpp present the current progress towards developing the library (we are yet to begin implementing the actual library with all its dependencies, hence, all supported operations are in those two files)
- testSearching.cpp and testSorting.cpp calculate the expected time of finding the number of occurences of a single element and sorting given data respectively.

# Dependencies
In order to run testALL_predetermined.cpp and testALL_random.cpp, so that evaluation of fully homomorphic programs can be performed with accurate average time and standard deviation, one has to install the TFHE library and use the FFT processor spqlios when compiling.
