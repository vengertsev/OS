
Test plan:

#================================
# 1. Testing driver functionality
#================================
sudo ./booga-test1.sh

Using this test I found an issues related to the cases with number of characters > 10,000. 
VM crashed on bigger numbers of characters, the root cause was that I used array on stack
instead of heap, after usign kmalloc() on kernel side, the issue was fixed.

All runs executed correctly. I am not typing the read commands output here since it is very extensive.
I output the results of write command only:

Attempting to write to booga device
Wrote 1000 bytes.
Attempting to write to booga device
Wrote 1000 bytes.
Attempting to write to booga device
Wrote 1000 bytes.
Attempting to write to booga device
./booga-test1.sh: line 19: 24442 Terminated              ./test-booga 3 1000 w
 booga returned 0 characters
1
 booga returned 1 characters
2
 booga returned 2 characters
3
 booga returned 10 characters
11
 booga returned 10 characters
11
 booga returned 100 characters
101
 booga returned 1000 characters
1001
 booga returned 10000 characters
10001
 booga returned 100000 characters
100001
 booga returned 200000 characters
200001


#================================
# 2. Testing thread-safety
#================================
sudo ./booga-test2.sh

These test run sucessfully, output is below: 

bytes read  = 0 
bytes written  = 0 
number of opens: 
  /dev/booga0 = 0 times
  /dev/booga1 = 0 times
  /dev/booga2 = 0 times
  /dev/booga3 = 0 times
strings output 
  booga! booga! = 0 times
  googoo! gaagaa! = 0 times
  neka! maka! = 0 times
  wooga! wooga! = 0 times

Attempting to write to booga device
Attempting to write to booga device
Wrote 100 bytes.
 booga returned 100 characters
wooga! wooga! wooga! wooga! wooga! wooga! wooga! wooga! wooga! wooga! wooga! wooga! wooga! wooga! wo
./booga-test2.sh: line 18: 26020 Terminated              ./test-booga 3 100 w
 booga returned 100 characters
neka! maka! neka! maka! neka! maka! neka! maka! neka! maka! neka! maka! neka! maka! neka! maka! neka
 booga returned 100 characters
booga! booga! booga! booga! booga! booga! booga! booga! booga! booga! booga! booga! booga! booga! bo
Attempting to write to booga device
Wrote 100 bytes.
Attempting to write to booga device
Wrote 100 bytes.
 booga returned 100 characters
googoo! gaagaa! googoo! gaagaa! googoo! gaagaa! googoo! gaagaa! googoo! gaagaa! googoo! gaagaa! goog

bytes read  = 400 
bytes written  = 300 
number of opens: 
  /dev/booga0 = 2 times
  /dev/booga1 = 2 times
  /dev/booga2 = 2 times
  /dev/booga3 = 2 times
strings output 
  booga! booga! = 1 times
  googoo! gaagaa! = 1 times
  neka! maka! = 1 times
  wooga! wooga! = 1 times



#===================================================
# 3. Additional Testing - Hammering driver on reads
#===================================================
In addition to the basic training I ran the check below 
to make sure that:
1) the driver can survive extensive repetition of operations.
2) the random numbers that are generated uniformally distributed

sudo ./booga_load
for i in {1..1000}; do sudo ./test-booga 0 100 read; done
cat /proc/driver/booga
sudo ./booga_unload

Got acceptable output output:

bytes read  = 100000 
bytes written  = 0 
number of opens: 
  /dev/booga0 = 1000 times
  /dev/booga1 = 0 times
  /dev/booga2 = 0 times
  /dev/booga3 = 0 times
strings output 
  booga! booga! = 263 times
  googoo! gaagaa! = 253 times
  neka! maka! = 235 times
  wooga! wooga! = 249 times


#===================================================
# 4. Additional Testing - Hammering driver on writes (on dev 3)
#===================================================
sudo ./booga_load
for i in {1..1000}; do sudo ./test-booga 3 100 write; done
cat /proc/driver/booga
sudo ./booga_unload

bytes read  = 0 
bytes written  = 0 
number of opens: 
  /dev/booga0 = 0 times
  /dev/booga1 = 0 times
  /dev/booga2 = 0 times
  /dev/booga3 = 1000 times
strings output 
  booga! booga! = 0 times
  googoo! gaagaa! = 0 times
  neka! maka! = 0 times
  wooga! wooga! = 0 times


#===================================================
# 5. Additional Testing - extensive alternation of minor numbers 
#===================================================
sudo ./booga_load
for i in {1..1000}; do sudo ./test-booga 0 100 read; sudo ./test-booga 1 100 read;done
cat /proc/driver/booga
sudo ./booga_unload

bytes read  = 200000 
bytes written  = 0 
number of opens: 
  /dev/booga0 = 1000 times
  /dev/booga1 = 1000 times
  /dev/booga2 = 0 times
  /dev/booga3 = 0 times
strings output 
  booga! booga! = 508 times
  googoo! gaagaa! = 489 times
  neka! maka! = 517 times
  wooga! wooga! = 486 times

