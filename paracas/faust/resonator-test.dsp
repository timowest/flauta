import("resonator.dsp");

reso = res~(_,_,lossesFilter) : (!,!,!,_,_) : calc ;

process = 1-1' : reso ;
