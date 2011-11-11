// test for receptivity-component

import("../faust/excitation.dsp");
import("oscillator.lib");

// 2 in, 1 out
process = receptivity(_,_,0.5);
