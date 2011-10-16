#include <vector>

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
using namespace std;

#define SIZE 128

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

int main() {
    bernoulli b;   // 2 in, 3 out
    jetdrive jd;   // 2 in, 2 out
    receptivity r; // 3 in, 1 out
    turbulence t;  // 1 in, 1 out
    vortex v;      // 1 in, 1 out
    
    b.init(44100);
    jd.init(44100);
    r.init(44100);
    t.init(44100);
    v.init(44100);

    float in1[SIZE],  in2[SIZE],  in3[SIZE];
    float out1[SIZE], out2[SIZE], out3[SIZE];
    float *inputs[] = {in1, in2, in3};
    float *outputs[] = {out1, out2, out3};

    char line[2048];

    // bernoulli
    ifstream bernoulli_in("tests/bernoulli-in.txt");
    bernoulli_in.getline(line, 2048);
    convert_line_to_floats(line, in1);
    bernoulli_in.getline(line, 2048);
    convert_line_to_floats(line, in2);
    bernoulli_in.close();
    b.compute(SIZE, inputs, outputs);

    ofstream bernoulli_out("gen/bernoulli_out.txt");
    convert_floats_to_out(out1, &bernoulli_out);
    convert_floats_to_out(out2, &bernoulli_out);
    convert_floats_to_out(out3, &bernoulli_out);
    bernoulli_out.close();

    /*for (int i = 0; i < SIZE; i++) {
        cout << in1[i] << " = " << out1[i] << ", " << out2[i] << ", " << out3[i] << endl;
    }*/

    // jetdrive
    // TODO

    // receptivity
    // TODO

    // turbulence
    // TODO

    // vortex
    // TODO
}


