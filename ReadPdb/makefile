readfile = myvector.o atoms.o mystring.o readfile.o

BINS = readfile.out

cc = gcc
CXX = g++ -std=c++11

CFLAGS += -03
CFLAGS += -std=c++11
CFLAGS += -pg -D_DEBUG -g -c -Wall

libs = -lm

all:$(BINS)

readfile.out: $(readfile)
	$(CXX)  $(readfile) -o $@ $(libs) 


clean:
	rm -f *.o
cleanall: clean
	rm -f $(BINS)
