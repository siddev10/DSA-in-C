// 1.	Implement insertion sort using singly linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
typedef struct Node1 {
    int data;
    struct Node1* next;
} Node1;

Node1* createNode1(int data) {
    Node1* newNode = (Node1*)malloc(sizeof(Node1));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertionSortLinkedList(Node1** head) {
    if (*head == NULL || (*head)->next == NULL) return;
    
    Node1* sorted = NULL;
    Node1* current = *head;
    
    while (current != NULL) {
        Node1* next = current->next;
        
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node1* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

void printList1(Node1* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void insertAtEnd1(Node1** head, int data) {
    Node1* newNode = createNode1(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node1* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}


int main() {
    Node1* head = NULL;
    int n, data;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd1(&head, data);
    }
    
    printf("Original list: ");
    printList1(head);
    
    insertionSortLinkedList(&head);
    
    printf("Sorted list: ");
    printList1(head);
    
    return 0;
}
