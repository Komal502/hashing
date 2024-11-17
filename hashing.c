#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Structure for Chaining (Linked List) method
struct Node {
    int key;
    struct Node* next;
};

// Structure for Open Addressing method
struct HashTable {
    int* table;
    int* status; // 0 = empty, 1 = occupied, 2 = deleted
};

// Function to create a new node for chaining
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Hash function 1 (Simple modulo based)
int hashFunction1(int key) {
    return key % TABLE_SIZE;
}

// Chaining Method: Insert key into hash table
void insertChaining(struct Node* hashTable[], int key) {
    int index = hashFunction1(key);
    struct Node* newNode = createNode(key);
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

// Chaining Method: Search for a key in hash table
int searchChaining(struct Node* hashTable[], int key) {
    int index = hashFunction1(key);
    struct Node* temp = hashTable[index];
    while (temp) {
        if (temp->key == key) {
            return 1; // Key found
        }
        temp = temp->next;
    }
    return 0; // Key not found
}

// Open Addressing: Initialize hash table
void initHashTable(struct HashTable* ht) {
    ht->table = (int*)malloc(sizeof(int) * TABLE_SIZE);
    ht->status = (int*)malloc(sizeof(int) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = -1; // -1 means empty slot
        ht->status[i] = 0; // 0 means empty
    }
}

// Open Addressing: Insert key into hash table (Linear Probing)
void insertOpenAddressing(struct HashTable* ht, int key) {
    int index = hashFunction1(key);
    int i = 0;
    while (i < TABLE_SIZE) {
        int probeIndex = (index + i) % TABLE_SIZE;
        if (ht->status[probeIndex] == 0 || ht->status[probeIndex] == 2) { // Empty or deleted slot
            ht->table[probeIndex] = key;
            ht->status[probeIndex] = 1; // Mark slot as occupied
            return;
        }
        i++;
    }
    printf("Hash table is full\n");
}

// Open Addressing: Search for key in hash table (Linear Probing)
int searchOpenAddressing(struct HashTable* ht, int key) {
    int index = hashFunction1(key);
    int i = 0;
    while (i < TABLE_SIZE) {
        int probeIndex = (index + i) % TABLE_SIZE;
        if (ht->status[probeIndex] == 0) {
            return 0; // Key not found
        }
        if (ht->status[probeIndex] == 1 && ht->table[probeIndex] == key) {
            return 1; // Key found
        }
        i++;
    }
    return 0; // Key not found
}

// Function to display hash table contents (Chaining)
void displayChaining(struct Node* hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        if (hashTable[i] == NULL) {
            printf("Empty\n");
        } else {
            struct Node* temp = hashTable[i];
            while (temp) {
                printf("%d -> ", temp->key);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

// Function to display hash table contents (Open Addressing)
void displayOpenAddressing(struct HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->status[i] == 0) {
            printf("Index %d: Empty\n", i);
        } else if (ht->status[i] == 1) {
            printf("Index %d: %d\n", i, ht->table[i]);
        } else {
            printf("Index %d: Deleted\n", i);
        }
    }
}

int main() {
    // Chaining Implementation
    struct Node* hashTableChaining[TABLE_SIZE] = {0}; // Initialize hash table with NULL
    insertChaining(hashTableChaining, 15);
    insertChaining(hashTableChaining, 25);
    insertChaining(hashTableChaining, 35);
    insertChaining(hashTableChaining, 5);

    printf("Chaining Method Hash Table:\n");
    displayChaining(hashTableChaining);

    // Search in Chaining
    printf("Searching for key 25 in Chaining: %s\n", searchChaining(hashTableChaining, 25) ? "Found" : "Not Found");

    // Open Addressing (Linear Probing) Implementation
    struct HashTable ht;
    initHashTable(&ht);
    insertOpenAddressing(&ht, 15);
    insertOpenAddressing(&ht, 25);
    insertOpenAddressing(&ht, 35);
    insertOpenAddressing(&ht, 5);

    printf("\nOpen Addressing Hash Table:\n");
    displayOpenAddressing(&ht);

    // Search in Open Addressing
    printf("Searching for key 25 in Open Addressing: %s\n", searchOpenAddressing(&ht, 25) ? "Found" : "Not Found");

    return 0;
}
