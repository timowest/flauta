#include <vector>

#include <sndfile.hh>
#include <iostream>
#include <cmath>
#include <stdio.h>

//#include "dsp.h"
#include "bernoulli.cpp"
#include "jetdrive.cpp"
#include "receptivity.cpp"
#include "turbulence.cpp"
#include "vortex.cpp"

int main() {
    bernoulli b;   // 2 in, 3 out
    jetdrive jd;   // 2 in, 2 out
    receptivity r; // 3 in, 1 out
    turbulence t;  // 1 in, 1 out
    vortex v;      // 1 in, 1 out

    // TODO : configure dsp objects
    // TODO : wav in -> dsp -> wav out
}
