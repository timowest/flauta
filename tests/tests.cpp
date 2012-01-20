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
#include "excitation.cpp"
#include "jetdrive.cpp"
#include "receptivity.cpp"
#include "turbulence.cpp"
#include "vortex.cpp"
#include "jet.cpp"
#include "sources.cpp"
#include "resonator.cpp"

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

int main(int argc, char *argv[]) {
    jet  jt;       // 4 in, 2 out	
    sources s;     // 3 in, 2 out
    blow bl;       // 1 in, 3 out
    bernoulli b;   // 2 in, 3 out
    excitation e;  // 2 in, 2 out
    jetdrive jd;   // 2 in, 2 out
    receptivity r; // 3 in, 1 out
    turbulence t;  // 1 in, 1 out
    vortex v;      // 1 in, 1 out
    resonator res; // 2 in, 3 out
    
    // inputs
    float in_imp[SIZE], in_noise[SIZE], in_ramp[SIZE], in_sine[SIZE], in_triang[SIZE], in_step[SIZE];
    read("tests/in_imp.txt", in_imp);       // 1
    read("tests/in_noise.txt", in_noise);   // 2
    read("tests/in_ramp.txt", in_ramp);     // 3
    read("tests/in_sine.txt", in_sine);     // 4
    read("tests/in_triang.txt", in_triang); // 5
    read("tests/in_step.txt", in_step);     // 6
    float* all_inputs[] = {in_imp, in_noise, in_ramp, in_sine, in_triang, in_step};

    // run tests
    // 1 input
    for (int i = 0; i < 6; i++) {
        float* in1[] = {all_inputs[i]};
        test(&bl,in1, "gen/blow_out_%d_faust.txt",       i+1, 3); 
        test(&t, in1, "gen/turbulence_out_%d_faust.txt", i+1, 1);
        test(&v, in1, "gen/vortex_out_%d_faust.txt",     i+1, 1);

        // 2 inputs
        for (int j = 0; j < 6; j++) {
            float* in2[] = {all_inputs[i], all_inputs[j]};  
            test(&b,  in2, "gen/bernoulli_out_%d_faust.txt",   (i+1)*10+j+1, 3);
            test(&jd, in2, "gen/jetdrive_out_%d_faust.txt",    (i+1)*10+j+1, 2);
            test(&e,  in2, "gen/excitation_out_%d_faust.txt",  (i+1)*10+j+1, 2); 
            test(&r,  in2, "gen/receptivity_out_%d_faust.txt", (i+1)*10+j+1, 1);
            test(&res,in2, "gen/resonator_out_%d_faust.txt", (i+1)*10+j+1, 3);

            if (argc > 1) continue; 

            // 3 inputs
            for (int r = 0; r < 6; r++) {
        	float* in3[] = {all_inputs[i], all_inputs[j], all_inputs[r]};  
            	test(&s,  in3, "gen/sources_out_%d_faust.txt", (r+1)*100+(i+1)*10+j+1, 2);

		// 4 inputs
		for (int q = 0; q < 6; q++) {
        	    float* in4[] = {all_inputs[i], all_inputs[j], all_inputs[r], all_inputs[q]};  
            	    test(&jt,  in4, "gen/jet_out_%d_faust.txt", (q+1)*1000+(r+1)*100+(i+1)*10+j+1, 2);
                }
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
