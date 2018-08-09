#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main() {
    const int nb_bits = 100;
    const int nb_trials = 128;

    //generate a keyset
    const int minimum_lambda = 110;
    const TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);

    //generate a random key
    uint32_t seed[] = { 327, 1592, 615 };
    tfhe_random_generator_setSeed(seed,3);
    const TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);

    fstream enc, ad, xr, r, nr, xnr, nad, adny, adyn, rny, ryn, bt;
    ad.open("testAND_ALL.txt", fstream::out);
    xr.open("testXOR_ALL.txt", fstream::out);
    r.open("testOR_ALL.txt", fstream::out);
    xnr.open("testXNOR_ALL.txt", fstream::out);
    nad.open("testNAND_ALL.txt", fstream::out);
    adyn.open("testANDYN_ALL.txt", fstream::out);
    adny.open("testANDNY_ALL.txt", fstream::out);
    rny.open("testORNY_ALL.txt", fstream::out);
    ryn.open("testORYN_ALL.txt", fstream::out);
    nr.open("testNOR_ALL.txt", fstream::out);
    enc.open("testENC_ALL.txt", fstream::out);
    

    for(int it = 0; it < nb_trials; it++) {
        //Encryption
        clock_t t = clock();

        LweSample* temp = new_gate_bootstrapping_ciphertext_array(nb_bits, params);

        bt.open("testBITS_ALL.txt", fstream::in);
        int i = 0;
        string str;
        while(getline(bt, str)){
            bool a;

            if(str[0] == '0') a = 0;
            else a = 1;

            bootsSymEncrypt(&temp[i], a, key);
            i++;
        }
        bt.close();

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        enc<<((float)t / CLOCKS_PER_SEC)<<"\r\n";

        //AND
        t = clock();

        LweSample* result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsAND(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        ad<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);

        //XOR
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsXOR(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        xr<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        //NAND
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsNAND(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        nad<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        //OR
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsOR(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        r<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        //NOR
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsNOR(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        nr<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        //XNOR
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsXNOR(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        xnr<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        //ANDYN
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsANDYN(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        adyn<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        //ANDNY
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsANDNY(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        adny<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        //ORYN
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsORYN(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        ryn<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        //ORNY
        t = clock();

        result = new_gate_bootstrapping_ciphertext(params);
        bootsCOPY(result, &temp[0], &key->cloud);

        for(int i = 0; i < nb_bits; i++)
            bootsORNY(result, result, temp + i, &key->cloud);

        t = clock() - t;

        cout<<((float)t / CLOCKS_PER_SEC)<<"\n";
        rny<<((float)t / CLOCKS_PER_SEC)<<"\r\n";
        delete_gate_bootstrapping_ciphertext(result);
        delete_gate_bootstrapping_ciphertext_array(nb_bits, temp);
    }
    
    //delete_gate_bootstrapping_secret_keyset(key);
    //delete_gate_bootstrapping_parameters(params);
    return 0;
}