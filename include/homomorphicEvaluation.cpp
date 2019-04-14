void Computation::Bootstrap() {
    bootCount++;
}

void Computation::Encrypt() {
    encCount++;
}

long long Computation::GetBootstrapping() {
    return bootCount;
}

long long Computation::GetEncryptions() {
    return encCount;
}

void RealGateBootstrappedBit::operator=(const RealGateBootstrappedBit &a) const {
    bootsCOPY(value, a.value, &key->cloud);
}

RealGateBootstrappedBit RealGateBootstrappedBit::operator&(const RealGateBootstrappedBit &a) const {
    RealGateBootstrappedBit b(0);

    bootsAND(b.value, value, a.value, &key->cloud);
    return b;
}

RealGateBootstrappedBit RealGateBootstrappedBit::operator^(const RealGateBootstrappedBit &a) const {
    RealGateBootstrappedBit b(0);

    bootsXOR(b.value, value, a.value, &key->cloud);
    return b;
}

RealGateBootstrappedBit RealGateBootstrappedBit::operator|(const RealGateBootstrappedBit &a) const {
    RealGateBootstrappedBit b(0);

    bootsOR(b.value, value, a.value, &key->cloud);
    return b;
}

RealGateBootstrappedBit RealGateBootstrappedBit::operator!() const {
    RealGateBootstrappedBit b(0);

    bootsNOT(b.value, value, &key->cloud);
    return b;
}

RealGateBootstrappedBit mux(RealGateBootstrappedBit a, RealGateBootstrappedBit b, RealGateBootstrappedBit c) {
    RealGateBootstrappedBit d;

    bootsMUX(d.value, a.value, b.value, c.value, &key->cloud);

    return d;
}

void SimulatedGateBootstrappedBit::Initialize(Computation &newComputation) {
    routine = &newComputation;
    routine->Encrypt();
}

void SimulatedGateBootstrappedBit::Initialize(bool n, Computation &newComputation) {
    value = n;
    routine = &newComputation;
    routine->Encrypt();
}

SimulatedGateBootstrappedBit SimulatedGateBootstrappedBit::operator&(const SimulatedGateBootstrappedBit &a) const {
    SimulatedGateBootstrappedBit b;

    b.value = value & a.value;
    b.routine = routine;

    routine->Bootstrap();
    return b;
}

SimulatedGateBootstrappedBit SimulatedGateBootstrappedBit::operator^(const SimulatedGateBootstrappedBit &a) const {
    SimulatedGateBootstrappedBit b;

    b.value = value ^ a.value;
    b.routine = routine;

    routine->Bootstrap();
    return b;
}

SimulatedGateBootstrappedBit SimulatedGateBootstrappedBit::operator|(const SimulatedGateBootstrappedBit &a) const {
    SimulatedGateBootstrappedBit b;

    b.value = value | a.value;
    b.routine = routine;

    routine->Bootstrap();
    return b;
}

SimulatedGateBootstrappedBit SimulatedGateBootstrappedBit::operator!() const {
    SimulatedGateBootstrappedBit b;

    b.value = !value;
    b.routine = routine;

    return b;
}

SimulatedGateBootstrappedBit mux(SimulatedGateBootstrappedBit a, SimulatedGateBootstrappedBit b, SimulatedGateBootstrappedBit c) {
    SimulatedGateBootstrappedBit d;

    d.value = a.value ? b.value : c.value;

    d.routine -> Bootstrap();
    d.routine -> Bootstrap();
    return d;
}

void SimulatedCircuitBootstrappedBit::Initialize(Computation &newComputation) {
    routine = &newComputation;
    routine->Encrypt();
}

void SimulatedCircuitBootstrappedBit::Initialize(bool n, Computation &newComputation) {
    value = n;
    routine = &newComputation;
    routine->Encrypt();
}

SimulatedCircuitBootstrappedBit SimulatedCircuitBootstrappedBit::operator&(const SimulatedCircuitBootstrappedBit &a) const {
    SimulatedCircuitBootstrappedBit b;

    b.value = value & a.value;
    b.routine = routine;
    b.level = std::max(level, a.level) + 1;

    if (routine->GetBootstrapping() < b.level)
        routine->Bootstrap();

    return b;
}

SimulatedCircuitBootstrappedBit SimulatedCircuitBootstrappedBit::operator^(const SimulatedCircuitBootstrappedBit &a) const {
    SimulatedCircuitBootstrappedBit b;

    b.value = value ^ a.value;
    b.routine = routine;
    b.level = std::max(level, a.level) + 1;

    if (routine->GetBootstrapping() < b.level)
        routine->Bootstrap();

    return b;
}

SimulatedCircuitBootstrappedBit SimulatedCircuitBootstrappedBit::operator|(const SimulatedCircuitBootstrappedBit &a) const {
    SimulatedCircuitBootstrappedBit b;

    b.value = value | a.value;
    b.routine = routine;
    b.level = std::max(level, a.level) + 1;

    if (routine->GetBootstrapping() < b.level)
        routine->Bootstrap();

    return b;
}

