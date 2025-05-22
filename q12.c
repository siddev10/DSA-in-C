// 12.	Implement Infix to prefix conversion and evaluate using stack.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct IntStack {
    int data;
    struct IntStack* next;
} IntStack;

void reverse(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}

void infixToPrefix(char* infix, char* prefix) {
    int n = strlen(infix);
    char temp[100];
    strcpy(temp, infix);
    
    // Reverse the infix expression
    reverse(temp);
    
    // Replace '(' with ')' and vice versa
    for (int i = 0; i < n; i++) {
        if (temp[i] == '(') temp[i] = ')';
        else if (temp[i] == ')') temp[i] = '(';
    }
    
    // Get postfix of modified expression
    infixToPostfix(temp, prefix);
    
    // Reverse the result to get prefix
    reverse(prefix);
}

int evaluatePrefix(char* prefix) {
    IntStack* stack = NULL;
    int n = strlen(prefix);
    
    for (int i = n - 1; i >= 0; i--) {
        if (prefix[i] >= '0' && prefix[i] <= '9') {
            pushInt(&stack, prefix[i] - '0');
        }
        else {
            int val1 = popInt(&stack);
            int val2 = popInt(&stack);
            
            switch (prefix[i]) {
                case '+': pushInt(&stack, val1 + val2); break;
                case '-': pushInt(&stack, val1 - val2); break;
                case '*': pushInt(&stack, val1 * val2); break;
                case '/': pushInt(&stack, val1 / val2); break;
            }
        }
    }
    
    return popInt(&stack);
}

