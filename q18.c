//18.	Implement following collision handling techniques for hash table                                       
// Quadratic Probing
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define TABLE_SIZE 10

typedef struct HashTable {
    int* table;
    bool* occupied;
} HashTable;

HashTable* createHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->table = (int*)malloc(TABLE_SIZE * sizeof(int));
    ht->occupied = (bool*)malloc(TABLE_SIZE * sizeof(bool));
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = -1;
        ht->occupied[i] = false;
    }
    
    return ht;
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}
void insertQuadraticProbing(HashTable* ht, int key) {
    int index = hashFunction(key);
    int i = 0;
    
    while (ht->occupied[(index + i * i) % TABLE_SIZE]) {
        i++;
        if (i >= TABLE_SIZE) {
            printf("Hash table is full\n");
            return;
        }
    }
    
    int finalIndex = (index + i * i) % TABLE_SIZE;
    ht->table[finalIndex] = key;
    ht->occupied[finalIndex] = true;
    printf("Inserted %d at index %d\n", key, finalIndex);
}

int searchQuadraticProbing(HashTable* ht, int key) {
    int index = hashFunction(key);
    int i = 0;
    
    while (ht->occupied[(index + i * i) % TABLE_SIZE]) {
        if (ht->table[(index + i * i) % TABLE_SIZE] == key) {
            return (index + i * i) % TABLE_SIZE;
        }
        i++;
        if (i >= TABLE_SIZE) break;
    }
    
    return -1;
}
void displayHashTable(HashTable* ht) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->occupied[i]) {
            printf("Index %d: %d\n", i, ht->table[i]);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}


int main() {
    printf("=== QUESTION 18: Quadratic Probing Hash Table ===\n");
    
    HashTable* ht = createHashTable();
    int choice, key;
    
    while (1) {
        printf("\n1. Insert\n2. Search\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insertQuadraticProbing(ht, key);
                break;
                
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                int result = searchQuadraticProbing(ht, key);
                if (result != -1) {
                    printf("Key %d found at index %d\n", key, result);
                } else {
                    printf("Key %d not found\n", key);
                }
                break;
                
            case 3:
                displayHashTable(ht);
                break;
                
            case 4:
                free(ht->table);
                free(ht->occupied);
                free(ht);
                exit(0);
                
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}
