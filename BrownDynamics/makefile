brown = myvector.o brown.o
BINS = brown.out 

cc = gcc
CXX = g++ -std=c++11

CFLAGS += -03
CFLAGS += -std=c++11
CFLAGS += -pg -D_DEBUG -g -c -Wall

libs = -lm

all:$(BINS)

brown.out: $(brown)
	$(CXX)  $(brown) -o $@ $(libs) 


clean:
	rm -f *.o
cleanall: clean
	rm -f $(BINS)
