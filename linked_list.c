/* LINKED LIST DATA STRUCTURE; SINGLY_LINKED LISTS WITH THE SENTINEL NODE
 * YEHOR MISHCHYRIAK. WESLEYAN UNIVERSITY
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Node{

    int value;
    struct Node* next;
}Node;


// methods for the node type
Node* create(int data){

    Node* node = calloc(1, sizeof(Node));
    node -> next = NULL;
    node -> value = data;
    return node;
}


void append(Node* head, int data){

    Node* current_node = head;
    while (current_node -> next != NULL)
        current_node = current_node -> next;

    current_node -> next = create(data);
}


int pop(Node* head){

    Node* current_node = head;
    if (current_node -> next == NULL) return -1;

    Node* previous_node = head;
    while (current_node -> next != NULL){
        previous_node = current_node;
        current_node = current_node -> next;
    }

    int data_to_pop = current_node -> value;
    free(current_node);
    previous_node -> next = NULL;
    return data_to_pop;
}


void insert(Node* head, int data, int location){

    Node* new_node = create(data);

    Node* current_node = head;
    int current_location = 0;
    while (current_location < location && current_node -> next != NULL){
        current_node = current_node -> next;
        current_location++;
    }

    new_node -> next = current_node -> next;
    current_node -> next = new_node;
}


void delete(Node* head, int location){

    Node* current_node = head;
    if (current_node -> next == NULL) return;

    Node* previous_node = head;
    int current_location = -1;
    do {
        previous_node = current_node;
        current_node = current_node -> next;
        current_location++;
    } while(current_node -> next != NULL && current_location != location);

    previous_node -> next = current_node -> next;
    free(current_node);
}


void remove_value(Node* head, int value_to_remove){

    Node* current_node = head;
    Node* previous_node = head;
    while (current_node -> next != NULL && current_node -> value != value_to_remove){
        previous_node = current_node;
        current_node = current_node -> next;
    }

    if (current_node -> value == value_to_remove){
        previous_node -> next = current_node -> next;
        free(current_node);
    } else return;
}


int find(Node* head, int data_to_find){

    Node* current_node = head;
    int index = -1;
    while (current_node != NULL){

        if (current_node -> value == data_to_find)
            return index;

        current_node = current_node -> next;
        index++;
    }

    return -1;
}


int len(Node* head){

    Node* current_node = head;
    int length = 0;

    while (current_node -> next != NULL){
        current_node = current_node -> next;
        length++;
    }

    return length;
}


int count(Node* head, int instance){

    Node* current_node = head;
    int number_of_instances = 0;

    while (current_node -> next != NULL){

        current_node = current_node -> next;
        if (current_node -> value == instance) number_of_instances++;
    }

    return number_of_instances;
}


void print_list(Node* head){

    Node* current_node = head;
    while(current_node -> next != NULL){
        current_node = current_node -> next;
        printf("%d ", current_node -> value);
    }
    printf("\n");
}


int main(void){

    return 1;
}

