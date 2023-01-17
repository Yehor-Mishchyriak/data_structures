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

/* creates a hash-table */
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

/* deletes a hash-table */
void clear(HashTable* table){

    // freeing chains
    for (int bucket = 0; bucket < table -> capacity; bucket++){

            for (Node* current_node = table -> buckets[bucket], *previous_node = current_node;
                 current_node != NULL;
                 previous_node = current_node, current_node = current_node -> next)

                free(previous_node);
    }

    // freeing buckets
    free(table -> buckets);

    // freeing the table
    free(table);
}

/* computes hash of key */
int hash(char* key, HashTable* table){

    int total = 0;
    for (int i = 0; i < strlen(key); i++){
        total += key[i];
    }

    return total % (table -> capacity);
}

/* tells if the table is empty */
bool isEmpty(HashTable* table){return table -> current_size == 0;}

/* tells if the table is full */
bool isFull(HashTable* table){return table -> current_size >= table -> capacity;}

/* returns the current size of the table */
int currentSize(HashTable* table){return table -> current_size;}

/* returns how full the table is */
double loadFactor(HashTable* table){return (double) table -> current_size / (double) table -> capacity;}

/* tells if the table is overloaded */
bool isOverLoaded(HashTable* table){return loadFactor(table) >= 0.7;}

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
    while (current_node != NULL){

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

/* returns a copy of a hash-table */
HashTable* copy(HashTable* table, int capacity){

    HashTable* new_table = createHashTable(capacity);

    for (int bucket = 0; bucket < table -> capacity; bucket++){

            for (Node* current_node = table -> buckets[bucket] -> next;
                 current_node != NULL;
                 current_node = current_node -> next)

                newPair(current_node -> key,
                        current_node -> value,
                        new_table);
    }

    return new_table;
}

/* returns the number of collided keys in the table */
int numberOfCollisions(HashTable* table){

    if (table -> capacity < 2) return table -> current_size;

    int collisions = 0;
    char** retrieved_keys = keys(table);

    for (int i = 0, current_hash; i < table -> current_size; i++){

        current_hash = hash(retrieved_keys[i], table);
        for (int j = 0; j < table -> current_size; j++){

            if (i == j) continue;
            else if (current_hash == hash(retrieved_keys[j], table)) collisions++;
        }
    }

    return collisions / 2;
}

/* prints an array of keys or values */
void print_array(char** array, int size){

    for (int i = 0; i < size; i++)
        printf("%s ", array[i]);
    printf("\n");
}


int main(void){

    HashTable* table1 = createHashTable(50);

    newPair("Yehor", "+380663557788", table1);
    newPair("Ihor", "+380674691167", table1);
    newPair("Dmitro", "+380993421872", table1);
    newPair("Pavel", "+380673272829", table1);

    HashTable* table2 = copy(table1, 5);
    newPair("Alexey", "+380993289910", table2);

    printf("table1: load is %f; # of collisions is %d;\ntable2: load is %f; # of collisions is %d;\n",
            loadFactor(table1), numberOfCollisions(table1), loadFactor(table2), numberOfCollisions(table2));

    return 1;
}

