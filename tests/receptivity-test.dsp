// test for receptivity-component

import("../faust/excitation.dsp");
import("oscillator.lib");

// 2 in, 1 out
process(a,b) = receptivity(a,b,25);
