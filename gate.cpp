#include <iostream>
#include <cmath>
#include <vector>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>

using namespace std;

long long bootCount = 0, encCount = 0;

//generate a keyset
const int minimum_lambda = 110;
const TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);
//generate a random key
TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);

class RealGateBootstrappedBit {
    public:
        LweSample* value = new_gate_bootstrapping_ciphertext(params);

        RealGateBootstrappedBit() {
            bootsSymEncrypt(value, 0, key);
        }

        RealGateBootstrappedBit(bool n) {
            bootsSymEncrypt(value, n, key);
        }

        void operator=(const RealGateBootstrappedBit& a) const {
            bootsCOPY(value, a.value, &key->cloud);
        }

        RealGateBootstrappedBit operator&(const RealGateBootstrappedBit& a) const {
            RealGateBootstrappedBit b(0);

            bootsAND(b.value, value, a.value, &key->cloud);
            return b;
        }

        RealGateBootstrappedBit operator^(const RealGateBootstrappedBit& a) const {
            RealGateBootstrappedBit b(0);

            bootsXOR(b.value, value, a.value, &key->cloud);
            return b;
        }

        RealGateBootstrappedBit operator|(const RealGateBootstrappedBit& a) const {
            RealGateBootstrappedBit b(0);

            bootsOR(b.value, value, a.value, &key->cloud);
            return b;
        }

        RealGateBootstrappedBit operator!() const {
            RealGateBootstrappedBit b(0);

            bootsNOT(b.value, value, &key->cloud);
            return b;
        }
};

class SimulatedGateBootstrappedBit {
    public:
        bool value;

        SimulatedGateBootstrappedBit() {
            value = 0;
            encCount++;
        }

        SimulatedGateBootstrappedBit(bool n) {
            value = n;
            encCount++;
        }

        SimulatedGateBootstrappedBit operator&(const SimulatedGateBootstrappedBit& a) const {
            bootCount++;
            SimulatedGateBootstrappedBit b(0);

            b.value = value & a.value;
            return b;
        }

        SimulatedGateBootstrappedBit operator^(const SimulatedGateBootstrappedBit& a) const {
            bootCount++;
            SimulatedGateBootstrappedBit b(0);

            b.value = value ^ a.value;
            return b;
        }

        SimulatedGateBootstrappedBit operator|(const SimulatedGateBootstrappedBit& a) const {
            bootCount++;
            SimulatedGateBootstrappedBit b(0);

            b.value = value | a.value;
            return b;
        }

        SimulatedGateBootstrappedBit operator!() const {
            SimulatedGateBootstrappedBit b(0);

            b.value = !value;
            return b;
        }
};

SimulatedGateBootstrappedBit mux(SimulatedGateBootstrappedBit a, SimulatedGateBootstrappedBit b, SimulatedGateBootstrappedBit c) {
    bootCount += 2;
    SimulatedGateBootstrappedBit d;

    d.value = a.value ? b.value : c.value;

    return d;
}

template <class BoolType>
class GenericInt32 {
    public:
    vector<BoolType> encValue;

    GenericInt32() {
        for(int i = 0; i < 32; i++) {
            BoolType a;
            encValue.push_back(a);
        }
    }

    GenericInt32(int n) {
        for(int i = 0; i < 32; i++) {
            BoolType a(n%2);
            encValue.push_back(a);
            n/=2;
        }
    }

    BoolType operator==(const GenericInt32& a) const {
        BoolType ans, temp;

        for(int i = 0; i < 32; i++) {
            temp = !(encValue[i] ^ a.encValue[i]);

            if(i != 0) ans = ans & temp;
            else ans = temp;
        }

        return ans;
    }

    BoolType operator>(const GenericInt32& a) const {
        BoolType ans, temp;

        for(int i = 0; i < 32; i++) {
            temp = !(encValue[i] ^ a.encValue[i]);

            ans = mux(temp, ans, encValue[i]);
        }

        return ans;
    }

    BoolType operator<(const GenericInt32& a) const {
        BoolType ans, temp;

        for(int i = 0; i < 32; i++) {
            temp = !(encValue[i] ^ a.encValue[i]);

            ans = mux(temp, ans, encValue[i]);
        }

        return !ans;
    }

    GenericInt32 operator~() const {
        GenericInt32 result;

        for(int i = 0; i < 32; i++)
            result.encValue[i] = !encValue[i];

        return result;
    }

    GenericInt32 operator&(const GenericInt32& a) const {
        GenericInt32 result;

        for(int i = 0; i < 32; i++)
            result.encValue[i] = encValue[i] & a.encValue[i];

        return result;
    }

    GenericInt32 operator|(const GenericInt32& a) const {
        GenericInt32 result;

        for(int i = 0; i < 32; i++)
            result.encValue[i] = encValue[i] | a.encValue[i];

        return result;
    }

    GenericInt32 operator^(const GenericInt32& a) const {
        GenericInt32 result;

        for(int i = 0; i < 32; i++)
            result.encValue[i] = encValue[i] ^ a.encValue[i];

        return result;
    }

