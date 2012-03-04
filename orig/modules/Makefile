standalone: 
	g++ -Wall -g -fpermissive FullTest.cpp -lm -I../stk/ -o FullTest.out
	./FullTest.out

fast:
	g++ -Wall -g -fpermissive FullTest.cpp -lm -I../stk/ -o FullTest.out
	./FullTest.out fast

wavgen: 
	g++ -Wall -g -fpermissive wavgen.cpp -lm -I../stk/ -lsndfile -o wavgen.out
	./wavgen.out
	
clean:
	rm -rf *.so *.out *.wav /gen/*.txt
