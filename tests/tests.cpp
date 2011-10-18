#include <sndfile.hh>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <math.h>
#include <cstdlib>

//#include "dsp.h"
#include "bernoulli.cpp"
#include "jetdrive.cpp"
#include "receptivity.cpp"
#include "turbulence.cpp"
#include "vortex.cpp"

#define SIZE 256

using namespace std;

void convert_line_to_floats(char* line, float* floats) {
    char *pch = strtok(line, " ");
    int counter = 0;
    for (; pch != NULL; floats++, counter++) {
        *floats = atof(pch);
        pch = strtok(NULL, " ");
    }
    // fill rest of array with last value
    float last_value = *(floats-1);
    for (int i = counter; i < SIZE; i++, floats++) {
        *floats = last_value;
    }
}

void convert_floats_to_out(float* floats, ofstream* out) {
    for (int i = 0; i < SIZE; i++) {
        (*out) << floats[i] << " ";
    }
    (*out) << "\n\n";
}

void test(dsp* processor, const char* in_file, const char* out_file, int in_count, int out_count);

int main() {
    bernoulli b;   // 2 in, 3 out
    jetdrive jd;   // 2 in, 2 out
    receptivity r; // 3 in, 1 out
    turbulence t;  // 1 in, 1 out
    vortex v;      // 1 in, 1 out
    
    test(&b,  "tests/bernoulli-in.txt",   "gen/bernoulli_out.txt",   2, 3);
    test(&jd, "tests/jetdrive-in.txt",    "gen/jetdrive_out.txt",    2, 3);
    test(&r,  "tests/receptivity-in.txt", "gen/receptivity_out.txt", 3, 1);
    test(&t,  "tests/turbulence-in.txt",  "gen/turbulence_out.txt",  1, 1);
    test(&v,  "tests/vortex-in.txt",      "gen/vortex_out.txt",      1, 1);

}

void test(dsp* processor, const char* in_file, const char* out_file, int in_count, int out_count) {
    float in1[SIZE],  in2[SIZE],  in3[SIZE];
    float out1[SIZE], out2[SIZE], out3[SIZE];
    float *inputs[] = {in1, in2, in3};
    float *outputs[] = {out1, out2, out3};

    char line[2048];

    // fill input buffers from file
    ifstream in(in_file);
    in.getline(line, 2048);
    convert_line_to_floats(line, in1);
    if (in_count > 1) {
        in.getline(line, 2048);
        convert_line_to_floats(line, in2);
    }
    if (in_count > 2) {
        in.getline(line, 2048);
        convert_line_to_floats(line, in3);
    }
    in.close();

    // process
    processor->init(44100);
    processor->compute(SIZE, inputs, outputs);

    // serialize outputs to file
    ofstream out(out_file);
    convert_floats_to_out(out1, &out);
    if (out_count > 1) convert_floats_to_out(out2, &out);
    if (out_count > 2) convert_floats_to_out(out3, &out);
    out.close();
}
