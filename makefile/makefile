rwdist = myvector.o rwdist.o
rwtime = myvector.o rwtime.o
BINS = rwdist.out rwtime.out

cc = gcc
CXX = g++ -std=c++11

CFLAGS += -03
CFLAGS += -std=c++11
CFLAGS += -pg -D_DEBUG -g -c -Wall

libs = -lm

all:$(BINS)

rwdist.out: $(rwdist)
	$(CXX)  $(rwdist) -o $@ $(libs) 
rwtime.out: $(rwtime)
	$(CXX)  $(rwtime) -o $@ $(libs) 

clean:
	rm -f *.o
cleanall: clean
	rm -f $(BINS)
