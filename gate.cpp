#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

long long bootCount = 0;

class bitFHE{
    public:
        bool value;

        bitFHE(){
            value = 0;
        }

        bitFHE(bool n){
            value = n;
        }

        bitFHE& operator&(const bitFHE& a){
            bootCount++;
            bitFHE b(0);

            b.value = value & a.value;
            return b;
        }

        bitFHE& operator^(const bitFHE& a){
            bootCount++;
            bitFHE b(0);

            b.value = value ^ a.value;
            return b;
        }

        bitFHE& operator|(const bitFHE& a){
            bootCount++;
            bitFHE b(0);

            b.value = value | a.value;
            return b;
        }

        bitFHE& operator!(){
            value = !value;
            return *this;
        }
};

bitFHE mux(bitFHE a, bitFHE b, bitFHE c){
    bootCount += 2;
    bitFHE d;

    d.value = a.value ? b.value : c.value;

    return d;
}

class intFHE{
    public:
    int value;
    vector<bitFHE> encValue;

    intFHE(){
        value = 0;
        for(int i = 0; i < 32; i++){
            bitFHE a(0);
            encValue.push_back(a);
        }
    }

    intFHE(int n){
        value = n;
        for(int i = 0; i < 32; i++){
            bitFHE a(n%2);
            encValue.push_back(a);
            n/=2;
        }
    }

    bitFHE& operator==(const intFHE& a){
        bitFHE ans, temp;

        for(int i = 0; i < 32; i++){
            temp = !(encValue[i] ^ a.encValue[i]);

            if(i != 0) ans = ans & temp;
            else ans = temp;
        }

        return ans;
    }

    bitFHE& operator>(const intFHE& a){
        bitFHE ans(0), temp;

        for(int i = 0; i < 32; i++){
            temp = !(encValue[i] ^ a.encValue[i]);

            ans = mux(temp, ans, encValue[i]);
        }

        return ans;
    }

    bitFHE& operator<(const intFHE& a){
        bitFHE ans(0), temp;

        for(int i = 0; i < 32; i++){
            temp = !(encValue[i] ^ a.encValue[i]);

            ans = mux(temp, ans, encValue[i]);
        }

        return !ans;
    }

    intFHE& operator+(const intFHE& a){
        bitFHE carry(0), temp(0);

        intFHE result(0);

        for(int i = 0; i < 32; i++){
            temp = encValue[i] ^ a.encValue[i];
            result.encValue[i] = temp ^ carry;

            carry = (encValue[i] & a.encValue[i]) | (temp & carry);
        }

        result.value = value + a.value;
        return result;
    }
};

int GetBootstrapping(){
    return bootCount;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    intFHE a(15), b(16), c(0);

    c = (a+b);
    cout<<c.value<<endl;
    cout<<GetBootstrapping()<<endl;
    return 0;
}