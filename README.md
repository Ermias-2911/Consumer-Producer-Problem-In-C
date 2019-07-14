# Consumer-Producer-Problem-In-C
## Author: Ermias Haile 
   Nov 29, 2018

## Project Description: 
implementing a Producer-Consumer program with a bounded buffer queue of N elements, P producer threads and C consumer<br/> 
threads  (N, P and C should be command line arguments to your program, along with three additional parameters, X, Ptime <br/>
and Ctime, that are described below). Each Producer thread should Enqueue X different numbers onto the queue (sleeping <br/>
for Ptime seconds in between each call to Enqueue). Each Consumer thread should Dequeue P*X/C (be careful when P*X/C is <br/>
not evenly divisible) items from the queue (sleeping for Ctime seconds in between each call to Dequeue). The main program<br/> should create/initialize the Bounded Buffer Queue, print a timestamp, spawn off C consumer threads & P producer threads,<br/> wait for all of the threads to finish and then print off another timestamp & the duration of execution.<br/>

### Step 1.
Write high level pseudocode for the Producer and Consumer threads, as well as for the Bounded Buffer Queue <br/>(Enqueue, Dequeue). Use semaphores to describe syn- chronization logic in your pseudocode. You may use the P/V calls to <br/>
denote locking
  
### Step 2.
and unlocking of a mutex and signal/wait calls to denote the locking and unlocking of semaphores. Submit this <br/>
pseudocode in a  file called pandcpseudo.txt . Design a testing strategy for verifying that all of the threads are <br/> collectively executing correctly. One possible testing strategy is to have a single atomic counter (i.e. a counter with <br/>
mutex synchronization so it is guaranteed to produce different numbers) to generate numbers for Producer threads, then <br/>
have the main routine combine the output from all of the Consumer threads, sort it and verify that all of the input <br/>
numbers appeared as output. Submit this testing strategy as part of your design documentation. <br/>
Implement your Producer-Consumer program using Linux threads. <br/>
For step 2, you will take your pandcpseudo.txt and implement it in C using the appro- priate synchronization <br/>
primitives(mutex locks and/or signal semaphores and/or count semaphores) so that your code always executes correctly. <br/> Submit well-commented source code and annotated output to demonstrate that your code is executing cor- rectly. <br/>
### The implementation has the following requirements:
– Your implementation must be stored in pandc.c NO OTHER .C FILES WILL BE CHECKED OR GRADED FOR ANY REASON <br/>
– Your program must accept 6 command like arguments N,P,C,X,Ptime,Ctime Where each arguments is : <br/>
∗ N is the number of buffers to maintain. <br/>
∗ P is the number of producer threads. <br/>
∗ C is the number of consumer threads.<br/>
∗ X is the number of items each producer thread will produce.<br/>
∗ Ptime is the how long (in seconds) each producer thread will sleep after producing an item.<br/>
∗ Ctime is the how long (in seconds) each consumer thread will sleep after consuming an item.<br/>
– Your implementation must maintain N buffers. Size of these buffers can be one which store one integer. Which basically<br/>
makes the bounded buffer and 1-Dimensional array of integers. <br/>
– Your implementation must generate a unique sequence of numbers for the Pro- ducer threads. Then the Consumer threads <br/>
should consume the same sequence. <br/>
– Your implementation must handle when P*X/C is not evenly divisible. For ex- <br/> ampleifP=3andX=5andC=2thenP*X/Cis(5*3)/2whichis7.5. This means one consumer thread consume 1 extra item then the other <br/>
thread.<br/>
– Each consumer thread must print their thread id and which item they have con- sumed. It may be useful to assign a <br/>
readable number to each thread to make things easier. <br/>


– Each consumer thread must sleep for Ctime AFTER consuming each item. <br/>
– Each producer thread must print their thread id and which item they have pro- duced. It may be useful to assign a <br/>
readable number to each thread to make things easier.<br/>
– Each producer thread must sleep for Ptime AFTER producing each item.<br/>
– Must use enqueue item and dequeue item functions given to add and remove<br/>
items. These need to be implemented as well.<br/>
– Your implementation must implement a test strategy that shows your program works. A simple approach is to maintain a <br/> consumer array and a producer array. If everything works out these two arrays should be identical and in order(Given <br/>
enqueue and dequeue are implemented correctly). <br/>

## Build Instructions

One can use Makefile given along with the source code to compile the program.
For using Makefille simply exute "make" command in same directory as that of source code.

To compile manually one can use following command:

gcc -I -Wall pandc.c -o pandc -lpthread -g

This will create object file named pandc

### Run Instructions
Simply run by executing the object file created. <br/>
./pandc N P C X Ptime Ctime <br/>
Where: <br/>
N: Max element in queue at a given time <br/>
P: No of producer thread <br/>
C: No of comsumer thread <br/>
X: No of elements enqueued by each producer thread <br/>
Ptime: Time for which producer thread sleeps <br/>
Ctime: Time for which consumer thread sleeps <br/>