SimulatedCircuitBootstrappedBit SimulatedCircuitBootstrappedBit::operator!() const {
    SimulatedCircuitBootstrappedBit b;

    b.value = !value;
    b.routine = routine;
    b.level = level;

    return b;
}

SimulatedCircuitBootstrappedBit mux(SimulatedCircuitBootstrappedBit a, SimulatedCircuitBootstrappedBit b, SimulatedCircuitBootstrappedBit c) {
    SimulatedCircuitBootstrappedBit d;

    d.value = a.value ? b.value : c.value;

    if(std::max(a.level, b.level) + 1 > d.routine -> GetBootstrapping()) {
        d.routine -> Bootstrap();
    }

    if(std::max(a.level, c.level) + 1 > d.routine -> GetBootstrapping()) {
        d.routine -> Bootstrap();
    }

    d.level = std::max(std::max(a.level, b.level), c.level) + 1;

    return d;
}

void SimulatedLevelledBit::Initialize(long long newDepth, Computation &newComputation) {
    depth = newDepth;
    routine = &newComputation;
    routine->Encrypt();
}

void SimulatedLevelledBit::Initialize(bool n, long long newDepth, Computation &newComputation) {
    value = n;
    depth = newDepth;
    routine = &newComputation;
    routine->Encrypt();
}

SimulatedLevelledBit SimulatedLevelledBit::operator&(const SimulatedLevelledBit &a) const {
    SimulatedLevelledBit b;

    b.value = value & a.value;
    b.routine = routine;
    b.level = std::max(level, a.level) + 1;
    b.depth = depth;

    if (b.depth < b.level)
    {
        b.level = 0;
        routine->Bootstrap();
    }

    return b;
}

SimulatedLevelledBit SimulatedLevelledBit::operator^(const SimulatedLevelledBit &a) const {
    SimulatedLevelledBit b;

    b.value = value ^ a.value;
    b.routine = routine;
    b.level = std::max(level, a.level) + 1;
    b.depth = depth;

    if (b.depth < b.level)
    {
        b.level = 0;
        routine->Bootstrap();
    }

    return b;
}

SimulatedLevelledBit SimulatedLevelledBit::operator|(const SimulatedLevelledBit &a) const {
    SimulatedLevelledBit b;

    b.value = value | a.value;
    b.routine = routine;
    b.level = std::max(level, a.level) + 1;
    b.depth = depth;

    if (b.depth < b.level)
    {
        b.level = 0;
        routine->Bootstrap();
    }

    return b;
}

SimulatedLevelledBit SimulatedLevelledBit::operator!() const {
    SimulatedLevelledBit b;

    b.value = !value;
    b.routine = routine;
    b.depth = depth;
    b.level = level;

    return b;
}

bool mux(bool a, bool b, bool c) {
    bool d;

    d = a ? b : c;

    return d;
}

template <class BoolType>
GenericInt32<BoolType>::GenericInt32() {
    for (int i = 0; i < 32; i++)
    {
        BoolType a(0);
        encValue.push_back(a);
    }
}

template <class BoolType>
GenericInt32<BoolType>::GenericInt32(int n) {
    for (int i = 0; i < 32; i++)
    {
        BoolType a(n % 2);
        encValue.push_back(a);
        n /= 2;
    }
}

template <class BoolType>
void GenericInt32<BoolType>::Initialize(Computation &newComputation) {
    for (int i = 0; i < 32; i++)
    {
        encValue[i].Initialize(newComputation);
    }
}

template <class BoolType>
void GenericInt32<BoolType>::Initialize(int n, Computation &newComputation) {
    for (int i = 0; i < 32; i++)
    {
        encValue[i].Initialize(n % 2, newComputation);
        n /= 2;
    }
}

template <class BoolType>
void GenericInt32<BoolType>::Initialize(int n, int newDepth, Computation &newComputation) {
    for (int i = 0; i < 32; i++)
    {
        encValue[i].Initialize(n % 2, newDepth, newComputation);
        n /= 2;
    }
}

template <class BoolType>
BoolType GenericInt32<BoolType>::operator==(const GenericInt32<BoolType> &a) const {
    BoolType ans(0), temp(0);

    for (int i = 0; i < 32; i++)
    {
        temp = !(encValue[i] ^ a.encValue[i]);

        if (i != 0)
            ans = temp & ans;
        else
            ans = temp;
    }

    return ans;
}

template <class BoolType>
BoolType GenericInt32<BoolType>::operator>(const GenericInt32<BoolType> &a) const {
    BoolType ans(0), temp(0);
    ans = encValue[0] & ans;
    temp = encValue[0] & temp;

    for (int i = 0; i < 32; i++)
    {
        temp = !(encValue[i] ^ a.encValue[i]);

        ans = mux(temp, ans, encValue[i]);
    }

    return ans;
}

