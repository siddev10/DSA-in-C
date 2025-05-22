/* 6.	WAP to implement following by using stack 
        a.	Factorial of a given number
        b.	Generation of Fibonacci series*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


typedef struct IntStack {
    int data;
    struct IntStack* next;
} IntStack;

void pushInt(IntStack** top, int data) {
    IntStack* newNode = (IntStack*)malloc(sizeof(IntStack));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int popInt(IntStack** top) {
    if (*top == NULL) return -1;
    IntStack* temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

long long factorialUsingStack(int n) {
    IntStack* stack = NULL;
    
    for (int i = 1; i <= n; i++) {
        pushInt(&stack, i);
    }
    
    long long result = 1;
    while (stack != NULL) {
        result *= popInt(&stack);
    }
    
    return result;
}

void fibonacciUsingStack(int n) {
    if (n <= 0) return;
    
    IntStack* stack = NULL;
    
    if (n >= 1) pushInt(&stack, 0);
    if (n >= 2) pushInt(&stack, 1);
    
    for (int i = 2; i < n; i++) {
        int b = popInt(&stack);
        int a = popInt(&stack);
        int c = a + b;
        pushInt(&stack, b);
        pushInt(&stack, c);
    }
    
    printf("Fibonacci series: ");
    int* temp = (int*)malloc(n * sizeof(int));
    int index = 0;
    
    while (stack != NULL) {
        temp[index++] = popInt(&stack);
    }
    
    for (int i = index - 1; i >= 0; i--) {
        printf("%d ", temp[i]);
    }
    printf("\n");
    free(temp);
}

int main() {
    printf("=== QUESTION 6: Stack Implementation for Factorial and Fibonacci ===\n");
    
    int choice, n;
    
    while (1) {
        printf("\n1. Factorial\n2. Fibonacci\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter number for factorial: ");
                scanf("%d", &n);
                printf("Factorial of %d = %lld\n", n, factorialUsingStack(n));
                break;
                
            case 2:
                printf("Enter number of terms for Fibonacci: ");
                scanf("%d", &n);
                fibonacciUsingStack(n);
                break;
                
            case 3:
                exit(0);
                
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}

