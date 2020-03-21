***********************************************
*********             README          *********
***********************************************
Use export libraries below before running.
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../list/lib:./lib


This was the toughest homework so far. I encounter two challenges.
The first challenge was the use of stop_requested. This flag was not explained in details inthe text of the homework, but was in the strcuture definition. 
I completely forget about this flag, and was puzzled on how to stop consumers from consuming when all producers are done. Then, when I saw that flag I understood why it is needed.
The second challenge was debugging and reproducing of the failing test cases. Indeed, I had some random issues with one test case that would fail 1 in 100 times. 
So by simmulating this rare case - I run it for 10000 times:

[dmitryvengertsev@onyx p3]$ for i in {1..10000}; do ./pc 1000 10 8 8 1; done

I had the issue with one of the locks, fixed it.
Also run main test set for 10 times, and all were successfull, so I am confident that it works on all sorts of thread combinations.

[dmitryvengertsev@onyx p3]$ for i in {1..10}; do echo $i; backpack.sh; done 


1
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boidu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boidu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

2
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boidu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boidu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

3
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

4
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

5
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

6
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

7
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

8
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

9
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!

10
Building project....
cd wrapper-library/; make
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make[1]: Nothing to be done for `all'.
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
cd wrapper-library/; make install
make[1]: Entering directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
install --mode=444 -C ThreadsafeBoundedList.h ..//include
install --mode=444 -C libthreadsafe-mylib.so ..//lib
install --mode=444 -C libthreadsafe-mylib.a ..//lib
make[1]: Leaving directory `/home/DMITRYVENGERTSEV/cs552/backpack/DmitryVengertsev@u.boisestate.edu/DmitryVengertsev@u.boisestate.edu/backpack/cs453-1-s20/p3/wrapper-library'
make: *** No rule to make target `pc-mq.o', needed by `pc-mq'.  Stop.

Running tests...this will take a few minutes

Backpack: all tests passed!





