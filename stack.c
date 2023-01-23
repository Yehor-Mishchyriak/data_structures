/* Yehor Mishchyriak, Wesleyan University, class of 2026;
 * Realization of a stack using arrays */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct{

    int capacity;
    int current_size;
    int* collection;
}Stack;

/* creates a stack  */
Stack* createStack(int capacity){

    Stack* new_stack = calloc(1, sizeof(Stack));
    new_stack -> collection = calloc(capacity, sizeof(int));
    new_stack -> capacity = capacity;

    return new_stack;
}

/* destroys a stack  */
void clear(Stack* stack){

    free(stack -> collection);
    free(stack);
}

/* checks if the stack is full */
bool isFull(Stack* stack){return stack -> current_size == stack -> capacity;}

/* checs if the stack is empty */
bool isEmpty(Stack* stack){return stack -> current_size == 0;}

/* pushes an element on top of the stack */
void push(int new_element, Stack* stack){

    if (isFull(stack)) return;

    stack -> collection[stack -> current_size] = new_element;
    stack -> current_size++;
}

/* removes an element from the top of the stack and returns its value */
int pop(Stack* stack){

    if (isEmpty(stack)) return -1;

    stack -> current_size--;
    return stack -> collection[stack -> current_size];
}

/* returns an element from the top of the stack */
int peak(Stack* stack){return isEmpty(stack) ? -1 : stack -> collection[stack -> current_size - 1];}

/* prints the whole stack */
void printStack(Stack* stack){

    for (int i = 0; i < stack -> current_size; i++)
        printf("%d ", stack -> collection[i]);
    printf("\n");
}


int main(void){

    Stack* stack1 = createStack(5);
    push(1, stack1);
    push(2, stack1);
    push(3, stack1);
    push(4, stack1);
    push(5, stack1);
    pop(stack1);
    push(6, stack1);
    push(7, stack1);
    printf("%d\n", peak(stack1));
    printStack(stack1);

    return 0;
}
