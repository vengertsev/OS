/*
 * booga.c -- the booga char module
 * This example shows how to use a semaphore to avoid race conditions
 * in updating a global data structure inside a driver.
 */
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/version.h> /* printk() */
#include <linux/init.h>  /*  for module_init and module_cleanup */
#include <linux/slab.h>  /*  for kmalloc/kfree */
#include <linux/fs.h>     /* everything... */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/sched.h>
#include <linux/proc_fs.h>	/* for the proc filesystem */
#include <linux/seq_file.h>
#include "booga.h"        /* local definitions */
#include <linux/random.h>
#include <linux/uaccess.h> /* will need for __copy_to_user() */


static int booga_major =   BOOGA_MAJOR;

struct booga_dev {
  char *data;
  unsigned int booga_minor; /*minor number */
  unsigned int usage;  /* lock the device while using it*/
} mydata;


static int booga_nr_devs = BOOGA_NR_DEVS;    /* number of bare booga devices */
module_param(booga_major, int, 0);
module_param(booga_nr_devs, int, 0);
MODULE_AUTHOR("Dmitry Vengertsev");
MODULE_LICENSE("GPL v2");

static booga_stats *booga_device_stats;
static struct proc_dir_entry* booga_proc_file;

static ssize_t booga_read (struct file *, char *, size_t , loff_t *);
static ssize_t booga_write (struct file *, const char *, size_t , loff_t *);
static int booga_open (struct inode *, struct file *);
static int booga_release (struct inode *, struct file *);
static int booga_proc_open(struct inode *inode, struct file *file);


/*  The different file operations */
/* The syntax you see below is an extension to gcc. The prefered */
/* way to init structures is to use C99 Taged syntax */
/* static struct file_operations booga_fops = { */
/* 		    .read    =       booga_read, */
/* 			.write   =       booga_write, */
/* 			.open    =       booga_open, */
/* 			.release =       booga_release */
/* }; */
/*  This is where we define the standard read,write,open and release function */
/*  pointers that provide the drivers main functionality. */
static struct file_operations booga_fops = {
		    read:       booga_read,
			write:      booga_write,
			open:       booga_open,
			release:    booga_release,
};

/* The file operations struct holds pointers to functions that are defined by */
/* driver impl. to perform operations on the device. What operations are needed */
/* and what they should do is dependent on the purpose of the driver. */
static const struct file_operations booga_proc_fops = {
		.owner	= THIS_MODULE,
		.open	= booga_proc_open,
		.read	= seq_read,
		.llseek	= seq_lseek,
		.release	= single_release,
};

/*
 * Open and close
 */
static int booga_open (struct inode *inode, struct file *filp)
{
		int num = NUM(inode->i_rdev);
        mydata.booga_minor =  num;
		
        if (num >= booga_nr_devs) return -ENODEV;

		filp->f_op = &booga_fops;

		/* need to protect this with a semaphore if multiple processes
		   will invoke this driver to prevent a race condition */
		if (down_interruptible (&booga_device_stats->sem))
				return (-ERESTARTSYS);

        if (num == 0) {
          booga_device_stats->num_open0++;
        } else if (num == 1) {
          booga_device_stats->num_open1++;
        } else if (num == 2) {
          booga_device_stats->num_open2++;
        } else if (num == 3) {
          booga_device_stats->num_open3++;
        }

		up(&booga_device_stats->sem);

		try_module_get(THIS_MODULE);
		return 0;          /* success */
}

static int booga_release (struct inode *inode, struct file *filp)
{
		/* need to protect this with a semaphore if multiple processes
		   will invoke this driver to prevent a race condition */
		if (down_interruptible (&booga_device_stats->sem))
				return (-ERESTARTSYS);

		up(&booga_device_stats->sem);

		module_put(THIS_MODULE);
		return 0;
}

/*
 * Data management: read and write
 */

static ssize_t booga_read (struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
		printk("<1>booga_read invoked.\n");

		char randval;
        get_random_bytes(&randval, 1);
        unsigned int choice = (randval & 0x7F) % 4; /* bitwise and to guarantee positive number*/
        printk("choice = %u\n", randval);
		/* need to protect this with a semaphore if multiple processes
		   will invoke this driver to prevent a race condition */

	   printk("count=%d\n",count);
       char *  data;
       data = (char *) kmalloc (sizeof(char)*(count+1),GFP_KERNEL); /* have to use malloc type function because need to allocate data on heap for big cases not on stack, have to use kmalloc to allocate memory on kernel.*/
       char phrase[20];
       int phrase_size; 

       if (choice%4 == 0) {
         phrase_size = 14;
         strcpy(phrase, "booga! booga! ");
       } else if (choice%4 == 1) {
         phrase_size = 16;
         strcpy(phrase, "googoo! gaagaa! ");        
       } else if (choice%4 == 2) {
         phrase_size = 12;
         strcpy(phrase, "neka! maka! ");        
       } else if (choice%4 == 3) {
         phrase_size = 14;
         strcpy(phrase, "wooga! wooga! ");
       }


       if (count > 0) {
           unsigned long i;
           unsigned long j=0;
           for (i=0; i< count; i++) {
               j = i % phrase_size;
               data[i]=phrase[j];
           }
       }
 

        if (down_interruptible (&booga_device_stats->sem))
				return (-ERESTARTSYS);
        if (count > 0) {
          __copy_to_user(buf, data, count);
          kfree(data);


         if (choice%4 == 0) {
           booga_device_stats->num_booga++;
         } else if (choice%4 == 1) {
           booga_device_stats->num_googa++;
         } else if (choice%4 == 2) {
           booga_device_stats->num_neka++;
         } else if (choice%4 == 3) {
           booga_device_stats->num_wooga++;
         }
       }

        booga_device_stats->bytes_read+=count;
		up(&booga_device_stats->sem);

		return count;
}

