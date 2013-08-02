ALSA_GTK = `pkg-config --cflags --libs alsa` `pkg-config --cflags --libs gtk+-2.0`
JACK_GTK = `pkg-config --cflags --libs jack` `pkg-config --cflags --libs gtk+-2.0`
GTKMM = `pkg-config --cflags --libs gtkmm-2.4`
PAQ = `pkg-config --cflags --libs paq`
FAUST = -I/usr/local/lib/faust/
TESTS = gen/blow.cpp gen/bernoulli.cpp gen/excitation.cpp gen/jetdrive.cpp gen/receptivity.cpp gen/turbulence.cpp gen/vortex.cpp gen/jet.cpp gen/sources.cpp gen/resonator.cpp

# tested with Faust 0.9.58

standalone:
	faust -a alsa-gtk.cpp -double faust/flauta.dsp > gen/flauta.cpp
	g++ -Wall gen/flauta.cpp $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o flauta.out

jack:
	faust -a jack-gtk.cpp -double faust/flauta.dsp > gen/flauta.cpp
	g++ -Wall gen/flauta.cpp $(JACK_GTK) $(FAUST) $(CFLAGS) -lm -o flauta.out

caqt:  gen
	faust2caqt faust/flauta.dsp
	mv faust/flauta.app gen

gen:
	mkdir gen

gen/%.cpp: tests/%-test.dsp
	faust -a minimal.cpp -double -cn $(patsubst gen/%.cpp,%,$@) $< > $@

wavgen: 
	faust -a minimal.cpp -double -cn flauta faust/flauta.dsp > gen/flauta_min.cpp
	g++ -Wall gen/wavgen.cpp $(FAUST) -lm -lsndfile -Igen/ -Isrc/ -o wavgen.out
	./wavgen.out

svg:
	rm -rf faust/*-svg    
	faust -svg -sn faust/flauta.dsp
	#faust -svg -sn faust/resonator.dsp

impedance:
	faust -a plot.cpp -o gen/resonator.cpp faust/resonator-test.dsp
	g++ -Wall -O3 -lm  gen/resonator.cpp -o resonator

svg2:
	faust -svg -sn faust/resonator-test.dsp

clean:
	rm -rf *.so *.out *.wav gen/* faust/*-svg alsa-gtk

