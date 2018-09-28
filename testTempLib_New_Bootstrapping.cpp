//#include <tfhe/tfhe.h>
//#include <tfhe/tfhe_io.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <vector>

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
        bool temp = timingOperations.timingAND(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T nandFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingNAND(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T andynFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingANDYN(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T andnyFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingANDNY(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T xorFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingXOR(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T xnorFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingXNOR(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T orFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingOR(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T orynFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingORYN(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T ornyFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingORNY(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
T norFHE (T a, T b) {
    T result = 0;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);
        bool temp = timingOperations.timingNOR(((a >> i) & 1), ((b >> i) & 1));

        result += temp * ith;
    }

    return  result;
}

template <class T>
bool areEqualFHE (T a, T b) {
    bool result = true, temp;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        long long ith = (long long) ((long long) 1 << i);

        temp = timingOperations.timingXNOR(((a >> i) & 1), ((b >> i) & 1));

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

        bool tmp = timingOperations.timingXNOR(((a >> i) & 1), ((b >> i) & 1));

        temp = timingOperations.timingMUX(tmp, temp, ((a >> i) & 1));
    }

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingMUX(temp, ((b >> i) & 1), ((a >> i) & 1)) * ith;
    }

    return result;
}

template <class T>
T maxFHE (T a, T b) {
    T result = 0;
    bool temp = false;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        long long ith = (long long) ((long long) 1 << i);

        bool tmp = timingOperations.timingXNOR(((a >> i) & 1), ((b >> i) & 1));

        temp = timingOperations.timingMUX(tmp, temp, ((a >> i) & 1));
    }

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingMUX(temp, ((a >> i) & 1), ((b >> i) & 1)) * ith;
    }

    return result;
}

template <class T>
T addFHE (T a, T b) {
    T result = 0;
    bool carry = false;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++) {
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingXOR(timingOperations.timingXOR(((a >> i) & 1), ((b >> i) & 1)), carry) * ith;

        bool temp = timingOperations.timingOR(timingOperations.timingAND(((a >> i) & 1), ((b >> i) & 1)), timingOperations.timingAND(((a >> i) & 1), carry));
        carry = timingOperations.timingOR(timingOperations.timingAND(carry, ((b >> i) & 1)), temp);
    }

    return result;
}

template <class T>
T addOneFHE (T a) {
    T result = 0;
    bool carry = true;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);

        result += timingOperations.timingXOR(carry, ((a >> i) & 1)) * ith;
        carry = timingOperations.timingAND(carry, ((a >> i) & 1));
    }

    return result;
}

template <class T>
T subFHE (T a, T b){
    T complementB = addOneFHE(~b);
    T result = addFHE(a, complementB);

    return result;
}

template <class T>
T multFHE (T a, T b){
    T result = 0;
    T limit = ((1 << (sizeof(T)*CHAR_BIT - 2)) - 1) * 2 + 1;

    for(int i = 0; i < sizeof(T)*CHAR_BIT; i++){
        long long ith = (long long) ((long long) 1 << i);

        T tmp = limit * ((b >> i) & 1);
        tmp = andFHE(a, tmp);
        tmp = tmp << i;

        result = addFHE(result, tmp);
    }

    return result;
}

template <class T>
T divFHE (T a, T b){
    T result = 0;

    for(int i = sizeof(T)*CHAR_BIT - 1; i >= 0; i--){
        T temp = maxFHE((b << i), (((1 << sizeof(T)*CHAR_BIT - 2) - 1) * 2 + 1) * (areEqualFHE((b << i), 0)));
        bool c = timingOperations.timingMUX(areEqualFHE(maxFHE(temp, a), a), 1, 0);

        a = subFHE(a, (b << i) * c);
        result += (1 << i) * c;
    }

    return result;
}

template <class T>
T remFHE (T a, T b){
    for(int i = sizeof(T)*CHAR_BIT - 1; i >= 0; i--){
        T temp = maxFHE((b << i), (((1 << sizeof(T)*CHAR_BIT - 2) - 1) * 2 + 1) * (areEqualFHE((b << i), 0)));
        bool c = timingOperations.timingMUX(areEqualFHE(maxFHE(temp, a), a), 1, 0);

        a = subFHE(a, (b << i) * c);
    }

    return a;
}

void resize(vector<bool> &x, int n){
    if(n > x.size())
        x.insert(x.end(),  n - x.size(), 0);
}

void init(vector<bool> &x, int n){
    x.clear();
    x.insert(x.begin(), n, 0);
}

