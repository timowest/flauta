// test for jet-component

import("../faust/excitation.dsp");
import("oscillator.lib");

// 3 in, 2 out
process(a,b,c) = jet(a,b,c,25);
