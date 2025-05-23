// 19.	Implement following collision handling techniques for hash table                                       Double Hashing Using Mod as a hash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define TABLE_SIZE 13  // Prime number for better distribution
#define HASH2_PRIME 7  // Smaller prime for second hash function

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

// Primary hash function: h1(key) = key % TABLE_SIZE
int hashFunction1(int key) {
    return key % TABLE_SIZE;
}

// Secondary hash function: h2(key) = HASH2_PRIME - (key % HASH2_PRIME)
// This ensures h2(key) is never 0 and is relatively prime to TABLE_SIZE
int hashFunction2(int key) {
    return HASH2_PRIME - (key % HASH2_PRIME);
}

// Double hashing formula: (h1(key) + i * h2(key)) % TABLE_SIZE
int doubleHash(int key, int i) {
    return (hashFunction1(key) + i * hashFunction2(key)) % TABLE_SIZE;
}

void insertDoubleHashing(HashTable* ht, int key) {
    int h1 = hashFunction1(key);
    int h2 = hashFunction2(key);
    int i = 0;
    
    printf("Inserting %d: h1(%d) = %d, h2(%d) = %d\n", key, key, h1, key, h2);
    
    while (i < TABLE_SIZE) {
        int index = doubleHash(key, i);
        
        if (!ht->occupied[index]) {
            ht->table[index] = key;
            ht->occupied[index] = true;
            printf("Inserted %d at index %d (attempt %d)\n", key, index, i + 1);
            return;
        }
        
        printf("Collision at index %d (attempt %d), trying next position\n", index, i + 1);
        i++;
    }
    
    printf("Hash table is full, cannot insert %d\n", key);
}

int searchDoubleHashing(HashTable* ht, int key) {
    int h1 = hashFunction1(key);
    int h2 = hashFunction2(key);
    int i = 0;
    
    while (i < TABLE_SIZE) {
        int index = doubleHash(key, i);
        
        if (!ht->occupied[index]) {
            // Empty slot found, key doesn't exist
            return -1;
        }
        
        if (ht->table[index] == key) {
            return index;
        }
        
        i++;
    }
    
    return -1; // Key not found
}

void deleteKey(HashTable* ht, int key) {
    int index = searchDoubleHashing(ht, key);
    
    if (index != -1) {
        ht->table[index] = -1;
        ht->occupied[index] = false;
        printf("Key %d deleted from index %d\n", key, index);
    } else {
        printf("Key %d not found, cannot delete\n", key);
    }
}

void displayHashTable(HashTable* ht) {
    printf("\n--- Hash Table Contents ---\n");
    printf("Index\tValue\tStatus\n");
    printf("-----\t-----\t------\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t", i);
        if (ht->occupied[i]) {
            printf("%d\tOccupied\n", ht->table[i]);
        } else {
            printf("Empty\tEmpty\n");
        }
    }
    printf("---------------------------\n");
}

void demonstrateDoubleHashing() {
    printf("\n=== Double Hashing Demonstration ===\n");
    printf("Let's insert keys: 10, 22, 31, 4, 15, 28, 17, 88, 59\n\n");
    
    HashTable* demo_ht = createHashTable();
    int demo_keys[] = {10, 22, 31, 4, 15, 28, 17, 88, 59};
    int num_keys = sizeof(demo_keys) / sizeof(demo_keys[0]);
    
    for (int i = 0; i < num_keys; i++) {
        printf("\n--- Inserting %d ---\n", demo_keys[i]);
        insertDoubleHashing(demo_ht, demo_keys[i]);
    }
    
    displayHashTable(demo_ht);
    
    // Test searching
    printf("\n=== Search Demonstration ===\n");
    int search_keys[] = {22, 17, 99};
    for (int i = 0; i < 3; i++) {
        int result = searchDoubleHashing(demo_ht, search_keys[i]);
        if (result != -1) {
            printf("Key %d found at index %d\n", search_keys[i], result);
        } else {
            printf("Key %d not found\n", search_keys[i]);
        }
    }
    
    free(demo_ht->table);
    free(demo_ht->occupied);
    free(demo_ht);
}

void freeHashTable(HashTable* ht) {
    if (ht) {
        free(ht->table);
        free(ht->occupied);
        free(ht);
    }
}

int main() {
    printf("=== DOUBLE HASHING HASH TABLE ===\n");
    printf("Table Size: %d (Prime)\n", TABLE_SIZE);
    printf("Primary Hash: h1(key) = key %% %d\n", TABLE_SIZE);
    printf("Secondary Hash: h2(key) = %d - (key %% %d)\n", HASH2_PRIME, HASH2_PRIME);
    printf("Double Hash: (h1(key) + i * h2(key)) %% %d\n", TABLE_SIZE);
    
    HashTable* ht = createHashTable();
    int choice, key;
    
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Delete\n");
        printf("5. Demonstrate Double Hashing\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insertDoubleHashing(ht, key);
                break;
                
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                int result = searchDoubleHashing(ht, key);
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
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(ht, key);
                break;
                
            case 5:
                demonstrateDoubleHashing();
                break;
                
            case 6:
                printf("Exiting program...\n");
                freeHashTable(ht);
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
