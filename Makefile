ALSA_GTK = `pkg-config --cflags --libs alsa` `pkg-config --cflags --libs gtk+-2.0`
GTKMM = `pkg-config --cflags --libs gtkmm-2.4`
PAQ = `pkg-config --cflags --libs paq`
FAUST = -I/usr/local/lib/faust/
TESTS = gen/blow.cpp gen/bernoulli.cpp gen/excitation.cpp gen/jetdrive.cpp gen/receptivity.cpp gen/turbulence.cpp gen/vortex.cpp gen/jet.cpp gen/sources.cpp

gen/flauta.cpp:
	faust -a alsa-gtk.cpp -double faust/flauta.dsp > gen/flauta.cpp

gen/%.cpp: tests/%-test.dsp
	faust -a minimal.cpp -double -cn $(patsubst gen/%.cpp,%,$@) $< > $@

standalone: gen/flauta.cpp 
	g++ -Wall gen/flauta.cpp  $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o flauta.out

compare: $(TESTS)
	g++ -Wall -fpermissive tests/tests.cpp $(FAUST) -lm -Igen/ -Isrc/ -o tests.out
	./tests.out
	cd orig/modules;make clean standalone;cd ../..
	python compare.py

svg:
	rm -rf faust/*-svg    
	faust -svg -sn faust/flauta.dsp

clean:
	rm -rf *.so *.out *.wav gen/* faust/*-svg alsa-gtk 
