#include <vector>

#include <sndfile.hh>
#include <iostream>
#include <cmath>
#include <stdio.h>

#include "Bernoulli.cpp"
#include "JetDrive.cpp"
#include "Tanh_table.cpp"
#include "Receptivity.cpp"
#include "MyFilter.cpp"
#include "Turbulence.cpp"
#include "Vortex.cpp"
#include "Blow.cpp"
#include "ADSR.cpp"
#include "SineWave.cpp"
#include "Generator.cpp"
#include "Envelope.cpp"
#include "Excitation.cpp"
#include "Resonator.cpp"
#include "Jet.cpp"
#include "Delay.cpp"
#include "DelayL.cpp"
#include "Filter.cpp"
#include "Sources.cpp"

#include "Instrmnt.cpp"
#include "Flauta.cpp"

#include "Stk.cpp"

#define SR       22050
#define SIZE     44100

int main() {
    double buffer[SIZE];    

    int format = SF_FORMAT_WAV | SF_FORMAT_DOUBLE;
    int channels = 1;
    int sampleRate = SR;

    double pitches[] = {70.0, 75.0, 80.0};
    for (int i = 0; i < 3; i++) {
        Stk::setSampleRate(22050.0);  
        Flauta fl;
        fl.noteOn(440.0, 1.0);
        for (int j = 0; j < SIZE; j++) {
            buffer[j] = fl.tick();
        }
        // TODO : set pitch

        // write wav
        char filename[30];
        sprintf(filename, "../../gen/flauta_%i_o.wav", i);
        SndfileHandle outfile(filename, SFM_WRITE, format, channels, sampleRate);
        if (!outfile) {
            return -1;
        }
        outfile.write(&buffer[0], SIZE);
    }
    return 0;
}
