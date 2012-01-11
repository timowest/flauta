// test for jet-component

import("../faust/excitation.dsp");
import("oscillator.lib");

// 4 in, 2 out
process(a,b,c,d) = jet(a,b,25,d);
