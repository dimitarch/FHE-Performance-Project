#include <iostream>
#include <cmath>
#include <vector>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include "../include/homomorphicEvaluation.h"

using namespace std;
using namespace homomorphicEvaluation;

bool Searching() {
    Computation cycle;
    GenericInt32<SimulatedGateBootstrappedBit> a[10];

    for(int i = 0; i < 10; i++) {
        a[i].Initialize(rand() % 25, cycle);
    }

    GenericInt32<SimulatedGateBootstrappedBit> x;
    x.Initialize(cycle);
    x = a[4];

    SimulatedGateBootstrappedBit result(0);
    result.Initialize(cycle);

    for(int i = 0; i < 10; i++) {
        result = result | (x == a[i]);
    }

    return result.value;
}

int Counting() {
    Computation cycle;
    GenericInt32<SimulatedGateBootstrappedBit> a[10], x, result, zero(0), one(1);

    for(int i = 0; i < 10; i++) {
        a[i].Initialize(rand() % 25, cycle);
    }

    x.Initialize(cycle);
    x = a[4];

    result.Initialize(cycle);

    for(int i = 0; i < 10; i++) {
        result = result + (x == a[i]);
    }

    int ans = 0;
    for(int i = 31; i >= 0; i--) {
        ans *= 2;
        ans += result.encValue[i].value;
    }

    return ans;
}

int main(){
    cout<<Searching()<<endl;
    cout<<Counting()<<endl;
    return 0;
}