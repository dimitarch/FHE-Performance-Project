//#include <tfhe/tfhe.h>
//#include <tfhe/tfhe_io.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;

double timeBoot = (0.014419389 + 0.014402810 + 0.014405210 + 0.014414890 + 0.014415586 + 0.014418391 + 0.014418821 + 0.014417746 + 0.014404012 + 0.014400963) / 10;
double sigmaBoot = (0.000115750 + 0.000123759 + 0.000115314 + 0.000105690 + 0.000100818 + 0.000108985 + 0.000107224 + 0.000107276 + 0.000129178 + 0.000111601) / 10;

template <class T>
class timingBool {
    private:
        int countBoot;
    public:
        timingBool (int a){
            countBoot = a;
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
    double operation = countBoot * timeBoot;
    return operation;
}

template <class T>
double timingBool<T>::sigma () {
    double sigma = countBoot * sigmaBoot;
    return sigma;
}

template <class T>
T timingBool<T>::timingAND (T a, T b) {
    countBoot++;

    return  a & b;
}

template <class T>
T timingBool<T>::timingNAND (T a, T b) {
    countBoot++;

    return  !(a & b);
}

template <class T>
T timingBool<T>::timingANDYN (T a, T b) {
    countBoot++;

    return  a & (!b);
}

template <class T>
T timingBool<T>::timingANDNY (T a, T b) {
    countBoot++;

    return  (!a) & b;
}

template <class T>
T timingBool<T>::timingXOR (T a, T b) {
    countBoot++;

    return  a ^ b;
}

template <class T>
T timingBool<T>::timingXNOR (T a, T b) {
    countBoot++;

    return  !(a ^ b);
}

template <class T>
T timingBool<T>::timingOR (T a, T b) {
    countBoot++;

    return  a | b;
}

template <class T>
T timingBool<T>::timingORYN (T a, T b) {
    countBoot++;

    return  a | (!b);
}

template <class T>
T timingBool<T>::timingORNY (T a, T b) {
    countBoot++;

    return  (!a) | b;
}

template <class T>
T timingBool<T>::timingNOR (T a, T b) {
    countBoot++;

    return  !(a | b);
}

template <class T>
T timingBool<T>::timingMUX (T a, T b, T c) {
    countBoot += 2;

    return  a ? b : c;
}

timingBool <bool> timingOperations(0);

template <class T>
T andFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingAND((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T nandFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingNAND((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T andynFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingANDYN((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T andnyFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingANDNY((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T xorFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingXOR((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T xnorFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingXNOR((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T orFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingOR((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T orynFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingORYN((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T ornyFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingORNY((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T norFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingNOR((bool) (a & ith), (bool) (b & ith));

        result += temp * ith;
    }

    return  result;
}

template <class T>
bool areEqualFHE (T a, T b) {
    bool result = true, temp;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        long long ith = (long long) ((long long) 1 << i);

        temp = timingOperations.timingXNOR((bool) (a & ith), (bool) (b & ith));

        result = timingOperations.timingAND(result, temp);
    }

    return result;
}

template <class T>
T minFHE (T a, T b) {
    T result = 0;
    bool temp = false;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        long long ith = (long long) ((long long) 1 << i);

        bool tmp = timingOperations.timingXNOR((bool) (a & ith), (bool) (b & ith));

        temp = timingOperations.timingMUX(tmp, temp, (bool) (a & ith));
    }

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingMUX(temp, (bool) (b & ith), (bool) (a & ith)) * ith;
    }

    return result;
}

template <class T>
T maxFHE (T a, T b) {
    T result = 0;
    bool temp = false;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        long long ith = (long long) ((long long) 1 << i);

        bool tmp = timingOperations.timingXNOR((bool) (a & ith), (bool) (b & ith));

        temp = timingOperations.timingMUX(tmp, temp, (bool) (a & ith));
    }

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingMUX(temp, (bool) (a & ith), (bool) (b & ith)) * ith;
    }

    return result;
}

template <class T>
T addFHE (T a, T b) {
    T result = 0;
    bool carry = false;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingXOR(timingOperations.timingXOR((bool) (a & ith), (bool) (b & ith)), carry) * ith;

        bool temp = timingOperations.timingOR(timingOperations.timingAND((bool) (a & ith), (bool) (b & ith)), timingOperations.timingAND((bool) (a & ith), carry));
        carry = timingOperations.timingOR(timingOperations.timingAND(carry, (bool) (b & ith)), temp);
    }

    return result;
}

template <class T>
T subFHE (T a, T b){
    T result = 0;
    bool carry = true;

    T complementB = 0;
    complementB = ~b;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingXOR(carry, (bool) (complementB & ith)) * ith;
        carry = timingOperations.timingAND(carry, (bool) (complementB & ith));
    }
    complementB = result;

    result = 0;
    carry = false;
    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingXOR(timingOperations.timingXOR((bool) (a & ith), (bool) (complementB & ith)), carry) * ith;

        bool temp = timingOperations.timingOR(timingOperations.timingAND((bool) (a & ith), (bool) (complementB & ith)), timingOperations.timingAND((bool) (a & ith), carry));
        carry = timingOperations.timingOR(timingOperations.timingAND(carry, (bool) (complementB & ith)), temp);
    }

    return result;
}

void approximateTimeFHE () {
    cout<<"Expected execution (in seconds): "<<timingOperations.timing()<<"\r\n";
    cout<<"Expected deviation (in seconds): "<<timingOperations.sigma()<<"\r\n";
}

int main() {
    long long a, b;

    cin>>a>>b;
    cout<<subFHE(a, b)<<"\r\n";

    approximateTimeFHE();
    return 0;
}