int main() {
    printf("=== QUESTION 12: Infix to Prefix Conversion and Evaluation ===\n");
    
    char infix[100], prefix[100];
    int choice;
    
    while (1) {
        printf("\n1. Convert Infix to Prefix\n2. Evaluate Prefix\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;
                
            case 2:
                printf("Enter prefix expression (single digits only): ");
                scanf("%s", prefix);
                printf("Result: %d\n", evaluatePrefix(prefix));
                break;
                
            case 3:
                exit(0);
                
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// Stack structure for characters (operators and parentheses)
typedef struct CharStack {
    char data;
    struct CharStack* next;
} CharStack;

// Stack structure for integers (evaluation)
typedef struct IntStack {
    int data;
    struct IntStack* next;
} IntStack;

// Character stack operations
void pushChar(CharStack** top, char data) {
    CharStack* newNode = (CharStack*)malloc(sizeof(CharStack));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

char popChar(CharStack** top) {
    if (*top == NULL) return '\0';
    CharStack* temp = *top;
    char data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

char topChar(CharStack* top) {
    if (top == NULL) return '\0';
    return top->data;
}

bool isCharStackEmpty(CharStack* top) {
    return top == NULL;
}

// Integer stack operations
void pushInt(IntStack** top, int data) {
    IntStack* newNode = (IntStack*)malloc(sizeof(IntStack));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int popInt(IntStack** top) {
    if (*top == NULL) return INT_MIN;
    IntStack* temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

bool isIntStackEmpty(IntStack* top) {
    return top == NULL;
}

// Utility functions
bool isOperand(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

bool isRightAssociative(char op) {
    return op == '^';
}

void reverse(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}

// Convert infix to postfix (needed for prefix conversion)
void infixToPostfix(char* infix, char* postfix) {
    CharStack* stack = NULL;
    int i = 0, j = 0;
    int n = strlen(infix);
    
    while (i < n) {
        char c = infix[i];
        
        if (isOperand(c)) {
            postfix[j++] = c;
        }
        else if (c == '(') {
            pushChar(&stack, c);
        }
        else if (c == ')') {
            while (!isCharStackEmpty(stack) && topChar(stack) != '(') {
                postfix[j++] = popChar(&stack);
            }
            if (!isCharStackEmpty(stack)) {
                popChar(&stack); // Remove '('
            }
        }
        else if (isOperator(c)) {
            while (!isCharStackEmpty(stack) && 
                   topChar(stack) != '(' &&
                   (precedence(topChar(stack)) > precedence(c) ||
                    (precedence(topChar(stack)) == precedence(c) && !isRightAssociative(c)))) {
                postfix[j++] = popChar(&stack);
            }
            pushChar(&stack, c);
        }
        i++;
    }
    
    while (!isCharStackEmpty(stack)) {
        postfix[j++] = popChar(&stack);
    }
    
    postfix[j] = '\0';
}

// Convert infix to prefix
void infixToPrefix(char* infix, char* prefix) {
    int n = strlen(infix);
    char temp[100];
    strcpy(temp, infix);
    
    // Step 1: Reverse the infix expression
    reverse(temp);
    
    // Step 2: Replace '(' with ')' and vice versa
    for (int i = 0; i < n; i++) {
        if (temp[i] == '(') temp[i] = ')';
        else if (temp[i] == ')') temp[i] = '(';
    }
    
    // Step 3: Get postfix of modified expression
    infixToPostfix(temp, prefix);
    
    // Step 4: Reverse the result to get prefix
    reverse(prefix);
}

// Evaluate prefix expression
int evaluatePrefix(char* prefix) {
    IntStack* stack = NULL;
    int n = strlen(prefix);
    
    // Scan from right to left
    for (int i = n - 1; i >= 0; i--) {
        char c = prefix[i];
        
        if (c >= '0' && c <= '9') {
            // If operand, push to stack
            pushInt(&stack, c - '0');
        }
        else if (isOperator(c)) {
            // If operator, pop two operands and apply operation
            if (isIntStackEmpty(stack)) {
                printf("Error: Invalid prefix expression\n");
                return INT_MIN;
            }
            int val1 = popInt(&stack);
            
            if (isIntStackEmpty(stack)) {
                printf("Error: Invalid prefix expression\n");
                return INT_MIN;
            }
            int val2 = popInt(&stack);
            
            int result;
            switch (c) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Division by zero\n");
                        return INT_MIN;
                    }
                    result = val1 / val2; 
                    break;
                case '^': 
                    result = 1;
                    for (int p = 0; p < val2; p++) {
                        result *= val1;
                    }
                    break;
                default:
                    printf("Error: Invalid operator\n");
                    return INT_MIN;
            }
            pushInt(&stack, result);
        }
    }
    
    if (isIntStackEmpty(stack)) {
        printf("Error: Invalid prefix expression\n");
        return INT_MIN;
    }
    
    int finalResult = popInt(&stack);
    
    // Check if stack is empty (valid expression should have exactly one result)
    if (!isIntStackEmpty(stack)) {
        printf("Error: Invalid prefix expression\n");
        return INT_MIN;
    }
    
    return finalResult;
}

// Function to demonstrate step-by-step conversion
void demonstrateConversion(char* infix) {
    printf("\n=== Step-by-step Infix to Prefix Conversion ===\n");
    printf("Original infix: %s\n", infix);
    
    char temp[100];
    strcpy(temp, infix);
    
    // Step 1
    reverse(temp);
    printf("Step 1 - Reverse infix: %s\n", temp);
    
    // Step 2
    int n = strlen(temp);
    for (int i = 0; i < n; i++) {
        if (temp[i] == '(') temp[i] = ')';
        else if (temp[i] == ')') temp[i] = '(';
    }
    printf("Step 2 - Swap parentheses: %s\n", temp);
    
    // Step 3
    char postfix[100];
    infixToPostfix(temp, postfix);
    printf("Step 3 - Convert to postfix: %s\n", postfix);
    
    // Step 4
    reverse(postfix);
    printf("Step 4 - Reverse postfix: %s\n", postfix);
    printf("Final prefix expression: %s\n", postfix);
}

int main() {
    printf("=== QUESTION 12: Infix to Prefix Conversion and Evaluation ===\n");
    
    char infix[100], prefix[100];
    int choice;
    
    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Convert Infix to Prefix\n");
        printf("2. Evaluate Prefix Expression\n");
        printf("3. Demonstrate Step-by-step Conversion\n");
        printf("4. Run Test Cases\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter infix expression (no spaces): ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Infix expression: %s\n", infix);
                printf("Prefix expression: %s\n", prefix);
                break;
                
            case 2:
                printf("Enter prefix expression (single digits only, no spaces): ");
                scanf("%s", prefix);
                int result = evaluatePrefix(prefix);
                if (result != INT_MIN) {
                    printf("Prefix expression: %s\n", prefix);
                    printf("Evaluation result: %d\n", result);
                }
                break;
                
            case 3:
                printf("Enter infix expression (no spaces): ");
                scanf("%s", infix);
                demonstrateConversion(infix);
                break;
                
            case 4:
                printf("\n=== Test Cases ===\n");
                
                // Test Case 1
                strcpy(infix, "A+B*C");
                infixToPrefix(infix, prefix);
                printf("Infix: %s -> Prefix: %s\n", infix, prefix);
                
                // Test Case 2
                strcpy(infix, "(A+B)*C");
                infixToPrefix(infix, prefix);
                printf("Infix: %s -> Prefix: %s\n", infix, prefix);
                
                // Test Case 3
                strcpy(infix, "A+B*C-D");
                infixToPrefix(infix, prefix);
                printf("Infix: %s -> Prefix: %s\n", infix, prefix);
                
                // Test Case 4 - Evaluation
                printf("\nEvaluation Test Cases:\n");
                strcpy(prefix, "+12");
                printf("Prefix: %s -> Result: %d\n", prefix, evaluatePrefix(prefix));
                
                strcpy(prefix, "*+234");
                printf("Prefix: %s -> Result: %d\n", prefix, evaluatePrefix(prefix));
                
                strcpy(prefix, "-*+1234");
                printf("Prefix: %s -> Result: %d\n", prefix, evaluatePrefix(prefix));
                break;
                
            case 5:
                printf("Exiting program...\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please enter 1-5.\n");
        }
    }
    
    return 0;
}