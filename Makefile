CC=g++
CFLAGS_O3=-I. -O3 -std=c++0x
LEDALIB=/usr/local/LEDA
LEDAINCL=/usr/local/LEDA/incl

build: bin/main.o bin/preflow_push.o bin/all_pairs_min_cut.o bin/graph_gen.o bin/benchmark.o bin/leda_alg.o
	$(CC) $(CFLAGS_O3) -o bin/main bin/main.o bin/preflow_push.o bin/all_pairs_min_cut.o bin/graph_gen.o bin/benchmark.o bin/leda_alg.o -L$(LEDALIB) -lleda

build-visual: bin/visualize.o bin/preflow_push.o bin/all_pairs_min_cut_visual.o bin/graph_gen.o
	$(CC) $(CFLAGS_O3) -o bin/visualize bin/visualize.o bin/preflow_push.o bin/all_pairs_min_cut_visual.o bin/graph_gen.o

run:
	./bin/main

run-visual:
	./bin/visualize

clean:
	rm -f bin/*

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS_O3) -c src/main.cpp -o bin/main.o -I$(LEDAINCL)

bin/visualize.o: src/visualize.cpp
	$(CC) $(CFLAGS_O3) -c src/visualize.cpp -o bin/visualize.o

bin/preflow_push.o: src/preflow_push.cpp
	$(CC) $(CFLAGS_O3) -c src/preflow_push.cpp -o bin/preflow_push.o

bin/all_pairs_min_cut.o: src/all_pairs_min_cut.cpp
	$(CC) $(CFLAGS_O3) -c src/all_pairs_min_cut.cpp -o bin/all_pairs_min_cut.o

bin/all_pairs_min_cut_visual.o: src/all_pairs_min_cut.cpp
	$(CC) $(CFLAGS_O3) -c src/all_pairs_min_cut.cpp -o bin/all_pairs_min_cut_visual.o -DAPMC_VISUAL -Wno-unused-result

bin/graph_gen.o: src/graph_gen.cpp
	$(CC) $(CFLAGS_O3) -c src/graph_gen.cpp -o bin/graph_gen.o

bin/benchmark.o: src/benchmark.cpp
	$(CC) $(CFLAGS_O3) -c src/benchmark.cpp -o bin/benchmark.o -I$(LEDAINCL)

bin/leda_alg.o: src/leda_alg.cpp
	$(CC) $(CFLAGS_O3) -c src/leda_alg.cpp -o bin/leda_alg.o -I$(LEDAINCL)