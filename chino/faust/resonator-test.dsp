import("resonator.dsp");


reso = res~(_,lossesFilter) : (!,!,_,_) : calc : (!,!,_) ;

process = 1-1' : reso ;
