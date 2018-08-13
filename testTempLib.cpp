//#include <tfhe/tfhe.h>
//#include <tfhe/tfhe_io.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;

double timeAND = 0.014419389, timeORYN = 0.014402810, timeORNY = 0.014405210, timeXNOR = 0.014414890, timeNOR = 0.014415586, timeXOR = 0.014418391, timeOR = 0.014418821, timeNAND = 0.014417746, timeANDNY = 0.014404012, timeANDYN = 0.014400963; 
double sigmaAND = 0.000115750, sigmaORYN = 0.000123759, sigmaORNY = 0.000115314, sigmaXNOR = 0.000105690, sigmaNOR = 0.000100818, sigmaXOR = 0.000108985, sigmaOR = 0.000107224, sigmaNAND = 0.000107276, sigmaANDNY = 0.000129178, sigmaANDYN = 0.000111601; 

template <class T>
class timingBool {
    private:
        int countAND;
        int countNAND;
        int countXOR;
        int countXNOR;
        int countOR;
        int countNOR;
        int countANDYN;
        int countANDNY;
        int countORYN;
        int countORNY;
        int countMUX;
    public:
        timingBool (int a){
            countAND = a;
            countNAND = a;
            countXOR = a;
            countXNOR = a;
            countOR = a;
            countNOR = a;
            countANDYN = a;
            countANDNY = a;
            countORYN = a;
            countORNY = a;
            countMUX = a;
        }
        double timing();
        double sigma();

        T timingAND(T a, T b);
        T timingNAND(T a, T b);
        T timingANDYN(T a, T b);
        T timingANDNY(T a, T b);
        T timingXOR(T a, T b);
        T timingXNOR(T a, T b);
        T timingOR(T a, T b);
        T timingNOR(T a, T b);
        T timingORYN(T a, T b);
        T timingORNY(T a, T b);
        T timingMUX(T a, T b, T c);
};


template <class T>
double timingBool<T>::timing () {
    double operation = countAND * timeAND+ countORYN * timeORYN + countORNY * timeORNY + countXNOR * timeXNOR + countNOR * timeNOR + countXOR * timeXOR + countOR * timeOR + countNAND * timeNAND + countANDNY * timeANDNY + countANDYN * timeANDYN + 2 * countMUX * timeXOR; 
    return operation;
}

template <class T>
double timingBool<T>::sigma () {
    double sigma = countAND * sigmaAND + countORYN * sigmaORYN + countORNY * sigmaORNY + countXNOR * sigmaXNOR + countNOR * sigmaNOR + countXOR * sigmaXOR + countOR * sigmaOR + countNAND * sigmaNAND + countANDNY * sigmaANDNY + countANDYN * sigmaANDYN + 2 * countMUX * sigmaXOR; 
    return sigma;
}

template <class T>
T timingBool<T>::timingAND (T a, T b) {
    countAND++;

    return  a & b;
}

template <class T>
T timingBool<T>::timingNAND (T a, T b) {
    countNAND++;

    return  !(a & b);
}

template <class T>
T timingBool<T>::timingANDYN (T a, T b) {
    countANDYN++;

    return  a & (!b);
}

template <class T>
T timingBool<T>::timingANDNY (T a, T b) {
    countANDNY++;

    return  (!a) & b;
}

template <class T>
T timingBool<T>::timingXOR (T a, T b) {
    countXOR++;

    return  a ^ b;
}

template <class T>
T timingBool<T>::timingXNOR (T a, T b) {
    countXNOR++;

    return  !(a ^ b);
}

template <class T>
T timingBool<T>::timingOR (T a, T b) {
    countOR++;

    return  a | b;
}

template <class T>
T timingBool<T>::timingORYN (T a, T b) {
    countORYN++;

    return  a | (!b);
}

template <class T>
T timingBool<T>::timingORNY (T a, T b) {
    countORNY++;

    return  (!a) | b;
}

template <class T>
T timingBool<T>::timingNOR (T a, T b) {
    countNOR++;

    return  !(a | b);
}

template <class T>
T timingBool<T>::timingMUX (T a, T b, T c) {
    countMUX++;

    return  a ? b : c;
}

timingBool <bool> timingOperation(0);

template <class T>
T andFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingAND(true, true);

    return  a & b;
}

template <class T>
T nandFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingNAND(true, true);

    return  !(a & b);
}

template <class T>
T andynFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingANDYN(true, true);
    return  a & (!b);
}

template <class T>
T andnyFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingANDNY(true, true);

    return  (!a) & b;
}

template <class T>
T xorFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingXOR(true, true);

    return  a ^ b;
}

template <class T>
T xnorFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingXNOR(true, true);

    return  !(a ^ b);
}

template <class T>
T orFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingOR(true, true);

    return  a | b;
}

template <class T>
T orynFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingORYN(true, true);

    return  a | (!b);
}

template <class T>
T ornyFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingORNY(true, true);

    return  (!a) | b;
}

template <class T>
T norFHE (T a, T b) {
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++)
        temp = timingOperation.timingNOR(true, true);

    return  !(a | b);
}

template <class T>
bool areEqual (T a, T b) {   
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        temp = timingOperation.timingXNOR(true, true);
        if(i != sizeof(T)*CHAR_BIT - 1) temp = timingOperation.timingAND(true, true);
    }

    return (a == b);
} 

template <class T>
T minFHE (T a, T b){
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        temp = timingOperation.timingXNOR(true, true);
        temp = timingOperation.timingMUX(true, true, true);
        temp = timingOperation.timingMUX(true, true, true);
    }

    return (a<b) ? a : b;
}

template <class T>
T maxFHE (T a, T b){
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        temp = timingOperation.timingXNOR(true, true);
        temp = timingOperation.timingMUX(true, true, true);
        temp = timingOperation.timingMUX(true, true, true);
    }

    return (a>b) ? a : b;
}

template <class T>
T addFHE (T a, T b){
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        temp = timingOperation.timingXOR(true, true);
        temp = timingOperation.timingXOR(true, true);
        temp = timingOperation.timingXOR(true, true);
        temp = timingOperation.timingAND(true, true);
        temp = timingOperation.timingAND(true, true);
    }

    return  (a + b);
}

template <class T>
T subFHE (T a, T b){
    bool temp;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        temp = timingOperation.timingXOR(true, true);
        temp = timingOperation.timingXOR(true, true);
        temp = timingOperation.timingXOR(true, true);
        temp = timingOperation.timingXOR(true, true);
        temp = timingOperation.timingAND(true, true);
        temp = timingOperation.timingAND(true, true);
        temp = timingOperation.timingAND(true, true);
    }

    return  (a - b);
}

int main() {
    short a, b;
    cin>>a>>b;
    cout<<areEqual(a, b)<<endl;
    cout<<addFHE(a, b)<<endl;
    cout<<timingOperation.timing()<<" "<<timingOperation.sigma()<<endl;
    return 0;
}
