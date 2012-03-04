#include <vector>

#include <sndfile.hh>
#include <iostream>
#include <cmath>
#include <stdio.h>

#include "flauta_min.cpp"    
#include "collector-ui.h"

#define SR       22050
#define SIZE     44100

int main() {
    float buffer_l[SIZE], buffer_r[SIZE];    
    float *outputs[] = {buffer_l, buffer_r};   

    int format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    int channels = 1;
    int sampleRate = SR;

    float pitches[] = {70.0, 75.0, 80.0};
    for (int i = 0; i < 3; i++) {
        CollectorUI ui;
        flauta fl;
        fl.init(SR); 
        fl.buildUserInterface(&ui); 

        *(ui.getZone("h2_gate")) = 1.0f; // note on 
        *(ui.getZone("h2_res_Note")) = pitches[i];
        fl.compute(SIZE, 0, outputs);

        // write wav
        char filename[30];
        sprintf(filename, "gen/flauta_%i_f.wav", i);
        SndfileHandle outfile(filename, SFM_WRITE, format, channels, sampleRate);
        if (!outfile) {
            return -1;
        }
        outfile.write(&buffer_l[0], SIZE);
    }
    return 0;
}
