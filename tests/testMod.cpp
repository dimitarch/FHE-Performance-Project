#include <iostream>
#include <cmath>
#include <vector>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include "../include/homomorphicEvaluation.h"

using namespace std;
using namespace homomorphicEvaluation;

bool TestModBool(){
    GenericInt32<bool> a(99), b(1000), c(0);

    c = b % a;

    int real = 1000 % 99;
    bool flag = true;

    for(int i = 0; i < 32; i++){
        flag &= (c.encValue[i] == (real%2));

        real /= 2;
    }

    return flag;
}

bool TestMod(){
    Computation cycle;
    GenericInt32<SimulatedGateBootstrappedBit> a(2), b(44), c(0);
    a.Initialize(cycle);
    b.Initialize(cycle);
    c.Initialize(cycle);

    c = b % a;

    int real = 44 % 2;
    bool flag = true;

    for(int i = 0; i < 32; i++) {
        flag &= (c.encValue[i].value == (real%2));

        real /= 2;
    }

    cout<<cycle.GetBootstrapping()<<endl;

    return flag;
}

bool TestModCircuit() {
    Computation cycle;
    GenericInt32<SimulatedCircuitBootstrappedBit> a(99), b(1000), c(0);
    a.Initialize(cycle);
    b.Initialize(cycle);
    c.Initialize(cycle);

    c = b % a;

    int real = 1000 % 99;
    bool flag = true;

    for(int i = 0; i < 32; i++) {
        flag &= (c.encValue[i].value == (real%2));

        real /= 2;
    }

    cout<<cycle.GetBootstrapping()<<endl;

    return flag;
}

int main(){
    cout<<TestModBool()<<endl;
    cout<<TestMod()<<endl;
    cout<<TestModCircuit()<<endl;

    return 0;
}