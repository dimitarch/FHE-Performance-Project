<<<<<<< HEAD
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void minFHE (LweSample* result, const LweSample* a, const LweSample* b, const int n, const TFheGateBootstrappingSecretKeySet* bk) {
    LweSample* temp = new_gate_bootstrapping_ciphertext(bk->params);

    for(int i = 0; i < n; i++) {
        LweSample* tmp = new_gate_bootstrapping_ciphertext(bk->params);
        bootsXNOR(tmp, &a[i], &b[i], &bk->cloud);
        bootsMUX(temp, tmp, temp, &a[i], &bk->cloud);
    }

    for(int i = 0; i < n; i++){
        bootsMUX(&result[i], temp, &b[i], &a[i], &bk->cloud);
    }
}

void maxFHE (LweSample* result, const LweSample* a, const LweSample* b, const int n, const TFheGateBootstrappingSecretKeySet* bk) {
    LweSample* temp = new_gate_bootstrapping_ciphertext(bk->params);

    for(int i = 0; i < n; i++) {
        LweSample* tmp = new_gate_bootstrapping_ciphertext(bk->params);
        bootsXNOR(tmp, &a[i], &b[i], &bk->cloud);
        bootsMUX(temp, tmp, temp, &a[i], &bk->cloud);
    }

    for(int i = 0; i < n; i++){
        bootsMUX(&result[i], temp, &a[i], &b[i], &bk->cloud);
    }
}

int main() {
    const int nb_bits = 101;
    const int nb_trials = 1024;

    //generate a keyset
    const int minimum_lambda = 110;
    const TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);

    //generate a random key
    uint32_t seed[] = { 327, 1592, 615 };
    tfhe_random_generator_setSeed(seed,3);
    const TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);

    fstream input, output;
    output.open("resultTime.txt", ios::app | ios::out);

    //Encryption
    input.open("testNumbers.txt", fstream::in);
    int i = 0, n = 40, bits = 32;
    int a;

    for(int l = 1; l<=2; l++){
        n = 32 / l;
        LweSample* temp[40];
    while((input >> a) && (i < n)){
        temp[i] = new_gate_bootstrapping_ciphertext_array(bits, params);

        for(int j = 0; j < bits; j++)
            bootsSymEncrypt(&temp[i][j], (a >> j) & 1, key);
        i++;
    }
    input.close();

    //Sorting
    clock_t t = clock();

    for(i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            LweSample* x = new_gate_bootstrapping_ciphertext_array(bits, params);
            LweSample* y = new_gate_bootstrapping_ciphertext_array(bits, params);

            for(int l = 0; l < bits; l++){
                bootsCOPY(&x[l], &temp[i][l], &key->cloud);
                bootsCOPY(&y[l], &temp[j][l], &key->cloud);
            }

            minFHE(temp[i], x, y, bits, key);
            maxFHE(temp[j], x, y, bits, key);
        }
    }

    t = clock() - t;
    cout<<((double)t / CLOCKS_PER_SEC)<<"\n";
    output<<n<<": "<<((double)t / CLOCKS_PER_SEC)<<"\r\n";
    }
    //delete_gate_bootstrapping_secret_keyset(key);
    //delete_gate_bootstrapping_parameters(params);
    return 0;
=======
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void minFHE (LweSample* result, const LweSample* a, const LweSample* b, const int n, const TFheGateBootstrappingSecretKeySet* bk) {
    LweSample* temp = new_gate_bootstrapping_ciphertext(bk->params);

    for(int i = 0; i < n; i++) {
        LweSample* tmp = new_gate_bootstrapping_ciphertext(bk->params);
        bootsXNOR(tmp, &a[i], &b[i], &bk->cloud);
        bootsMUX(temp, tmp, temp, &a[i], &bk->cloud);
    }

    for(int i = 0; i < n; i++){
        bootsMUX(&result[i], temp, &b[i], &a[i], &bk->cloud);
    }
}

void maxFHE (LweSample* result, const LweSample* a, const LweSample* b, const int n, const TFheGateBootstrappingSecretKeySet* bk) {
    LweSample* temp = new_gate_bootstrapping_ciphertext(bk->params);

    for(int i = 0; i < n; i++) {
        LweSample* tmp = new_gate_bootstrapping_ciphertext(bk->params);
        bootsXNOR(tmp, &a[i], &b[i], &bk->cloud);
        bootsMUX(temp, tmp, temp, &a[i], &bk->cloud);
    }

    for(int i = 0; i < n; i++){
        bootsMUX(&result[i], temp, &a[i], &b[i], &bk->cloud);
    }
}

int main() {
    const int nb_bits = 101;
    const int nb_trials = 1024;

    //generate a keyset
    const int minimum_lambda = 110;
    const TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);

    //generate a random key
    uint32_t seed[] = { 327, 1592, 615 };
    tfhe_random_generator_setSeed(seed,3);
    const TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);

    fstream input, output;
    output.open("resultTime.txt", ios::app | ios::out);

    //Encryption
    input.open("testNumbers.txt", fstream::in);
    int i = 0, n = 40, bits = 32;
    int a;

    for(int l = 1; l<=2; l++){
        n = 32 / l;
        LweSample* temp[40];
    while((input >> a) && (i < n)){
        temp[i] = new_gate_bootstrapping_ciphertext_array(bits, params);

        for(int j = 0; j < bits; j++)
            bootsSymEncrypt(&temp[i][j], (a >> j) & 1, key);
        i++;
    }
    input.close();

    //Sorting
    clock_t t = clock();

    for(i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            LweSample* x = new_gate_bootstrapping_ciphertext_array(bits, params);
            LweSample* y = new_gate_bootstrapping_ciphertext_array(bits, params);

            for(int l = 0; l < bits; l++){
                bootsCOPY(&x[l], &temp[i][l], &key->cloud);
                bootsCOPY(&y[l], &temp[j][l], &key->cloud);
            }

            minFHE(temp[i], x, y, bits, key);
            maxFHE(temp[j], x, y, bits, key);
        }
    }

    t = clock() - t;
    cout<<((double)t / CLOCKS_PER_SEC)<<"\n";
    output<<n<<": "<<((double)t / CLOCKS_PER_SEC)<<"\r\n";
    }
    //delete_gate_bootstrapping_secret_keyset(key);
    //delete_gate_bootstrapping_parameters(params);
    return 0;
>>>>>>> dea4b89a12e47aa50c3b9df88748414cc68db261
}