    GenericInt32 operator+(const GenericInt32& a) const {
        BoolType carry, temp;

        GenericInt32 result;

        for(int i = 0; i < 32; i++) {
            temp = encValue[i] ^ a.encValue[i];
            result.encValue[i] = temp ^ carry;

            carry = (encValue[i] & a.encValue[i]) | (temp & carry);
        }

        return result;
    }

    GenericInt32 operator++(int) const {
        BoolType carry(1);

        GenericInt32 result;

        for(int i = 0; i < 32; i++) {
            result.encValue[i] = encValue[i] ^ carry;
            carry = encValue[i] & carry;
        }

        return result;
    }

    GenericInt32 operator-(const GenericInt32& a) const {
        GenericInt32 result;

        result = ~a;
        result = result++;
        result = result + *this;

        return result;
    }

    GenericInt32 operator*(const GenericInt32& a) const {
        BoolType def;
        GenericInt32 result, temp;

        for(int i = 0 ; i < 32; i++) {
            for(int j = 31; j >= 0; j--)
                if(j >= i) temp.encValue[j] = encValue[j - i] & a.encValue[i];
                else temp.encValue[i] = def;

            result = result + temp;
        }

        return result;
    }

    GenericInt32 operator/(const GenericInt32& a) const {
        BoolType def, max, one(1);
        GenericInt32 result, divident, temp , zero;

        for(int i = 0; i < 32; i++)
            divident.encValue[i] = encValue[i];

        for(int i = 31; i >= 0; i--) {
            for(int j = 31; j >= 0; j--)
                if(j >= i) temp.encValue[j] = a.encValue[j - i];
                else temp.encValue[j] = def;

            max = temp > zero;
            for(int j = 0; j < 32; j++)
                temp.encValue[j] = mux(max, temp.encValue[j], one);

            max = (divident > temp) | (divident == temp);
            for(int j = 0; j < 32; j++)
                temp.encValue[j] = temp.encValue[j] & max;

            divident = divident - temp;
            result.encValue[i] = max;
        }

        return result;
    }

    GenericInt32 operator%(const GenericInt32& a) const {
        BoolType def, max, one(1);
        GenericInt32 divident, temp , zero;

        for(int i = 0; i < 32; i++)
            divident.encValue[i] = encValue[i];

        for(int i = 31; i >= 0; i--) {
            for(int j = 31; j >= 0; j--)
                if(j >= i) temp.encValue[j] = a.encValue[j - i];
                else temp.encValue[j] = def;

            max = temp > zero;
            for(int j = 0; j < 32; j++)
                temp.encValue[j] = mux(max, temp.encValue[j], one);

            max = (divident > temp) | (divident == temp);
            for(int j = 0; j < 32; j++)
                temp.encValue[j] = temp.encValue[j] & max;

            divident = divident - temp;
        }

        return divident;
    }
};

bool TestAddition(){
    GenericInt32<SimulatedGateBootstrappedBit> a(99), b(1000), c(0);
    c = a + b;
    int real = 1099;
    bool flag = true;

    for(int i = 0; i < 32; i++){
        flag &= (c.encValue[i].value == (real%2));
        real /= 2;
    }

    return flag;
}

bool TestSubtraction(){
    GenericInt32<SimulatedGateBootstrappedBit> a(99), b(1000), c(0);
    c = b - a;
    int real = 1000 - 99;
    bool flag = true;

    for(int i = 0; i < 32; i++){
        flag &= (c.encValue[i].value == (real%2));
        real /= 2;
    }

    return flag;
}

bool TestMultiplication(){
    GenericInt32<SimulatedGateBootstrappedBit> a(99), b(1000), c(0);
    c = b * a;
    int real = 1000 * 99;
    bool flag = true;

    for(int i = 0; i < 32; i++){
        flag &= (c.encValue[i].value == (real%2));
        real /= 2;
    }

    return flag;
}

bool TestDivision(){
    GenericInt32<SimulatedGateBootstrappedBit> a(99), b(1000), c(0);
    c = b / a;
    int real = 1000 / 99;
    bool flag = true;

    for(int i = 0; i < 32; i++){
        flag &= (c.encValue[i].value == (real%2));
        real /= 2;
    }

    return flag;
}

bool TestMod(){
    GenericInt32<SimulatedGateBootstrappedBit> a(99), b(1000), c(0);
    c = b % a;
    int real = 1000 % 99;
    bool flag = true;

    for(int i = 0; i < 32; i++){
        flag &= (c.encValue[i].value == (real%2));
        real /= 2;
    }

    return flag;
}

int GetBootstrapping(){
    return bootCount;
}

int GetEncryption(){
    return encCount;
}

int main(){
    RealGateBootstrappedBit a(0), b(1), c;
    cout<<"*"<<endl;
    c = a | b;
    cout<<"*"<<endl;
    cout<<bootsSymDecrypt(c.value, key)<<endl;

    cout<<TestAddition()<<endl;
    cout<<TestSubtraction()<<endl;
    cout<<TestMultiplication()<<endl;
    cout<<TestDivision()<<endl;
    cout<<TestMod()<<endl;

    cout<<GetBootstrapping()<<endl;
    cout<<GetEncryption()<<endl;
    return 0;
}