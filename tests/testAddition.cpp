#include <iostream>
#include <cmath>
#include <vector>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include "../include/homomorphicEvaluation.h"

using namespace std;
using namespace homomorphicEvaluation;

bool TestAdditionBool(){
    GenericInt32<bool> a(99), b(1000), c(0);

    c = a + b;

    int real = 1099;
    bool flag = true;

    for(int i = 0; i < 32; i++){
        flag &= (c.encValue[i] == (real%2));

        real /= 2;
    }

    return flag;
}

bool TestAddition() {
    Computation cycle;
    GenericInt32<SimulatedGateBootstrappedBit> a(99), b(1000), c(0);
    a.Initialize(cycle);
    b.Initialize(cycle);
    c.Initialize(cycle);

    c = a + b;

    int real = 1099;
    bool flag = true;

    for(int i = 0; i < 32; i++){
        flag &= (c.encValue[i].value == (real%2));

        real /= 2;
    }

    cout<<cycle.GetBootstrapping()<<endl;

    return flag;
}

bool TestAdditionCircuit() {
    Computation cycle;
    GenericInt32<SimulatedCircuitBootstrappedBit> a(99), b(1000), c(0);
    a.Initialize(cycle);
    b.Initialize(cycle);
    c.Initialize(cycle);

    c = a + b;

    int real = 1099;
    bool flag = true;

    for(int i = 0; i < 32; i++) {
        flag &= (c.encValue[i].value == (real%2));

        real /= 2;
    }

    cout<<cycle.GetBootstrapping()<<endl;

    return flag;
}

int main(){
    cout<<TestAdditionBool()<<endl;
    cout<<TestAddition()<<endl;
    cout<<TestAdditionCircuit()<<endl;

    return 0;
}