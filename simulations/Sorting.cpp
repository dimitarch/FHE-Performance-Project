#include <iostream>
#include <cmath>
#include <vector>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include "../include/homomorphicEvaluation.h"

using namespace std;
using namespace homomorphicEvaluation;

void BubbleSortGate() {
    Computation cycle;
    GenericInt32<SimulatedGateBootstrappedBit> a[10];

    for(int i = 0; i < 10; i++) {
        a[i].Initialize(rand() % 25, cycle);
    }

    for(int i = 0; i < 10; i++) {
        for(int j = i + 1; j < 10; j++) {
            GenericInt32<SimulatedGateBootstrappedBit> minValue, maxValue;

            minValue = min(a[i], a[j]);
            maxValue = max(a[i], a[j]);

            a[i] = minValue;
            a[j] = maxValue;
        }
    }

    cout<<cycle.GetBootstrapping()<<endl;
}

void BubbleSortCircuit() {
    Computation cycle;
    GenericInt32<SimulatedCircuitBootstrappedBit> a[10];

    for(int i = 0; i < 10; i++) {
        a[i].Initialize(rand() % 25, cycle);
    }

    for(int i = 0; i < 10; i++) {
        for(int j = i + 1; j < 10; j++) {
            GenericInt32<SimulatedCircuitBootstrappedBit> minValue, maxValue;

            minValue = min(a[i], a[j]);
            maxValue = max(a[i], a[j]);

            a[i] = minValue;
            a[j] = maxValue;
        }
    }

    cout<<cycle.GetBootstrapping()<<endl;
}

/*void SelectionSortGate() {
    Computation cycle;
    GenericInt32<SimulatedGateBootstrappedBit> a[10];

    for(int i = 0; i < 10; i++) {
        a[i].Initialize(rand() % 25, cycle);
    }

    for(int i = 0; i < 10; i++) {
        GenericInt32<SimulatedGateBootstrappedBit> minValue;
        minValue = a[i + 1];
        for(int j = i + 1; j < 10; j++) {
            minValue = min(minValue, a[j]);
        }
    }

    cout<<cycle.GetBootstrapping()<<endl;
}*/

int main(){
    BubbleSortGate();
    BubbleSortCircuit();
    //cout<<SelectionSort()<<endl;
    return 0;
}