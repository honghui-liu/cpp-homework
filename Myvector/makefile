myvector = myvector.o main.o

BINS = myvector.out

cc = gcc
CXX = g++ -std=c++11

CFLAGS += -03
CFLAGS += -std=c++11
CFLAGS += -pg -D_DEBUG -g -c -Wall

libs = -lm

all:$(BINS)

myvector.out: $(myvector)
	$(CXX)  $(myvector) -o $@ $(libs) 


clean:
	rm -f *.o
cleanall: clean
	rm -f $(BINS)