### OUTPUT: 
Current Time: Thu Nov 29 12:24:35 2018 <br/>

Number of Buffers: 7<br/> 
Number of Producers: 5<br/>
Number of Consumers: 3<br/>
Number of items Produced by each producer: 16<br/>
Number of items Consumed by each consumer: 26<br/>
Over consume on?: 1<br/>
Over consume amount: 28<br/>
Time each Producer Sleeps (seconds): 1<br/>
Time each Consumer Sleeps (seconds): 1<br/>

0 was produced by producer-> 0<br/>
0 was consumed by consumer-> 2<br/>
1 was produced by producer-> 0<br/>
1 was consumed by consumer-> 2<br/>
2 was produced by producer-> 0<br/>
2 was consumed by consumer-> 2<br/>
3 was produced by producer-> 0<br/>
3 was consumed by consumer-> 1<br/>
4 was produced by producer-> 0<br/>
4 was consumed by consumer-> 1<br/>
5 was produced by producer-> 0<br/>
5 was consumed by consumer-> 1<br/>
6 was produced by producer-> 0<br/>
6 was consumed by consumer-> 0<br/>
7 was produced by producer-> 0<br/>
7 was consumed by consumer-> 0<br/>
8 was produced by producer-> 0<br/>
8 was consumed by consumer-> 0<br/>
9 was produced by producer-> 0<br/>
9 was consumed by consumer-> 2<br/>
10 was produced by producer-> 0<br/>
10 was consumed by consumer-> 1<br/>
11 was produced by producer-> 0<br/>
11 was consumed by consumer-> 0<br/>
12 was produced by producer-> 0<br/>
12 was consumed by consumer-> 0<br/>
13 was produced by producer-> 0<br/>
13 was consumed by consumer-> 2<br/>
14 was produced by producer-> 0<br/>
14 was consumed by consumer-> 0<br/>
15 was produced by producer-> 0<br/>
15 was consumed by consumer-> 0<br/>
Producer Thread joined: 0<br/>
16 was produced by producer-> 1<br/>
16 was consumed by consumer-> 1<br/>
17 was produced by producer-> 1<br/>
17 was consumed by consumer-> 1<br/>
18 was produced by producer-> 1<br/>
18 was consumed by consumer-> 1<br/>
19 was produced by producer-> 1<br/>
19 was consumed by consumer-> 0<br/>
20 was produced by producer-> 1<br/>
20 was consumed by consumer-> 0<br/>
21 was produced by producer-> 1<br/>
21 was consumed by consumer-> 1<br/>
22 was produced by producer-> 1<br/>
22 was consumed by consumer-> 2<br/>
23 was produced by producer-> 1<br/>
23 was consumed by consumer-> 1<br/>
24 was produced by producer-> 1<br/>
24 was consumed by consumer-> 1<br/>
25 was produced by producer-> 1<br/>
25 was consumed by consumer-> 1<br/>
26 was produced by producer-> 1<br/>
26 was consumed by consumer-> 0<br/>
27 was produced by producer-> 1<br/>
27 was consumed by consumer-> 0<br/>
28 was produced by producer-> 1<br/>
28 was consumed by consumer-> 2<br/>
29 was produced by producer-> 1<br/>
29 was consumed by consumer-> 2<br/>
30 was produced by producer-> 1<br/>
30 was consumed by consumer-> 2<br/>
31 was produced by producer-> 1<br/>
31 was consumed by consumer-> 0<br/>
32 was produced by producer-> 2<br/>
Producer Thread joined: 1<br/>
32 was consumed by consumer-> 0<br/>
33 was produced by producer-> 2<br/>
33 was consumed by consumer-> 0<br/>
34 was produced by producer-> 2<br/>
34 was consumed by consumer-> 2<br/>
35 was produced by producer-> 2<br/>
35 was consumed by consumer-> 1<br/>
36 was produced by producer-> 2<br/>
36 was consumed by consumer-> 1<br/>
37 was produced by producer-> 2<br/>
37 was consumed by consumer-> 0<br/>
38 was produced by producer-> 2<br/>
38 was consumed by consumer-> 2<br/>
39 was produced by producer-> 2<br/>
39 was consumed by consumer-> 1<br/>
40 was produced by producer-> 2<br/>
40 was consumed by consumer-> 1<br/>
41 was produced by producer-> 2<br/>
41 was consumed by consumer-> 0<br/>
42 was produced by producer-> 2<br/>
42 was consumed by consumer-> 0<br/>
43 was produced by producer-> 2<br/>
43 was consumed by consumer-> 2<br/>
44 was produced by producer-> 2<br/>
44 was consumed by consumer-> 0<br/>
45 was produced by producer-> 2<br/>
45 was consumed by consumer-> 1<br/>
46 was produced by producer-> 2<br/>
46 was consumed by consumer-> 1<br/>
46 was consumed by consumer-> 1<br/>
47 was produced by producer-> 2<br/>
47 was consumed by consumer-> 0<br/>
Producer Thread joined: 2<br/>
48 was produced by producer-> 3<br/>
48 was consumed by consumer-> 1<br/>
49 was produced by producer-> 3<br/>
49 was consumed by consumer-> 1<br/>
50 was produced by producer-> 3<br/>
50 was consumed by consumer-> 1<br/>
51 was produced by producer-> 3<br/>
51 was consumed by consumer-> 1<br/>
52 was produced by producer-> 3<br/>
53 was produced by producer-> 3<br/>
52 was consumed by consumer-> 1<br/>
53 was consumed by consumer-> 2<br/>
54 was produced by producer-> 3<br/>
54 was consumed by consumer-> 0<br/>
55 was produced by producer-> 3<br/>
55 was consumed by consumer-> 0<br/>
56 was produced by producer-> 3<br/>
56 was consumed by consumer-> 1<br/>
57 was produced by producer-> 3<br/>
57 was consumed by consumer-> 2<br/>
58 was produced by producer-> 3<br/>
58 was consumed by consumer-> 2<br/>
59 was produced by producer-> 3<br/>
59 was consumed by consumer-> 0<br/>
60 was produced by producer-> 3<br/>
60 was consumed by consumer-> 0<br/>
61 was produced by producer-> 3<br/>
61 was consumed by consumer-> 0<br/>
62 was produced by producer-> 3<br/>
62 was consumed by consumer-> 0<br/>
63 was produced by producer-> 3<br/>
63 was consumed by consumer-> 2<br/>
Producer Thread joined: 3<br/>
64 was produced by producer-> 4<br/>
64 was consumed by consumer-> 1<br/>
65 was produced by producer-> 4<br/>
65 was consumed by consumer-> 1<br/>
66 was produced by producer-> 4<br/>
66 was consumed by consumer-> 0<br/>
67 was produced by producer-> 4<br/>
67 was consumed by consumer-> 0<br/>
68 was produced by producer-> 4<br/>
68 was consumed by consumer-> 0<br/>
69 was produced by producer-> 4<br/>
69 was consumed by consumer-> 2<br/>
70 was produced by producer-> 4<br/>
70 was consumed by consumer-> 2<br/>
71 was produced by producer-> 4<br/>
71 was consumed by consumer-> 2<br/>
72 was produced by producer-> 4<br/>
72 was consumed by consumer-> 2<br/>
73 was produced by producer-> 4<br/>
73 was consumed by consumer-> 2<br/>
74 was produced by producer-> 4<br/>
74 was consumed by consumer-> 1<br/>
75 was produced by producer-> 4<br/>
76 was produced by producer-> 4<br/>
75 was consumed by consumer-> 2<br/>
77 was produced by producer-> 4<br/>
76 was consumed by consumer-> 2<br/>
78 was produced by producer-> 4<br/>
77 was consumed by consumer-> 2<br/>
78 was consumed by consumer-> 2<br/>
79 was produced by producer-> 4<br/>
79 was consumed by consumer-> 2<br/>
Producer Thread joined: 4<br/>
Consumer Thread joined: 0<br/>
Consumer Thread joined: 1<br/>
Consumer Thread joined: 2<br/>

