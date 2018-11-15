#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

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

    fstream restime, bt;
    

    //Number to search for
    int x = 12;
    //cin>>x;
    LweSample* search = new_gate_bootstrapping_ciphertext_array(16, params);
    for(int j = 0; j < 16; j++)
        bootsSymEncrypt(&search[j], (x >> j) & 1, key);

    //Encryption
    LweSample* temp[300];
    bt.open("testNumbers.txt", fstream::in);
    int i = 0, n = 300;
    int a;

    while((bt >> a) && (i < n)){
        temp[i] = new_gate_bootstrapping_ciphertext_array(16, params);
        for(int j = 0; j < 16; j++)
            bootsSymEncrypt(&temp[i][j], (a >> j) & 1, key);
        i++;
    }
    bt.close();

    //Searching
    LweSample* br = new_gate_bootstrapping_ciphertext(params);
    bootsSymEncrypt(br, 0, key);

    clock_t t = clock();
    //for(int l = 0; l < 10; l++){
    for(i = 0; i < n; i++){
        LweSample* result = new_gate_bootstrapping_ciphertext(params);

        for(int j = 0; j < 16; j++){
            LweSample* restemp = new_gate_bootstrapping_ciphertext(params);

            bootsXNOR(restemp, &temp[i][j], &search[j], &key->cloud);

            if(j != 0) bootsAND(result, result, restemp, &key->cloud);
            else bootsCOPY(result, restemp, &key->cloud);

            delete_gate_bootstrapping_ciphertext(restemp);
        }

        bootsOR(br, br, result, &key->cloud);
        delete_gate_bootstrapping_ciphertext(result);
    }
    //}
    t = clock() - t;
    cout<<bootsSymDecrypt(br, key)<<"\n";
    cout<<(double)((double)t / CLOCKS_PER_SEC)<<"\n";
    restime.open("resultTime.txt", ios::app | ios::out);
    restime<<n<<": "<<(double)((double)t / CLOCKS_PER_SEC)<<"\r\n";
    restime.close();
    //delete_gate_bootstrapping_secret_keyset(key);
    //delete_gate_bootstrapping_parameters(params);
    return 0;
}