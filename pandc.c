#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <limits.h>

//definition of the queue
typedef struct
{ 
	int front; //Index of front end of queue
	int rear; //Index of rear end of queue
	int size;  //current number of element in queue
	int capacity;  //Maximum capacity of the queue
	int *array; //Stores actual element of the queue
}Queue;


//Queue to store element consumed and produced
Queue* masterQueue, *producer_elem_array, *consumer_elem_array;

int producerSleep, consumerSleep, produceElement, queueSize, producerCount, consumerCount;
pthread_mutex_t lock_variable, sync_var;



//prints the current timestamp
void timestamp()
{
    time_t ltime;
    ltime=time(NULL);
    printf("Current Time: %s\n",asctime( localtime(&ltime) ) );
}

// Validate if input string is numeric string
int validNumber(char *s)
{
        int strLen = 0, i = 0;
        if(s == NULL)
        {
                return 0;
        }
        strLen = strlen(s);

        if(strLen < 1)
        {
                return 0;
        }

        for(i = 0; i < strLen; i++)
        {
                if(!isdigit(s[i]))
                {
                        return 0;
                }
        }
        return 1;
}


//Prints the usage of the program
void usage(char *exe) {
        printf("Usage: %s N P C X Ptime Ctime\n",  exe);
        printf("Where:\n");
        printf("N: Max element in queue at a given time\n");
        printf("P: No of producer thread\n");
        printf("C: No of comsumer thread\n");
        printf("X: No of elements enqueued by each producer thread\n");
        printf("Ptime: Time for which producer thread sleeps\n");
        printf("Ctime: Time for which consumer thread sleeps\n");
}


//Prints usage and error in case non numerical arguments are passed
void usage_err(char *exe) {
        fprintf(stderr, "All arguments should be numeric\n");
        fflush(stderr);
        usage(exe);
}


//Initialise the queue with starting capacity
Queue* createQueue(int capacity) 
{ 
	Queue* queue = (Queue*) malloc(sizeof(Queue)); 
	queue->capacity = capacity; 
	queue->front = queue->size = 0;  
	queue->rear = capacity - 1;  
	queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
	return queue; 
}  

//Deallocates the memory
void freeQueue(Queue *queue)
{
	free(queue->array);
	free(queue);
}

//Utility function to check if queue is Full
int queueFull(Queue *q) 
{  
	return (q->size == q->capacity);  
} 
  
//Utility function to check if queue is empty
int queueEmpty(Queue *q) 
{
  return (q->size == 0); 
} 



/* 
 * Function to remove item.
 * Item removed is returned
 */
int dequeue_item()
{
	if (queueEmpty(masterQueue))
		return INT_MIN; 

	int qItem = masterQueue->array[masterQueue->front]; 
	masterQueue->front = (masterQueue->front + 1)%masterQueue->capacity; 
	masterQueue->size = masterQueue->size - 1; 
	return qItem; 
}

//Add item in queue
int enqueue(Queue *queue, int item)
{
        if (queueFull(queue))        
                return INT_MIN;

        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->array[queue->rear] = item;
        queue->size = queue->size + 1;
        return item;
}


/* 
 * Function to add item.
 * Item added is returned.
 * It is up to you to determine
 * how to use the ruturn value.
 * If you decide to not use it, then ignore
 * the return value, do not change the
 * return type to void. 
 */
int enqueue_item(int item)
{
	return enqueue(masterQueue, item);
}



// Produccer thread function
void* producer_thread (void *tid)
{
	int thr_id;
	thr_id = *((int*)tid);
	int counter = 0, temp = 0;

	 pthread_mutex_lock(&sync_var);
	//Loop until required number of elements are produced
	while(counter < produceElement) {
		//Lock mutex
		pthread_mutex_lock(&lock_variable);
		//get the element that is enqued
		temp = enqueue_item((thr_id * produceElement) + counter);
		if(temp != INT_MIN) {
			//Add the element in producer_elem_array. It is used at end to compare the genunity of program
			enqueue(producer_elem_array, temp);
			printf("%d was produced by producer-> %d\n", temp, thr_id);
			counter++;
		}
		pthread_mutex_unlock(&lock_variable);
		sleep(producerSleep);
	}
	pthread_mutex_unlock(&sync_var);
	return NULL;

}

// Consumer thread function
void* consumer_thread (void *tid)
{
        int thr_id;
        thr_id = *((int*)tid);
        int counter = 0;
	int limit = 0, temp = 0;

	//If first thread then consume additional elements
	if(thr_id == 0) {
		temp = (producerCount * produceElement) / consumerCount;
		//All remaining elements after consumerCount - 1 consumers have consume their part
		limit = (producerCount * produceElement) - (temp * (consumerCount - 1));
	} else {
		limit =  (producerCount * produceElement) / consumerCount;
	}

	//Consume until reuqired elements aree consumed
        while(counter < limit) {
                pthread_mutex_lock(&lock_variable);
		//Get item from queue
		temp = dequeue_item();
                if(temp != INT_MIN) {
			printf("%d was consumed by consumer-> %d\n", temp, thr_id);
			//Add element to consumption queue. It is used at end of program to compare with elements produced in sequence
			enqueue(consumer_elem_array, temp);
                        counter++;
                }
                pthread_mutex_unlock(&lock_variable);
                sleep(consumerSleep);
        }

        return NULL;
}


