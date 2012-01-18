ALSA_GTK = `pkg-config --cflags --libs alsa` `pkg-config --cflags --libs gtk+-2.0`
GTKMM = `pkg-config --cflags --libs gtkmm-2.4`
PAQ = `pkg-config --cflags --libs paq`
FAUST = -I/usr/local/lib/faust/
TESTS = gen/blow.cpp gen/bernoulli.cpp gen/excitation.cpp gen/jetdrive.cpp gen/receptivity.cpp gen/turbulence.cpp gen/vortex.cpp gen/jet.cpp gen/sources.cpp

# temporary
gen/resonator.cpp:
	faust -a alsa-gtk.cpp -double faust/resonator.dsp > gen/resonator.cpp

# temporary
resonator: gen/resonator.cpp 
	g++ -Wall gen/resonator.cpp $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o resonator.out

gen/flauta.cpp:
	faust -a alsa-gtk.cpp -double faust/flauta.dsp > gen/flauta.cpp

gen/%.cpp: tests/%-test.dsp
	faust -a minimal.cpp -double -cn $(patsubst gen/%.cpp,%,$@) $< > $@

standalone: gen/flauta.cpp 
	g++ -Wall gen/flauta.cpp $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o flauta.out

compare: $(TESTS)
	g++ -Wall -fpermissive tests/tests.cpp -g $(FAUST) -lm -Igen/ -Isrc/ -o tests.out
	./tests.out
	cd orig/modules;make clean standalone;cd ../..
	python compare.py

compare_fast: $(TESTS)
	g++ -Wall -fpermissive tests/tests.cpp -g $(FAUST) -lm -Igen/ -Isrc/ -o tests.out
	./tests.out fast
	cd orig/modules;make clean fast;cd ../..
	python compare.py fast

svg:
	rm -rf faust/*-svg    
	faust -svg -sn faust/flauta.dsp
	faust -svg -sn faust/resonator.dsp

clean:
	rm -rf *.so *.out *.wav gen/* faust/*-svg alsa-gtk

