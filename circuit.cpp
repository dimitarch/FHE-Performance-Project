#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class bitFHE{
    public:
        int bootLevel;
        bool value;


        bitFHE(){
            value = 0;
            bootLevel = 0;
        }

        bitFHE(bool n){
            value = n;
            bootLevel = 0;
        }

        void init(bool n);
};

void bitFHE::init(bool n){
    value = n;
}

class intFHE{
    public:
        int value;
        vector<bitFHE> valueFHE;

    intFHE(int n){
        value = n;

        bitFHE temp;
        for(int i = 0; i < 32; i++){
            temp.init((bool) (n % 2));
            n/=2;

            valueFHE.push_back(temp);
        }
    }
};

int bootDepth = 0;

void xorFHE(bitFHE &c, bitFHE a, bitFHE b){
    c.value = a.value ^ b.value;
    c.bootLevel = max(a.bootLevel, b.bootLevel) + 1;

    if(c.bootLevel > bootDepth)
        bootDepth = c.bootLevel;
}

void andFHE(bitFHE &c, bitFHE a, bitFHE b){
    c.value = a.value & b.value;
    c.bootLevel = max(a.bootLevel, b.bootLevel) + 1;

    if(c.bootLevel > bootDepth)
        bootDepth = c.bootLevel;
}

void orFHE(bitFHE &c, bitFHE a, bitFHE b){
    c.value = a.value | b.value;
    c.bootLevel = max(a.bootLevel, b.bootLevel) + 1;

    if(c.bootLevel > bootDepth)
        bootDepth = c.bootLevel;
}

void sumFHE(vector<bitFHE> &c, vector<bitFHE> a, vector<bitFHE> b){
    bitFHE zero, carry;

    int csize = max(a.size(), b.size());
    c.insert(c.begin(), csize, zero);

    for(int i = 0; i < csize; i++){
        if(i < a.size() && i < b.size()){
            xorFHE(c[i], a[i], b[i]);

            bitFHE temp1, temp2;
            andFHE(temp1, c[i], carry);
            andFHE(temp2, a[i], b[i]);

            xorFHE(c[i], c[i], carry);
            orFHE(carry, temp1, temp2);
        }
    }
}

int GetBootstrapping(){
    return bootDepth;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    bitFHE a, b, c, d;

    a.value = 1;
    b.value = 0;

    xorFHE(c, a, b);
    xorFHE(d, a, c);
    xorFHE(c, c, a);
    xorFHE(b, c, d);

    vector<bitFHE> n;
    n.push_back(a);
    n.push_back(a);

    vector<bitFHE> m;
    m.push_back(a);
    m.push_back(a);

    vector<bitFHE> k;

    sumFHE(k, n, m);

    cout<<GetBootstrapping()<<endl;
    return 0;
}