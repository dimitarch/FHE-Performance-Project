# FHE Performance Library – Project
The repository contains the initial stages of the development of a fully homomorphic library for testing, based on the following paper – https://drive.google.com/open?id=1AW6FxGBuT9Qe_9whGFJJuQwYuIKN0Kh9.
The files are as follows:
- gate.cpp – The library in development for Gate Bootstrapping
- circuit.cpp – The library in development for Circuit Bootstrapping
- testMean.txt – Test data for bootstrapping in TFHE on a Intel Core i7 4700-HQ (2.40 GHz)
# Future Development
Finalization of the development process and starting the wrapping procedure as well as utilizing the algorithm in classical algorithms and arbitrary programs.
# Dependencies
In order to run gate.cpp, so that evaluation of fully homomorphic programs can be performed with accurate average time and standard deviation, one has to install the TFHE library (https://tfhe.github.io/tfhe/) and use the FFT processor spqlios-avx when compiling.
