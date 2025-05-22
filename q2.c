// 2.	Implement bubble sort using Doubly linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct DNode {
    int data;
    struct DNode* next;
    struct DNode* prev;
} DNode;

DNode* createDNode(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtEndD(DNode** head, int data) {
    DNode* newNode = createDNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    DNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void bubbleSortDoublyLinkedList(DNode** head) {
    if (*head == NULL) return;
    
    bool swapped;
    DNode* ptr1;
    DNode* lptr = NULL;
    
    do {
        swapped = false;
        ptr1 = *head;
        
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void printDList(DNode* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {    
    DNode* head = NULL;
    int n, data;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEndD(&head, data);
    }
    
    printf("Original list: ");
    printDList(head);
    
    bubbleSortDoublyLinkedList(&head);
    
    printf("Sorted list: ");
    printDList(head);
    
    return 0;
}
