# Project 1/Shell mydash {#mainpage}

* Author: Dmitry Vengertsev
* Class: CS453 [Operating Systems] Section #num

See CONTENTS.md for a description of the p1 starter files supplied to you in this folder. You
should complete the template below with your own words to finish this README file.

## Overview
The program implements a simple shell that can perform several critical commands like "cd", and other
linux commands with flags using kernel methods like execvp() - to execute commands with flags,
and fork() - to create child process. Shell also enables outcomplete and history.

## Manifest

1. Makefile - contains details on how to compline and link the programm
2. mydash.c - source code for mydash
3. mydash.h - header file for mydash
4. README.md - this file
5. valgrind.supp - Valgrind memory leakage and errors suppression file


## Building the project

Preform the git pull in the directory at onyx.
Run >> make
Run >> mydash
To get the version of the shell run >> mydash -v 


## Features and usage

1. The main feature of the program is the ability to execute shell commands with the attributes, similarly to the bash shell.
One can execute "ls -all" in mydash and get the results like in bash. If the number of arguments in the command more than allowed 2048, it will print an error message.

mydash>ls -all
total 176
drwxr-xr-x. 5 dmitryvengertsev 491339     17 Jan 28 22:54 .
drwxr-xr-x. 3 dmitryvengertsev 491339      3 Jan 28 22:25 ..
-rw-r--r--. 1 dmitryvengertsev 491339      0 Jan 25 23:16 ”
-rwxr-xr-x. 1 dmitryvengertsev 491339   3743 Jan 19 02:08 backpack.sh
-rw-r--r--. 1 dmitryvengertsev 491339   2337 Jan 19 02:08 CONTENTS.md
-rw-r--r--. 1 dmitryvengertsev 491339 105540 Jan 19 02:08 doxygen-config
-rw-r--r--. 1 dmitryvengertsev 491339    280 Jan 26 00:12 Makefile
-rwxr-xr-x. 1 dmitryvengertsev 491339  27208 Jan 28 22:54 mydash
drwxr-xr-x. 2 dmitryvengertsev 491339     16 Jan 28 22:54 mydash-src
-rw-r--r--. 1 dmitryvengertsev 491339    233 Jan 28 22:21 .nfs0000000005186d4a00007d12
drwxr-xr-x. 2 dmitryvengertsev 491339      5 Jan 19 02:08 other-progs
-rw-r--r--. 1 dmitryvengertsev 491339    710 Jan 19 02:08 p1-rubric.txt
-rw-r--r--. 1 dmitryvengertsev 491339   2404 Jan 28 22:48 README.md
drwxr-xr-x. 2 dmitryvengertsev 491339      7 Jan 19 02:08 smoketest-files
-rw-r--r--. 1 dmitryvengertsev 491339    609 Jan 28 22:25 smoke_test_out.txt
-rw-r--r--. 1 dmitryvengertsev 491339    419 Jan 19 02:08 TestCases
-rw-r--r--. 1 dmitryvengertsev 491339    598 Jan 28 22:44 valgrind.supp

2. mydash provides auto complete capabilities of the filenames by using 'Tab' key
mydash> ls Te
click Tab
mydash>ls TestCases

3. mydash shell uses uses up arrow, down arrow, left arrow, right arrow keys to access the history of commands
typed in by the user.

4. mydash shell  ignores empty commands or commands that consist only of spaces.

5. mydash shell terminates normally on receiving the end of input (ctrl+D) or by using "exit"

6. mydash shell understands change directiry command "cd". If the directory is not provided, it will change to home directory.

7. one can setup custom prompt name using environment variable DASH_PROMPT. If the variable is not defined, prompt "mydash>" will be used. 

8. by running >> mydash -v, you will get a version that is based on git SHA commit 
[dmitryvengertsev@onyx p1]$ mydash -v
mydash> Version 1: Revision 4ef360 (author: Dmitry Vengertsev DmitryVengertsev@u.boisestate.edu)

9. on successful exit mydash shell returns 0, else positive value.


## Testing

1. I run the basic provided smoke tests sucessfully with the following results:
>> backpack.sh   smoke_test_out.txt

START: Testing normal command execution
  END: Testing normal command execution
START: Testing use of readline for filename completion and history
  END: Testing use of readline
START: Testing the empty command
  END: Testing the empty command
START: Testing EOF
  END: Testing EOF
START: Testing exit
  END: Testing exit
START: Testing cd
  END: Testing cd 
START: Testing version
  END: Testing version

Valgrind was NOT run, make sure and test with valgrind as you progress further
PASSED: Basic smoke tests passed! Please test for more functionality as you continue.

2. Morevover, I run additional TestCases provided in TestCases file, and I appended it with few more test cases. 
For example, cat, wc commands testing, I also tested all sort of different spaces and tabs combinations for the empty line.
Also I added testing for the number of arguments provided to command when exceeding allowed 2048, it will print error.

3. Moreover, I tested external commands for ctr+D, and for usage of the variable for DASH_PROMPT and custom prompt setup, also HOME directory setup

### Valgrind

1. I run Valgrind the following way:

>> valgrind --leak-check=full ./mydash

2. But I got quite a bit of erros related to readline, that are out of my control so I suppressed them using:

>> valgrind --leak-check=full  --suppressions=valgrind.supp ./mydash

3. I ended up with these unfixed leaks, couldn't find the root cause:
==58103== 17 bytes in 5 blocks are definitely lost in loss record 8 of 45
==58103==    at 0x4C29E63: malloc (vg_replace_malloc.c:309)
==58103==    by 0x401434: parseInput (parsing.c:21)
==58103==    by 0x400D61: main (mydash.c:59)

### Known Bugs

There are few potential memory leaks like described in the previous section.

## Reflection and Self Assessment

The main struggle for me was the use of execvp() function.
1. execvp() was not providign any output, then I found a blog giving a simple example, and I understood that
I didn't use the right format, used *char instead of **char. 
2. When previous issue was fixed, I was encounturing a new inconsistent error - when I do "ls" first and then "cd", 
the shell would crush. Appending command arguments to execvp with NULL helped to solve this issue.
3. then by doing testing I found a bug of forgeting to include "readline.h"

## Sources used

I didn't use any source outside of the provided starting code.