//It pronts the element produced and consumed sequentially
void print_consumer_producer_array() {
	int i = 0, match = 1;
	printf("Producer Array\tConsumer Array\n");

	//Print all elements in sequence
	for(i = 0; i < produceElement * producerCount; i++) {
		printf("%d\t\t%d\n", producer_elem_array->array[i], consumer_elem_array->array[i]);
		if(producer_elem_array->array[i] != consumer_elem_array->array[i]) {
			match = 0;
		}
	}
	
	if(match) {
		printf("Consume and Produce Arrays Match!\n");
	} else {
		printf("Consume and Produce Arrays does not Match!\n");
	}

	printf("\n\n");
}


//It it used to perform initialisation 
void initialise(int argc, char** argv) {
	int consume = 0, overConsume = 0, overOn = 0;
	if(argc != 7) {
		usage(argv[0]);
		exit(-1);
	}

	// check if all command line arguments are numeric
	if(!validNumber(argv[1]) || !validNumber(argv[2]) || !validNumber(argv[3]) || !validNumber(argv[4]) || !validNumber(argv[5]) || !validNumber(argv[6]))
	{
		usage_err(argv[0]);
		exit(-1);
	}

	//Initialise vairables
	queueSize = atoi(argv[1]);
	producerCount = atoi(argv[2]);
	consumerCount = atoi(argv[3]);
	produceElement = atoi(argv[4]);
	producerSleep = atoi(argv[5]);
	consumerSleep = atoi(argv[6]);

	//Initialise queues
	masterQueue = createQueue(queueSize);
	producer_elem_array = createQueue(produceElement * producerCount);
	consumer_elem_array = createQueue(produceElement * producerCount);

	pthread_mutex_init(&lock_variable, NULL);
	pthread_mutex_init(&sync_var, NULL);

	//Print initial values
	printf("Number of Buffers: %d\n", queueSize);
	printf("Number of Producers: %d\n", producerCount);
	printf("Number of Consumers: %d\n", consumerCount);
	printf("Number of items Produced by each producer: %d\n", produceElement);

	//Find number of elements consumed by each consumer
	consume = (producerCount * produceElement) / consumerCount;

	//Compute if there is overconsumption
	overConsume = (producerCount * produceElement) - (consume * (consumerCount - 1));
	if(overConsume != consume) {
		overOn = 1;
	}

	printf("Number of items Consumed by each consumer: %d\n", consume);
	printf("Over consume on?: %d\n", overOn);
	printf("Over consume amount: %d\n", overOn * overConsume);
	printf("Time each Producer Sleeps (seconds): %d\n", producerSleep);
	printf("Time each Consumer Sleeps (seconds): %d\n", consumerSleep);
}



int main(int argc, char** argv) {
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	timestamp();
	int i = 0;
	pthread_t *producer_array = NULL;
	pthread_t *consumer_array = NULL;

	producerSleep = consumerSleep = produceElement = queueSize = producerCount = consumerCount = 0;
	masterQueue = NULL;

	initialise(argc, argv);
	printf("\n");
	

	producer_array = (pthread_t *) malloc(sizeof(pthread_t) * producerCount);
	consumer_array = (pthread_t *) malloc(sizeof(pthread_t) * consumerCount);

	// Creating consumer threads
	for(i = 0; i < consumerCount; i++) {
		if(pthread_create(&consumer_array[i], NULL, consumer_thread, (void*)&i)  != 0)
		{
			printf(" Warning can't create Thread %d\n", i);
			exit(-2);
		}
	}


	// Creating producer threads
	for(i = 0; i < producerCount; i++) {
		if(pthread_create(&producer_array[i], NULL, producer_thread, (void*)&i)  != 0)
		{
			printf(" Warning can't create Thread %d\n", i);
			exit(-2);
		}
		sleep(1);
	}


	//Wait for all threads
	for(i = 0; i < producerCount; i++) {
		pthread_join(producer_array[i], NULL);
		printf("Producer Thread joined: %d\n", i);
	}

	for(i = 0; i < consumerCount; i++) {
		pthread_join(consumer_array[i], NULL);
		printf("Consumer Thread joined: %d\n", i);
	}
	printf("\n");
	timestamp();

	//Print the differences
	print_consumer_producer_array();
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTime Elapsed: %f secs\n", cpu_time_used);

	//free memory
	free(producer_array);
	free(consumer_array);
	freeQueue(masterQueue);
	freeQueue(producer_elem_array);
	freeQueue(consumer_elem_array);
	return 0;
}
