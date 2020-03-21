
CC=gcc
CFLAGS=-g -O2 -std=gnu89 -Wall -Wpointer-arith -Wstrict-prototypes -I. 
# specify libraries to compile below, e.g. -lm (for the math library) 
LIBS=-lpthread

mergesort: mergesortTest.o mergesort.o timing.o 
	$(CC) $(CPPFLAGS)  mergesortTest.o mergesort.o timing.o $(LIBS) -o mergesort

clean:
	/bin/rm -f *.o mergesort
