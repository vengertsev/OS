
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

// function prototypes
int check_if_sorted(int A[], int n);
void generate_random_array(int A[], int n, int seed);
void serial_mergesort(int A[], int p, int r); 
void *parallel_mergesort(void *arg); 
void merge_array_parts(int A[], int parts_cnt, int agg);

void merge(int A[], int p, int q, int r);
void insertion_sort(int A[], int p, int r);
double getMilliSeconds(void);

// global variables 
int *A;
int num_threads; 
int elems_per_thread;
int offset;
int n;


/*
 * generate_random_array(int A[], int n, int seed):
 *
 * description: Generate random integers in the range [0,RANGE]
 *              and store in A[1..n]
 */

#define RANGE 1000000

void generate_random_array(int A[], int n, int seed)
{
    int i;

	srandom(seed);
    for (i=0; i<n; i++)
        A[i] = random()%RANGE;
}


/*
 * check_if_sorted(int A[], int n):
 *
 * description: returns TRUE if A[1..n] are sorted in nondecreasing order
 *              otherwise returns FALSE
 */     

int check_if_sorted(int A[], int n) 
{
	int i=0;

	for (i=1; i<n; i++) {
		if (A[i-1] > A[i]) {
			return FALSE;
		}
	}
	return TRUE;
}


int main(int argc, char **argv) {
	
	if (argc < 3) { // there must be at least two command-line argument
			fprintf(stderr, "Usage: %s <input size> <levels_cnt> [<seed>] \n", argv[0]);
			exit(1);
	}
 
	n = atoi(argv[1]);
  int thread_cnt = atoi(argv[2]);
	int seed = 1;
	if (argc == 4)
		seed = atoi(argv[3]);
		
	 A = (int *) malloc(sizeof(int) * (n+1)); // n+1 since we are using A[1]..A[n]		

	 // generate random input    
   generate_random_array(A, n, seed);

   long i;
	
	 double start_time;
	 double sorting_time;

   num_threads = thread_cnt; 
   elems_per_thread = n/num_threads;
   offset = n % num_threads;


	 // sort the input (and time it)
	 start_time = getMilliSeconds();
 
   pthread_t threads[num_threads];

   // create threads
   for ( i = 0; i < num_threads; i ++) {
        int rc = pthread_create(&threads[i], NULL, parallel_mergesort, (void *)i);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
   }
   
   // wait till threads are done 
   for(i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
   }

  merge_array_parts(A, num_threads, 1);

  sorting_time = getMilliSeconds() - start_time;
	
	// print results if correctly sorted otherwise cry foul and exit
	if (check_if_sorted(A,n)) {
		printf("Sorting %d elements took %4.2lf seconds.\n", n,  sorting_time/1000.0);
	} else { 
		printf("%s: sorting failed!!!!\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS); 
} 


void *parallel_mergesort(void *arg)
{
    int thread_id = (long)arg;
    int p = thread_id * (elems_per_thread);
    int r = (thread_id + 1) * (elems_per_thread) - 1;
    if (thread_id == num_threads - 1) {
        r += offset;
    }
    
    int q = p + (r - p) / 2;   
    if (p < r) {
        serial_mergesort(A, p, r);
        serial_mergesort(A, p + 1, r);
        merge(A, p, q, r);
    }
    return NULL;
}


void merge_array_parts(int A[], int parts_cnt, int agg) {  
    int i;
    for(i = 0; i < parts_cnt; i = i + 2) {
        int p = i * (elems_per_thread*agg);
        int r = ((i + 2) * elems_per_thread*agg) - 1;
        int q = p + (elems_per_thread*agg) - 1;
        if (r >= n) {
            r = n - 1;
        }
        merge(A, p, q, r);
    }
    if (parts_cnt / 2 >= 1) {
        merge_array_parts(A, parts_cnt/2,  2*agg);
    }
}
