# FHE Performance Library – Project
The repository contains a fully homomorphic library for testing, based on the following [paper](https://drive.google.com/open?id=1GeCuOPi-xpSxgd2unqutDHMDwn0iWEwG).
The files are as follows:
- include folder - The library itself with implementations for Gate, Circuit and Levelled Bootstrapping
- tests folder – Tests to prove the validity of the implementation of the fundamental binary and arithmetic operations
- simulations folder - Analysis of classical algorithms implemented with the library
- testMean.txt – Test data for bootstrapping in TFHE on a Intel Core i7 4700-HQ (2.40 GHz)
# Future Development
We plan to examine HELib and extend the number of analysed algorithms.
# Dependencies
In order to run the library, so that evaluation of fully homomorphic programs can be performed with accurate average time and standard deviation, one has to install the TFHE library (https://tfhe.github.io/tfhe/) and use the FFT processor spqlios-avx when compiling.
