/* Yehor Mishchyriak, Wesleyan University, class of 2026;
 * Realization of a queue using arrays */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct{

    int capacity;
    int current_size;
    int* collection;
}Queue;

/* creates a queue */
Queue* createQueue(int capacity){

    if (capacity <= 0) return NULL;

    Queue* new_queue = calloc(1, sizeof(Queue));
    new_queue -> capacity = capacity;
    new_queue -> current_size = 0;
    new_queue -> collection = calloc(capacity, sizeof(int));

    return new_queue;
}

/* destroys a queue */
void clear(Queue* queue){

    free(queue -> collection);
    free(queue);
}

/* checks if the queue is empty */
bool isEmpty(Queue* queue){return queue -> current_size == 0;}

/* checks if the queue is empty */
bool isFull(Queue* queue){return queue -> current_size == queue -> capacity;}

/* adds an element to the queue */
void enqueue(int new_element, Queue* queue){

    if (isFull(queue)) return;

    queue -> collection[queue -> current_size] = new_element;
    queue -> current_size++;
}

/* removes an element from the queue */
void dequeue(Queue* queue){

    if (isEmpty(queue)) return;
    if (queue -> current_size == 1){queue -> current_size--; return;}

    for (int i = 0, j = 1; j < queue -> current_size; i++, j++)
        queue -> collection[i] = queue -> collection[j];

    queue -> current_size--;
}

/* returns the first element of the queue */
int first(Queue* queue){return isEmpty(queue) ? -1 : queue -> collection[0];}

/* returns the last element of the queue */
int last(Queue* queue){return isEmpty(queue) ? -1 : queue -> collection[queue -> current_size - 1];}

/* prints a queue */
void printQueue(Queue* queue){
    for (int i = 0; i < queue -> current_size; i++)
        printf("%d ", queue -> collection[i]);
    printf("\n");
}


int main(void){

    return 1;
}
