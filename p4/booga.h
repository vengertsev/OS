
#ifndef __BOOGA_H
#define __BOOGA_H
/*
 * booga.h -- definitions for the char module
 *
 */
#ifndef BOOGA_MAJOR
#define BOOGA_MAJOR 0   /* dynamic major by default */
#endif

#ifndef BOOGA_NR_DEVS
#define BOOGA_NR_DEVS 4    /* booga0 through booga3 */
#endif
/*
 * Split minors in two parts
 */
#define TYPE(dev)   (MINOR(dev) >> 4)  /* high nibble */
#define NUM(dev)    (MINOR(dev) & 0xf) /* low  nibble */

/*
 * The different configurable parameters
 */
struct booga_stats {
        long int bytes_read;
        long int bytes_written;
        long int num_open0;
        long int num_open1;
        long int num_open2;
        long int num_open3;
        long int num_booga;
        long int num_googa;
        long int num_neka;
        long int num_wooga;
        /*
	long int num_open;
	long int num_read; 
	long int num_write; 
	long int num_close;
        */ 
	struct semaphore sem;
};
typedef struct booga_stats booga_stats;

/*extern example_stats Example_Device_Stats;*/

#endif /* __BOOGA_H */
