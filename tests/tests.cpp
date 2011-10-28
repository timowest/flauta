#include <sndfile.hh>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>

//#include "dsp.h"
#include "blow.cpp"
#include "bernoulli.cpp"
#include "jetdrive.cpp"
#include "receptivity.cpp"
#include "turbulence.cpp"
#include "vortex.cpp"

#define SR       44100
#define SIZE     22050
#define LINESIZE 220500

using namespace std;

void write(ofstream* out, float* floats) {
    (*out) << floats[0];
    for (int i = 1; i < SIZE; i++) {
        (*out) << "," << floats[i];
    }
    (*out) << "\n";
}

void read(const char* in_file, float* floats) {
    // TODO : optimize
    char line[LINESIZE];
    ifstream in(in_file);
    in.getline(line, LINESIZE);
    
    char *pch = strtok(line, ",");
    while (pch != NULL) {
        *floats = atof(pch);
        pch = strtok(NULL, ",");
        floats++;
    }

    in.close();
}

void test(dsp* processor, float** inputs, const char* out_file, int index, int out_count);

int main() {
    blow bl;       // 1 in, 3 out
    bernoulli b;   // 2 in, 3 out
    jetdrive jd;   // 2 in, 2 out
    receptivity r; // 3 in, 1 out
    turbulence t;  // 1 in, 1 out
    vortex v;      // 1 in, 1 out
    
    // inputs
    float in_imp[SIZE], in_noise[SIZE], in_ramp[SIZE], in_sine[SIZE], in_triang[SIZE];
    read("tests/in_imp.txt", in_imp);
    read("tests/in_noise.txt", in_noise);
    read("tests/in_ramp.txt", in_ramp);
    read("tests/in_sine.txt", in_sine);
    read("tests/in_triang.txt", in_triang);
    float* all_inputs[] = {in_imp, in_noise, in_ramp, in_sine, in_triang};

    // run tests
    // 1 input
    for (int i = 0; i < 5; i++) {
        float* in1[] = {all_inputs[i]};
        test(&bl,in1, "gen/blow_out_%d.txt",       i+1, 3); 
        test(&t, in1, "gen/turbulence_out_%d.txt", i+1, 1);
        test(&v, in1, "gen/vortex_out_%d.txt",     i+1, 1);
        // 2 inputs
        for (int j = 0; j < 5; j++) {
            float* in2[] = {all_inputs[i], all_inputs[j]};  
            test(&b, in2, "gen/bernoulli_out_%d.txt", (i+1)*10+j+1, 3);
            test(&jd, in2, "gen/jetdrive_out_%d.txt", (i+1)*10+j+1, 2);
            // 3 inputs
            for (int k = 0; k < 5; k++) {
                float* in3[] = {all_inputs[i], all_inputs[j], all_inputs[k]};
                test(&r, in3, "gen/receptivity_out_%d.txt", (i+1)*100+(j+1)*10+k+1, 1);
            } 
        } 
    }
}

void test(dsp* processor, float** inputs, const char* format, int index, int out_count) {
    float out1[SIZE], out2[SIZE], out3[SIZE];
    float *outputs[] = {out1, out2, out3};
    char outfile[32];
    sprintf(outfile, format, index);

    // process
    cout << outfile << endl;
    processor->init(SR);
    processor->compute(SIZE, inputs, outputs);

    // serialize outputs to file
    ofstream out(outfile);
    write(&out, out1);
    if (out_count > 1) write(&out, out2);
    if (out_count > 2) write(&out, out3);
    out.close();
}
