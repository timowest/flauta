ALSA_GTK = `pkg-config --cflags --libs alsa` `pkg-config --cflags --libs gtk+-2.0`
GTKMM = `pkg-config --cflags --libs gtkmm-2.4`
PAQ = `pkg-config --cflags --libs paq`
FAUST = -I/usr/local/lib/faust/

standalone: 
	faust -fun -vec -a alsa-gtk.cpp faust/flauta.dsp > gen/flauta.cpp
	g++ -Wall gen/flauta.cpp  $(ALSA_GTK) $(FAUST) $(CFLAGS) -lm -o flauta.out

svg:
	rm -rf faust/*-svg    
	faust -svg -sn faust/flauta.dsp

clean:
	rm -rf *.so *.out *.wav gen/* faust/*-svg alsa-gtk 
