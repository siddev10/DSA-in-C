//20.	Implement Push and pop operations of stacks on doubly linked lists
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Stack structure using doubly linked list
typedef struct Stack {
    Node* top;    // Points to top of stack (last inserted element)
    int size;     // Current size of stack
} Stack;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to create an empty stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

// Function to check if stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to get current size of stack
int getSize(Stack* stack) {
    return stack->size;
}

// PUSH operation - Add element to top of stack
void push(Stack* stack, int data) {
    Node* newNode = createNode(data);
    if (!newNode) {
        return;
    }
    
    if (isEmpty(stack)) {
        // First element - stack is empty
        stack->top = newNode;
    } else {
        // Add to top of existing stack
        newNode->prev = stack->top;  // New node's prev points to current top
        stack->top->next = newNode;  // Current top's next points to new node
        stack->top = newNode;        // Update top to new node
    }
    
    stack->size++;
    printf("Pushed %d onto stack. Stack size: %d\n", data, stack->size);
}

// POP operation - Remove and return top element
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow! Cannot pop from empty stack.\n");
        return -1;  // Return -1 to indicate error
    }
    
    Node* topNode = stack->top;
    int poppedData = topNode->data;
    
    if (stack->size == 1) {
        // Only one element in stack
        stack->top = NULL;
    } else {
        // More than one element
        stack->top = topNode->prev;  // Move top to previous node
        stack->top->next = NULL;     // Remove link to popped node
    }
    
    free(topNode);  // Free memory of popped node
    stack->size--;
    
    printf("Popped %d from stack. Stack size: %d\n", poppedData, stack->size);
    return poppedData;
}

// PEEK operation - View top element without removing
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    
    printf("Top element: %d\n", stack->top->data);
    return stack->top->data;
}

// Function to display entire stack (top to bottom)
void displayStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    
    printf("\n--- Stack Contents (Top to Bottom) ---\n");
    printf("Size: %d\n", stack->size);
    printf("Stack: ");
    
    Node* current = stack->top;
    while (current != NULL) {
        printf("[%d]", current->data);
        if (current->prev != NULL) {
            printf(" -> ");
        }
        current = current->prev;
    }
    printf(" -> NULL\n");
    printf("--------------------------------------\n");
}

// Function to display stack from bottom to top (using doubly linked list advantage)
void displayStackBottomToTop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    
    // Find the bottom node (first inserted)
    Node* bottom = stack->top;
    while (bottom->prev != NULL) {
        bottom = bottom->prev;
    }
    
    printf("\n--- Stack Contents (Bottom to Top) ---\n");
    printf("Stack: ");
    
    Node* current = bottom;
    while (current != NULL) {
        printf("[%d]", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> TOP\n");
    printf("--------------------------------------\n");
}

// Function to clear entire stack
void clearStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    printf("Stack cleared successfully!\n");
}

// Function to free stack memory
void freeStack(Stack* stack) {
    clearStack(stack);
    free(stack);
    printf("Stack memory freed!\n");
}

// Demonstration function
void demonstrateStack() {
    printf("\n=== Stack Demonstration ===\n");
    Stack* demo = createStack();
    
    printf("1. Pushing elements: 10, 20, 30, 40, 50\n");
    push(demo, 10);
    push(demo, 20);
    push(demo, 30);
    push(demo, 40);
    push(demo, 50);
    
    displayStack(demo);
    displayStackBottomToTop(demo);
    
    printf("\n2. Peek operation:\n");
    peek(demo);
    
    printf("\n3. Pop operations:\n");
    pop(demo);
    pop(demo);
    displayStack(demo);
    
    printf("\n4. Push more elements: 60, 70\n");
    push(demo, 60);
    push(demo, 70);
    displayStack(demo);
    
    freeStack(demo);
}

int main() {
    printf("=== STACK IMPLEMENTATION USING DOUBLY LINKED LIST ===\n");
    printf("Operations: Push (add to top), Pop (remove from top)\n");
    printf("Advantage: Can traverse both directions due to doubly linked structure\n\n");
    
    Stack* stack = createStack();
    int choice, value;
    
    while (1) {
        printf("\n=== STACK MENU ===\n");
        printf("1. Push (Add element)\n");
        printf("2. Pop (Remove element)\n");
        printf("3. Peek (View top element)\n");
        printf("4. Display Stack (Top to Bottom)\n");
        printf("5. Display Stack (Bottom to Top)\n");
        printf("6. Check if Empty\n");
        printf("7. Get Stack Size\n");
        printf("8. Clear Stack\n");
        printf("9. Demonstrate Stack\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(stack, value);
                break;
                
            case 2:
                pop(stack);
                break;
                
            case 3:
                peek(stack);
                break;
                
            case 4:
                displayStack(stack);
                break;
                
            case 5:
                displayStackBottomToTop(stack);
                break;
                
            case 6:
                if (isEmpty(stack)) {
                    printf("Stack is empty.\n");
                } else {
                    printf("Stack is not empty. Size: %d\n", getSize(stack));
                }
                break;
                
            case 7:
                printf("Current stack size: %d\n", getSize(stack));
                break;
                
            case 8:
                clearStack(stack);
                break;
                
            case 9:
                demonstrateStack();
                break;
                
            case 10:
                printf("Exiting program...\n");
                freeStack(stack);
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}