Current Time: Thu Nov 29 12:25:56 2018<br/>

Producer Array	Consumer Array<br/>
0		0<br/>
1		1<br/>
2		2<br/>
3		3<br/>
4		4<br/>
5		5<br/>
6		6<br/>
7		7<br/>
8		8<br/>
9		9<br/>
10		10<br/>
11		11<br/>
12		12<br/>
13		13<br/>
14		14<br/>
15		15<br/>
16		16<br/>
17		17<br/>
18		18<br/>
19		19<br/>
20		20<br/>
21		21<br/>
22		22<br/>
23		23<br/>
24		24<br/>
25		25<br/>
26		26<br/>
27		27<br/>
28		28<br/>
29		29<br/>
30		30<br/>
31		31<br/>
32		32<br/>
33		33<br/>
34		34<br/>
35		35<br/>
36		36<br/>
37		37<br/>
38		38<br/>
39		39<br/>
40		40<br/>
41		41<br/>
42		42<br/>
43		43<br/>
44		44<br/>
45		45<br/>
46		46<br/>
47		47<br/>
48		48<br/>
49		49<br/>
50		50<br/>
51		51<br/>
52		52<br/>
53		53<br/>
54		54<br/>
55		55<br/>
56		56<br/>
57		57<br/>
58		58<br/>
59		59<br/>
60		60<br/>
61		61<br/>
62		62<br/>
63		63<br/>
64		64<br/>
65		65<br/>
66		66<br/>
67		67<br/>
68		68<br/>
69		69<br/>
70		70<br/>
71		71<br/>
72		72<br/>
73		73<br/>
74		74<br/>
75		75<br/>
76		76<br/>
77		77<br/>
78		78<br/>
79		79<br/>
Consume and Produce Arrays Match!<br/>



Time Elapsed: 0.035365 secs<br/>