template <class BoolType>
BoolType GenericInt32<BoolType>::operator<(const GenericInt32<BoolType> &a) const {
    BoolType ans(0), temp(0);
    ans = encValue[0] & ans;
    temp = encValue[0] & temp;

    for (int i = 0; i < 32; i++)
    {
        temp = !(encValue[i] ^ a.encValue[i]);

        ans = mux(temp, ans, encValue[i]);
    }

    return !ans;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator~() const {
    GenericInt32<BoolType> result;

    for (int i = 0; i < 32; i++)
        result.encValue[i] = !encValue[i];

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator&(const GenericInt32<BoolType> &a) const {
    GenericInt32<BoolType> result;

    for (int i = 0; i < 32; i++)
        result.encValue[i] = encValue[i] & a.encValue[i];

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator|(const GenericInt32<BoolType> &a) const {
    GenericInt32<BoolType> result;

    for (int i = 0; i < 32; i++)
        result.encValue[i] = encValue[i] | a.encValue[i];

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator^(const GenericInt32<BoolType> &a) const {
    GenericInt32<BoolType> result;

    for (int i = 0; i < 32; i++)
        result.encValue[i] = encValue[i] ^ a.encValue[i];

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator+(const BoolType &a) const {
    BoolType carry;

    carry = a;

    GenericInt32<BoolType> result;

    for (int i = 0; i < 32; i++)
    {
        result.encValue[i] = encValue[i] ^ carry;
        carry = encValue[i] & carry;
    }

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator+(const GenericInt32<BoolType> &a) const {
    BoolType carry(0), temp(0);

    GenericInt32<BoolType> result;

    for (int i = 0; i < 32; i++)
    {
        temp = encValue[i] ^ a.encValue[i];
        result.encValue[i] = temp ^ carry;

        carry = (encValue[i] & a.encValue[i]) | (temp & carry);
    }

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator++(int) const {
    BoolType carry(1);

    GenericInt32<BoolType> result;

    for (int i = 0; i < 32; i++)
    {
        result.encValue[i] = encValue[i] ^ carry;
        carry = encValue[i] & carry;
    }

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator-(const GenericInt32<BoolType> &a) const {
    GenericInt32<BoolType> result;

    result = ~a;
    result = result++;
    result = result + *this;

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator*(const GenericInt32<BoolType> &a) const {
    BoolType def(0);
    def = encValue[0] & def;

    GenericInt32<BoolType> result, temp;

    for (int i = 0; i < 32; i++)
    {
        for (int j = 31; j >= 0; j--)
            if (j >= i)
                temp.encValue[j] = encValue[j - i] & a.encValue[i];
            else
                temp.encValue[j] = def;

        result = temp + result;
    }

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator/(const GenericInt32<BoolType> &a) const {
    BoolType def(0), max(0), one(1);
    def = encValue[0] & def;
    one = encValue[0] | one;

    GenericInt32<BoolType> result, divident, temp, zero;

    for (int i = 0; i < 32; i++)
        divident.encValue[i] = encValue[i];

    for (int i = 31; i >= 0; i--)
    {
        for (int j = 31; j >= 0; j--)
            if (j >= i)
                temp.encValue[j] = a.encValue[j - i];
            else
                temp.encValue[j] = def;

        max = temp > zero;
        for (int j = 0; j < 32; j++)
            temp.encValue[j] = mux(max, temp.encValue[j], one);

        max = (divident > temp) | (divident == temp);
        for (int j = 0; j < 32; j++)
            temp.encValue[j] = temp.encValue[j] & max;

        divident = divident - temp;
        result.encValue[i] = max;
    }

    return result;
}

template <class BoolType>
GenericInt32<BoolType> GenericInt32<BoolType>::operator%(const GenericInt32<BoolType> &a) const {
    BoolType def(0), max(0), one(1);
    def = encValue[0] & def;
    one = encValue[0] | one;

    GenericInt32<BoolType> result, divident, temp, zero;

    for (int i = 0; i < 32; i++)
        divident.encValue[i] = encValue[i];

    for (int i = 31; i >= 0; i--)
    {
        for (int j = 31; j >= 0; j--)
            if (j >= i)
                temp.encValue[j] = a.encValue[j - i];
            else
                temp.encValue[j] = def;

        max = temp > zero;
        for (int j = 0; j < 32; j++)
            temp.encValue[j] = mux(max, temp.encValue[j], one);

        max = (divident > temp) | (divident == temp);
        for (int j = 0; j < 32; j++)
            temp.encValue[j] = temp.encValue[j] & max;

        divident = divident - temp;
    }

    return divident;
}

template <class BoolType>
GenericInt32<BoolType> min(const GenericInt32<BoolType> &a, const GenericInt32<BoolType> &b) {
    BoolType smaller(0);
    GenericInt32<BoolType> result;
    smaller = a < b;

    for (int i = 0; i < 32; i++) {
        result.encValue[i] = mux(smaller, a.encValue[i], b.encValue[i]);
    }

    return result;
}

template <class BoolType>
GenericInt32<BoolType> max(const GenericInt32<BoolType> &a, const GenericInt32<BoolType> &b) {
    BoolType smaller(0);
    GenericInt32<BoolType> result;
    smaller = a < b;

    for (int i = 0; i < 32; i++) {
        result.encValue[i] = mux(smaller, a.encValue[i], b.encValue[i]);
    }

    return result;
}