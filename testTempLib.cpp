//#include <tfhe/tfhe.h>
//#include <tfhe/tfhe_io.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;

template <class T>
class timeFHE{
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
        void init();
        void print();
        bool areEqual(T a, T b);  
        T minFHE(T a, T b);
        T maxFHE(T a, T b);
};

template <class T>
void timeFHE<T>::init (){
    countAND = 0;
    countNAND = 0;
    countXOR = 0;
    countXNOR = 0;
    countOR = 0;
    countNOR = 0;
    countANDYN = 0;
    countANDNY = 0;
    countORYN = 0;
    countORNY = 0;
    countMUX = 0;
}

template <class T>
void timeFHE<T>::print (){
    cout<<countAND<<"\n"<<countXNOR<<"\n"<<countMUX<<"\n"; 
}

template <class T>
bool timeFHE<T>::areEqual (T a, T b){
    countXNOR += sizeof(T) * CHAR_BIT;
    countAND += (sizeof(T) * CHAR_BIT - 1);

    return (a == b);
}

template <class T>
T timeFHE<T>::minFHE (T a, T b){
    countXNOR += sizeof(T) * CHAR_BIT;
    countMUX += 2 * (sizeof(T) * CHAR_BIT);

    return (a<b) ? a : b;
}

template <class T>
T timeFHE<T>::maxFHE (T a, T b){
    countXNOR += sizeof(T) * CHAR_BIT;
    countMUX += 2 * (sizeof(T) * CHAR_BIT);

    return (a>b) ? a : b;
}

int main() {
    int a1, b1;
    cin>>a1>>b1;
    timeFHE <int> temp1;
    temp1.init();
    cout<<temp1.areEqual(a1, b1)<<endl;
    cout<<temp1.minFHE(a1, b1)<<endl;
    cout<<temp1.maxFHE(a1, b1)<<endl;
    temp1.print();

    short a2, b2;
    cin>>a2>>b2;
    timeFHE <short> temp2;
    temp2.init();
    cout<<temp2.areEqual(a2, b2)<<endl;
    temp2.print();

    char a3, b3;
    cin>>a3>>b3;
    timeFHE <char> temp3;
    temp3.init();
    cout<<temp3.areEqual(a3, b3)<<endl;
    temp3.print();
    return 0;
}