void addNFHE (vector<bool> &result, vector<bool> a, vector<bool> b, int n){
    resize(a, n);
    resize(b, n);
    init(result, n);

    bool carry = false;

    for(int i = 0; i < n; i++) {
        result[i] = timingOperations.timingXOR(timingOperations.timingXOR(a[i], b[i]), carry);

        bool temp = timingOperations.timingOR(timingOperations.timingAND(a[i], b[i]), timingOperations.timingAND(a[i], carry));
        carry = timingOperations.timingOR(timingOperations.timingAND(carry, b[i]), temp);
    }
}

void addOneNFHE (vector<bool> &result, vector<bool> a, int n) {
    resize(a, n);
    init(result, n);

    bool carry = true;

    for(int i = 0; i < n; i++){
        result[i] = timingOperations.timingXOR(carry, a[i]);
        carry = timingOperations.timingAND(carry, a[i]);
    }
}

void subNFHE (vector<bool> &result, vector<bool> a, vector<bool> b, int n){
    resize(a, n);
    resize(b, n);
    init(result, n);

    vector<bool> complementB(n);
    for(int i = 0; i < n; i++){
        complementB[i] = !b[i];
    }

    vector<bool> temp;
    addOneNFHE(temp, complementB, n);
    addNFHE(result, a, temp, n);
}

void multNFHE(vector<bool> &result, vector<bool> a, vector<bool> b, int n){
    vector<bool> temp;
    vector<bool> tempRes;
    init(temp, n);
    init(result, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp[j] = timingOperations.timingAND(a[j], b[i]);
        }

        temp.insert(temp.begin(), i, 0);

        addNFHE(tempRes, result, temp, n);
        result = tempRes;
    }
}

void multKaratsubaFHE (vector<bool> &result, vector<bool> a, vector<bool> b, int n, int depth){
    resize(a, n);
    resize(b, n);
    init(result, n);

    if(depth <= 8){
        multNFHE(result, a, b, n);
        return;
    }

    vector<bool> lowA;
    for(int i = 0; i < depth/2; i++)
        lowA.push_back(a[i]);

    vector<bool> lowB;
    for(int i = 0; i < depth/2; i++)
        lowB.push_back(b[i]);

    vector<bool> highA;
    for(int i = depth/2; i < depth; i++)
        highA.push_back(a[i]);

    vector<bool> highB;
    for(int i = depth/2; i < depth; i++)
        highB.push_back(b[i]);

    vector<bool> z0(n);
    init(z0, n);
    vector<bool> z1(n);
    init(z1, n);
    vector<bool> z2(n);
    init(z2, n);

    vector<bool> tmp1;
    addNFHE(tmp1, lowA, highA, (depth%2 == 0) ? (depth/2 + 1) : (depth/2 + 2));
    vector<bool> tmp2;
    addNFHE(tmp2, lowB, highB, (depth%2 == 0) ? (depth/2 + 1) : (depth/2 + 2));

    multKaratsubaFHE(z0, lowA, lowB, n, ceil((double) depth/2));
    multKaratsubaFHE(z1, tmp1, tmp2, n, (depth%2 == 0) ? (depth/2 + 1) : (depth/2 + 2));
    multKaratsubaFHE(z2, highA, highB, n, ceil((double) depth/2));

    addNFHE(tmp1, z0, z2, n);
    subNFHE(tmp2, z1, tmp1, n);

    z1 = tmp2;

    z2.insert(z2.begin(), ((int) depth/2) * 2, 0);
    z1.insert(z1.begin(),  depth/2, 0);

    addNFHE(tmp1, z0, z2, n);
    addNFHE(result, tmp1, z1, n);

    return;
}

void approximateTimeFHE () {
    cout<<"Expected execution (in seconds): "<<timingOperations.timing()<<"\r\n";
    cout<<"Expected deviation (in seconds): "<<timingOperations.sigma()<<"\r\n";
}

int main() {
    /*vector<bool> a;
    vector<bool> b;
    vector<bool> result;
    int d;
    cin>>d;
    for(int j = 0;  j < 100; j++){
    long long x, y;
    x = (long long) (rand() * rand() * (rand() % 100)) - 1;
    y = 511;

    for(int i = 0; i < 64; i++){
        a.push_back(x>>i & 1);
        b.push_back(y>>i & 1);
    }

    multNFHE(result, a, b, 64);

    long long ans = 0;
    for(int i = 63; i >= 0; i--){
        ans += ((long long) result[i] << i);
    }

    //approximateTimeFHE();

    //if(ans != multFHE(x, y))
    cout<<x<<" "<<y<<" "<<ans<<" "<<multFHE((long long) x, (long long) y)<<" "<< ans - multFHE((long long) x, (long long) y)<<endl;

    //approximateTimeFHE();
    a.clear();
    b.clear();
    result.clear();
    }
    approximateTimeFHE();*/
    int a, b;
    cin>>a>>b;
    cout<<remFHE(a, b)<<endl;
    return 0;
}