static ssize_t booga_write (struct file *filp, const char *buf, size_t count , loff_t *f_pos)
{
		printk("<1>booga_write invoked.\n");
        // on /dev/booga3 writing is not allowed
        if (mydata.booga_minor == 3) {
            count = 0;
		    kill_pid(find_vpid(current->pid), SIGTERM, 1);	
        }

        /* need to protect this with a semaphore if multiple processes
		   will invoke this driver to prevent a race condition */
		if (down_interruptible (&booga_device_stats->sem))
				return (-ERESTARTSYS);
		
        booga_device_stats->bytes_written+=count;

        up(&booga_device_stats->sem);
		return count; // pretend that count bytes were written
}

static void init_booga_device_stats(void)
{
		booga_device_stats->bytes_read=0;
        booga_device_stats->bytes_written=0;
        booga_device_stats->num_open0=0;
        booga_device_stats->num_open1=0;
        booga_device_stats->num_open2=0;
        booga_device_stats->num_open3=0;
        booga_device_stats->num_booga=0;
        booga_device_stats->num_googa=0;
        booga_device_stats->num_neka=0;
        booga_device_stats->num_wooga=0;

		sema_init(&booga_device_stats->sem, 1);
}

static int booga_proc_show(struct seq_file *m, void *v)
{
        seq_printf(m, "bytes read  = %ld \n", booga_device_stats->bytes_read);
        seq_printf(m, "bytes written  = %ld \n", booga_device_stats->bytes_written); 
	    seq_printf(m, "number of opens: \n");
        seq_printf(m, "  /dev/booga0 = %ld times\n", booga_device_stats->num_open0); 
        seq_printf(m, "  /dev/booga1 = %ld times\n", booga_device_stats->num_open1); 
        seq_printf(m, "  /dev/booga2 = %ld times\n", booga_device_stats->num_open2); 
        seq_printf(m, "  /dev/booga3 = %ld times\n", booga_device_stats->num_open3); 
        seq_printf(m, "strings output \n"); 
        seq_printf(m, "  booga! booga! = %ld times\n", booga_device_stats->num_booga); 
        seq_printf(m, "  googoo! gaagaa! = %ld times\n", booga_device_stats->num_googa); 
        seq_printf(m, "  neka! maka! = %ld times\n", booga_device_stats->num_neka);
        seq_printf(m, "  wooga! wooga! = %ld times\n", booga_device_stats->num_wooga);
 
		return 0;
}


static int booga_proc_open(struct inode *inode, struct file *file)
{
		return single_open(file, booga_proc_show, NULL);
}


static __init int booga_init(void)
{
		int result;

		/*
		 * Register your major, and accept a dynamic number
		 */
		result = register_chrdev(booga_major, "booga", &booga_fops);
		if (result < 0) {
				printk(KERN_WARNING "booga: can't get major %d\n",booga_major);
				return result;
		}
		if (booga_major == 0) booga_major = result; /* dynamic */
		printk("<1> booga device driver version 4: loaded at major number %d\n", booga_major);

		booga_device_stats = (booga_stats *) kmalloc(sizeof(booga_stats),GFP_KERNEL);
		if (!booga_device_stats) {
				result = -ENOMEM;
				goto fail_malloc;
		}
		init_booga_device_stats();

		/* We assume that the /proc/driver exists. Otherwise we need to use proc_mkdir to
		 * create it as follows: proc_mkdir("driver", NULL);
		 */
		booga_proc_file = proc_create("driver/booga", 0, NULL, &booga_proc_fops);
		if (!booga_proc_file)  {
				result = -ENOMEM;
				goto fail_malloc;
		}

		return 0;

fail_malloc:
		unregister_chrdev(booga_major, "booga");
		return  result;
}



static __exit  void booga_cleanup(void)
{
		remove_proc_entry("driver/booga", NULL /* parent dir */);
		kfree(booga_device_stats);
		unregister_chrdev(booga_major, "booga");
		printk("<1> booga device driver version 4: unloaded\n");
}


module_init(booga_init);
module_exit(booga_cleanup);

/* vim: set ts=4: */

