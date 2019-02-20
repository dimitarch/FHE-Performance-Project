#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

long long bootCount = 0, encCount = 0;

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
    int value;
    vector<BoolType> encValue;

    GenericInt32() {
        value = 0;
        for(int i = 0; i < 32; i++) {
            BoolType a;
            encValue.push_back(a);
        }
    }

    GenericInt32(int n) {
        value = n;
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

        result.value = ~value;
        return result;
    }

    GenericInt32 operator&(const GenericInt32& a) const {
        GenericInt32 result;

        for(int i = 0; i < 32; i++)
            result.encValue[i] = encValue[i] & a.encValue[i];

        result.value = value & a.value;
        return result;
    }

    GenericInt32 operator|(const GenericInt32& a) const {
        GenericInt32 result;

        for(int i = 0; i < 32; i++)
            result.encValue[i] = encValue[i] | a.encValue[i];

        result.value = value | a.value;
        return result;
    }

    GenericInt32 operator^(const GenericInt32& a) const {
        GenericInt32 result;

        for(int i = 0; i < 32; i++)
            result.encValue[i] = encValue[i] ^ a.encValue[i];

        result.value = value ^ a.value;
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

        result.value = value + a.value;
        return result;
    }

    GenericInt32 operator++(int) const {
        BoolType carry(1);

        GenericInt32 result;

        for(int i = 0; i < 32; i++) {
            result.encValue[i] = encValue[i] ^ carry;
            carry = encValue[i] & carry;
        }

        result.value = value + 1;

        return result;
    }

    GenericInt32 operator-(const GenericInt32& a) const {
        GenericInt32 result;

        result = ~a;
        result = result++;
        result = result + *this;

        result.value = value - a.value;
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

        result.value = value * a.value;
        return result;
    }

    GenericInt32 operator/(const GenericInt32& a) const {
        BoolType def, max, one(1);
        GenericInt32 result, divident, temp , zero;

        for(int i = 0; i < 32; i++)
            divident.encValue[i] = encValue[i];
        divident.value = value;

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

        result.value = value / a.value;
        return result;
    }

    GenericInt32 operator%(const GenericInt32& a) const {
        BoolType def, max, one(1);
        GenericInt32 divident, temp , zero;

        for(int i = 0; i < 32; i++)
            divident.encValue[i] = encValue[i];
        divident.value = value;

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
    cout<<TestAddition()<<endl;
    cout<<TestSubtraction()<<endl;
    cout<<TestMultiplication()<<endl;
    cout<<TestDivision()<<endl;
    cout<<TestMod()<<endl;

    cout<<GetBootstrapping()<<endl;
    cout<<GetEncryption()<<endl;
    return 0;
}