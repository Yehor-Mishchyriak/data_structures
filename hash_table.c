/* Yehor Mishchyriak, Wesleyan University, class of 2026;
 * Realization of a dictionary using hash-tables,
 * and separate chaining for collision resolution
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/* structs */
typedef struct Node{

    char* key;
    char* value;
    struct Node* next;
}Node;


typedef struct HashTable{

    int capacity;
    int current_size;
    Node** buckets;
}HashTable;

/* creates a node */
Node* createNode(char* key, char* value, Node* next){

    Node* newNode = calloc(1, sizeof(Node));
    newNode -> key = key;
    newNode -> value = value;
    newNode -> next = next;

    return newNode;
}

/* initializes a hash-table */
HashTable* createHashTable(int capacity){

    HashTable* table = calloc(1, sizeof(HashTable));
    table -> buckets = calloc(capacity, sizeof(Node));
    table -> capacity = capacity;
    table -> current_size = 0;

    for (int i = 0; i < capacity; i++){

        table -> buckets[i] = createNode("dummy", "-1", NULL);
    }

    return table;
}

/* computes hash of key */
int hash(char* key, HashTable* table){

    int total = 0;
    for (int i = 0; i < strlen(key); i++){
        total += key[i];
    }

    return total % (table -> capacity);
}

/* prints key : value pairs */
void keyValuePairs(HashTable* table){

    for (int bucket = 0; bucket < table -> capacity; bucket++){

            for (Node* current_node = table -> buckets[bucket] -> next;

                 current_node != NULL;
                 current_node = current_node -> next)
            printf("%s : %s\n", current_node -> key, current_node -> value);
    }
}

/* tells if the table contains a cetrain key */
void newPair(char* key, char* value, HashTable* table){

    Node* current_node = table -> buckets[hash(key, table)];
    Node* previous_node = current_node;
    while (current_node -> next != NULL){

        if (current_node -> key == key){
            current_node -> value = value;
            return;
        }

        previous_node = current_node;
        current_node = current_node -> next;
    }

    previous_node -> next = createNode(key, value, NULL);
    table -> current_size++;
}

/* returns a value by the key */
char* get(char* key, HashTable* table){

    Node* current_node = table -> buckets[hash(key, table)];
    while (current_node != NULL){

        if (current_node -> key == key){
            return current_node -> value;
        }

        current_node = current_node -> next;
    }

    return "NULL";
}

/* deletes a key-value pair by the key, and returns a value;
 * if the key is not found, returns "NULL"
 */
char* pop(char* key, HashTable* table){

    Node* current_node = table -> buckets[hash(key, table)];
    Node* previous_node = current_node;
    while (current_node != NULL){

        if (current_node -> key == key){
            char* temp = current_node -> value;
            previous_node -> next = current_node -> next;
            free(current_node);
            table -> current_size--;
            return temp;
        }

        previous_node = current_node;
        current_node = current_node -> next;
    }

    return "NULL";
}

/* deletes a key-value pair by the key */
void delete(char* key, HashTable* table){

    Node* current_node = table -> buckets[hash(key, table)];
    Node* previous_node = current_node;
    while (current_node != NULL){

        if (current_node -> key == key){
            previous_node -> next = current_node -> next;
            free(current_node);
            table -> current_size--;
            return;
        }

        previous_node = current_node;
        current_node = current_node -> next;
    }
}

/* returns an array of keys */
char** keys(HashTable* table){

    char** keys = calloc(table -> current_size, sizeof(char*));
    for (int bucket = 0, index = 0; bucket < table -> capacity; bucket++){

            for (Node* current_node = table -> buckets[bucket] -> next;
                 current_node != NULL;
                 current_node = current_node -> next, index++)

                keys[index] = current_node -> key;
    }

    return keys;
}

/* returns an array of values */
char** values(HashTable* table){

    char** values = calloc(table -> current_size, sizeof(char*));
    for (int bucket = 0, index = 0; bucket < table -> capacity; bucket++){

            for (Node* current_node = table -> buckets[bucket] -> next;
                 current_node != NULL;
                 current_node = current_node -> next, index++)

                values[index] = current_node -> value;
    }

    return values;
}

/* prints an array of keys or values */
void print_array(char** array, int size){

    for (int i = 0; i < size; i++)
        printf("%s ", array[i]);
    printf("\n");
}


int main(void){

    HashTable* table1 = createHashTable(10);
    newPair("Yehor", "+380663557788", table1);
    newPair("Ihor", "+380674691167", table1);
    newPair("Dmitro", "+380993421872", table1);

    print_array(keys(table1), table1 -> current_size);
    print_array(values(table1), table1 -> current_size);

    return 1;
}


/* Additionally, the data structure needs:
 *
 * (1) isEmpty and isFull functions;
 * (2) clear function to delete the dictionary;
 * (3) copy to create a copy of a dictionary;
 */
