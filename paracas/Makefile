ALSA = `pkg-config --cflags --libs alsa`
JACK = `pkg-config --cflags --libs jack` 
GTK = `pkg-config --cflags --libs gtk+-2.0`
SC = `pkg-config --cflags libscsynth`
FAUST = -I/usr/local/lib/faust/
TESTS = gen/blow.cpp gen/bernoulli.cpp gen/excitation.cpp gen/jetdrive.cpp gen/receptivity.cpp gen/turbulence.cpp gen/vortex.cpp gen/jet.cpp gen/sources.cpp gen/resonator.cpp

# tested with Faust 0.9.58

alsa-gtk:
	faust -a alsa-gtk.cpp -double faust/flauta.dsp > gen/flauta.cpp
	g++ -Wall gen/flauta.cpp $(ALSA) $(GTK) $(FAUST) $(CFLAGS) -lm -o flauta.out

jack-gtk:
	faust2jack faust/flauta.dsp
	mv faust/flauta gen
	
jack-qt:	
	faust2jaqt faust/flauta.dsp
	mv faust/flauta gen
	
puredata:	
	faust2puredata faust/flauta.dsp
	mv faust/flauta~.pd_linux gen
	
msp:
	faust2msp faust/flauta.dsp # FIXME
	
supercollider:	
	faust2supercollider faust/flauta.dsp
	mv faust/flauta.sc gen
	mv faust/flauta.so gen	
	
ca-qt: gen
	faust2caqt faust/flauta.dsp
	mv faust/flauta.app gen

gen:
	mkdir gen

gen/%.cpp: tests/%-test.dsp
	faust -a minimal.cpp -double -cn $(patsubst gen/%.cpp,%,$@) $< > $@

impedance:
	faust -a plot.cpp -o gen/resonator.cpp faust/resonator-test.dsp
	g++ -Wall -O3 -lm  gen/resonator.cpp -o resonator

wavgen: 
	faust -a minimal.cpp -double -cn flauta faust/flauta.dsp > gen/flauta_min.cpp
	g++ -Wall tests/wavgen.cpp $(FAUST) -lm -lsndfile -Igen/ -Isrc/ -o wavgen.out
	./wavgen.out

svg:
	rm -rf faust/*-svg    
	faust -svg -sn faust/flauta.dsp
	#faust -svg -sn faust/resonator.dsp

clean:
	rm -rf *.so *.out *.wav gen/* faust/*-svg alsa-gtk

