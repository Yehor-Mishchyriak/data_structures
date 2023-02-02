/* Yehor Mishchyriak, Wesleyan University, class of 2026;
 * Realization of a singly-linked list */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* node type */
typedef struct Node{

    char* value;
    struct Node* next;
}Node;

/* list type */
typedef struct{

    Node* head;
    int currentSize;
}List;

/* creates a node */
Node* createNode(char* value){

    Node* NewNode = calloc(1, sizeof(Node));
    NewNode -> next = NULL;
    NewNode -> value = value;
    return NewNode;
}

/* adds an element to the end of the list */
void append(List* list, char* value){

    Node* current_node = list -> head;
    while (current_node -> next != NULL)
        current_node = current_node -> next;

    current_node -> next = createNode(value);
    list -> currentSize++;
}

/* creates a list of the passed elements */
/* vargs type to be passed is <char*> */
List* createListOf(int length, ...){

    va_list args;
    if (length < 0){va_end(args); return NULL;}

    List* newList = calloc(1, sizeof(List));
    newList -> head = createNode("dummy");
    newList -> currentSize = 0;

    va_start(args, length);

    for (int i = 0; i < length; i++)
        append(newList, va_arg(args, char*));

    va_end(args);

    return newList;
}

/* returns the last element of the list */
/* having deleted it beforehand */
char* pop(List* list){

    Node* current_node = list -> head;
    if (current_node -> next == NULL) return "NULL";

    Node* previous_node = list -> head;
    while (current_node -> next != NULL){
        previous_node = current_node;
        current_node = current_node -> next;
    }

    char* data_to_pop = current_node -> value;
    free(current_node);
    previous_node -> next = NULL;

    list -> currentSize--;
    return data_to_pop;
}

/* inserts an element at the specified location in the list */
void insert(List* list, char* value, int location){

    Node* newNode = createNode(value);

    Node* current_node = list -> head;
    int current_location = 0;
    while (current_location < location && current_node -> next != NULL){
        current_node = current_node -> next;
        current_location++;
    }

    newNode -> next = current_node -> next;
    current_node -> next = newNode;
    list -> currentSize++;
}

/* deletes an element from the specified location in the list */
/* if location > (list -> currentSize) */
/* the last element is deleted */
void del(List* list, int location){

    Node* current_node = list -> head;
    if (current_node -> next == NULL) return;

    Node* previous_node = list -> head;
    int current_location = -1;
    do {
        previous_node = current_node;
        current_node = current_node -> next;
        current_location++;
    } while(current_node -> next != NULL && current_location != location);

    previous_node -> next = current_node -> next;
    free(current_node);
    list -> currentSize--;
}

/* removes the specified value from the list */
void remove_value(List* list, char* value_to_remove){

    Node* current_node = list -> head;
    Node* previous_node = list -> head;
    while (current_node -> next != NULL &&
          current_node -> value != value_to_remove){

        previous_node = current_node;
        current_node = current_node -> next;
    }

    if (current_node -> value == value_to_remove){
        previous_node -> next = current_node -> next;
        free(current_node);
        list -> currentSize--;
    } else return;
}

/* returns the location of the specified element */
int find(List* list, char* data_to_find){

    Node* current_node = list -> head;
    int index = -1;
    while (current_node != NULL){

        if (current_node -> value == data_to_find)
            return index;

        current_node = current_node -> next;
        index++;
    }

    return -1;
}

/* returns the current length of the list */
int len(List* list){return list -> currentSize;}

/* returns the number of the instances of the specified element */
int count(List* list, char* instance){

    Node* current_node = list -> head;
    int number_of_instances = 0;

    while (current_node -> next != NULL){

        current_node = current_node -> next;
        if (current_node -> value == instance) number_of_instances++;
    }

    return number_of_instances;
}

/* prints the list */
void printList(List* list){

    Node* current_node = list -> head;

    while(current_node -> next != NULL){
        current_node = current_node -> next;
        printf("%s ", current_node -> value);
    }printf("\n");
}

int main(void){

    return 1;
}
