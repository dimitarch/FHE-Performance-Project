#ifndef HOMOMORPHIC_ENCRYPTION_EVALUATION_H
#define HOMOMORPHIC_ENCRYPTION_EVALUATION_H

#include <iostream>
#include <cmath>
#include <vector>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>

namespace homomorphicEvaluation {
    //generate a keyset
    const int minimum_lambda = 110;
    const TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);
    //generate a random key
    TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);

    class Computation {
    public:
        long long bootCount, encCount;
        Computation() { bootCount = 0; encCount = 0; }
        void Bootstrap();
        void Encrypt();
        long long GetBootstrapping();
        long long GetEncryptions();
    };

    class RealGateBootstrappedBit {
    public:
        LweSample* value = new_gate_bootstrapping_ciphertext(params);

        RealGateBootstrappedBit() { bootsSymEncrypt(value, 0, key); }
        RealGateBootstrappedBit(bool n) { bootsSymEncrypt(value, n, key); }
        void operator=(const RealGateBootstrappedBit& a) const;
        RealGateBootstrappedBit operator&(const RealGateBootstrappedBit& a) const;
        RealGateBootstrappedBit operator^(const RealGateBootstrappedBit& a) const;
        RealGateBootstrappedBit operator|(const RealGateBootstrappedBit& a) const;
        RealGateBootstrappedBit operator!() const;
    };

    class SimulatedGateBootstrappedBit {
    public:
        bool value;
        Computation* routine;
        SimulatedGateBootstrappedBit() { value = 0; }
        SimulatedGateBootstrappedBit(bool n) { value = n; }
        void Initialize(Computation& newComputation);
        void Initialize(bool n, Computation& newComputation);
        SimulatedGateBootstrappedBit operator&(const SimulatedGateBootstrappedBit& a) const;
        SimulatedGateBootstrappedBit operator^(const SimulatedGateBootstrappedBit& a) const;
        SimulatedGateBootstrappedBit operator|(const SimulatedGateBootstrappedBit& a) const;
        SimulatedGateBootstrappedBit operator!() const;
    };

    class SimulatedCircuitBootstrappedBit {
    public:
        bool value;
        long long level;
        Computation* routine;
        SimulatedCircuitBootstrappedBit() { value = 0; level = 0; }
        SimulatedCircuitBootstrappedBit(bool n) { value = n; level = 0; }
        void Initialize(Computation& newComputation);
        void Initialize(bool n, Computation& newComputation);
        SimulatedCircuitBootstrappedBit operator&(const SimulatedCircuitBootstrappedBit& a) const;
        SimulatedCircuitBootstrappedBit operator^(const SimulatedCircuitBootstrappedBit& a) const;
        SimulatedCircuitBootstrappedBit operator|(const SimulatedCircuitBootstrappedBit& a) const;
        SimulatedCircuitBootstrappedBit operator!() const;
    };

    class SimulatedLevelledBit {
    public:
        bool value;
        long long level;
        long long depth;
        Computation* routine;
        SimulatedLevelledBit() { value = 0; level = 0; }
        SimulatedLevelledBit(bool n) { value = n; level = 0; }
        void Initialize(long long newDepth, Computation& newComputation);
        void Initialize(bool n, long long newDepth, Computation& newComputation);
        SimulatedLevelledBit operator&(const SimulatedLevelledBit& a) const;
        SimulatedLevelledBit operator^(const SimulatedLevelledBit& a) const;
        SimulatedLevelledBit operator|(const SimulatedLevelledBit& a) const;
        SimulatedLevelledBit operator!() const;
    };

    template <class BoolType> class GenericInt32 {
    public:
        std::vector<BoolType> encValue;
        GenericInt32();
        GenericInt32(int n);
        void Initialize(Computation& newComputation);
        void Initialize(int n, Computation& newComputation);
        void Initialize(int n, int newDepth, Computation& newComputation);
        BoolType operator==(const GenericInt32<BoolType>& a) const;
        BoolType operator>(const GenericInt32<BoolType>& a) const;
        BoolType operator<(const GenericInt32<BoolType>& a) const;
        GenericInt32<BoolType> operator~() const;
        GenericInt32<BoolType> operator&(const GenericInt32<BoolType>& a) const;
        GenericInt32<BoolType> operator|(const GenericInt32<BoolType>& a) const;
        GenericInt32<BoolType> operator^(const GenericInt32<BoolType>& a) const;
        GenericInt32<BoolType> operator+(const BoolType& a) const;
        GenericInt32<BoolType> operator+(const GenericInt32<BoolType>& a) const;
        GenericInt32<BoolType> operator++(int) const;
        GenericInt32<BoolType> operator-(const GenericInt32<BoolType>& a) const;
        GenericInt32<BoolType> operator*(const GenericInt32<BoolType>& a) const;
        GenericInt32<BoolType> operator/(const GenericInt32<BoolType>& a) const;
        GenericInt32<BoolType> operator%(const GenericInt32<BoolType>& a) const;
    };

    // homomorphicEvaluation.cpp includes the definitions of all the template classes/functions/methods
    #include "homomorphicEvaluation.cpp"
};

#endif