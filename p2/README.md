# 1. Details on the performance

[dmitryvengertsev@onyx p2]$ mergesort 1000000000 1 42
Sorting 1000000000 elements took 263.08 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 2 42
Sorting 1000000000 elements took 143.71 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 3 42
Sorting 1000000000 elements took 100.49 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 4 42
Sorting 1000000000 elements took 92.36 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 5 42
Sorting 1000000000 elements took 69.64 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 6 42
Sorting 1000000000 elements took 63.64 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 7 42
Sorting 1000000000 elements took 57.89 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 8 42
Sorting 1000000000 elements took 57.88 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 9 42
Sorting 1000000000 elements took 53.82 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 10 42
Sorting 1000000000 elements took 48.92 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 11 42
Sorting 1000000000 elements took 47.65 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 12 42
Sorting 1000000000 elements took 47.36 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 13 42
Sorting 1000000000 elements took 46.28 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 15 42
Sorting 1000000000 elements took 42.05 seconds.
[dmitryvengertsev@onyx p2]$ mergesort 1000000000 16 42
Sorting 1000000000 elements took 47.73 seconds.


# 2. Observations regarding the assignment

Initially I tried to implement threaded merge sort with the limited number of levels, but I had issues with passing several arguments to pthread_create function.
Therefore, I decided to write merge sort with the limited number of threads. I divided the whole array into array_parts and run each part on it's thread with a serial merge sort. When all the parts are sorted (checked with pthread_join), I merge the sorted parts.

