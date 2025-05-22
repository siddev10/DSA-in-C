// 11.	Implement Infix to postfix conversion and evaluate using stack.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

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
            return -1;
    }
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isOperand(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isRightAssociative(char op) {
    return op == '^';
}

// Power function for exponentiation
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// Convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    CharStack* stack = NULL;
    int k = 0;
    
    printf("\nStep-by-step conversion:\n");
    printf("%-10s %-15s %-15s %-15s\n", "Symbol", "Stack", "Postfix", "Action");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; infix[i]; i++) {
        char current = infix[i];
        
        // Skip spaces
        if (isspace(current)) continue;
        
        if (isOperand(current)) {
            postfix[k++] = current;
            printf("%-10c %-15s %-15s %-15s\n", current, 
                   stack ? "..." : "empty", postfix, "Add to output");
        }
        else if (current == '(') {
            pushChar(&stack, current);
            printf("%-10c %-15s %-15s %-15s\n", current, 
                   "(...", postfix, "Push to stack");
        }
        else if (current == ')') {
            while (stack != NULL && topChar(stack) != '(') {
                postfix[k++] = popChar(&stack);
            }
            if (stack != NULL) {
                popChar(&stack); // Remove '('
            }
            printf("%-10c %-15s %-15s %-15s\n", current, 
                   stack ? "..." : "empty", postfix, "Pop until '('");
        }
        else if (isOperator(current)) {
            while (stack != NULL && topChar(stack) != '(' &&
                   (precedence(current) < precedence(topChar(stack)) ||
                    (precedence(current) == precedence(topChar(stack)) && !isRightAssociative(current)))) {
                postfix[k++] = popChar(&stack);
            }
            pushChar(&stack, current);
            printf("%-10c %-15s %-15s %-15s\n", current, 
                   "...", postfix, "Process operator");
        }
    }
    
    // Pop remaining operators
    while (stack != NULL) {
        postfix[k++] = popChar(&stack);
    }
    
    postfix[k] = '\0';
    printf("%-10s %-15s %-15s %-15s\n", "END", "empty", postfix, "Pop remaining");
}

// Evaluate postfix expression
int evaluatePostfix(char* postfix) {
    IntStack* stack = NULL;
    
    printf("\nStep-by-step evaluation:\n");
    printf("%-10s %-15s %-15s\n", "Symbol", "Stack", "Operation");
    printf("-----------------------------------------\n");
    
    for (int i = 0; postfix[i]; i++) {
        char current = postfix[i];
        
        if (current >= '0' && current <= '9') {
            int value = current - '0';
            pushInt(&stack, value);
            printf("%-10c %-15d %-15s\n", current, value, "Push operand");
        }
        else if (isOperator(current)) {
            if (isIntStackEmpty(stack)) {
                printf("Error: Invalid postfix expression - insufficient operands\n");
                return INT_MIN;
            }
            int val1 = popInt(&stack);
            
            if (isIntStackEmpty(stack)) {
                printf("Error: Invalid postfix expression - insufficient operands\n");
                return INT_MIN;
            }
            int val2 = popInt(&stack);
            
            int result;
            char operation[50];
            
            switch (current) {
                case '+': 
                    result = val2 + val1; 
                    sprintf(operation, "%d + %d = %d", val2, val1, result);
                    break;
                case '-': 
                    result = val2 - val1; 
                    sprintf(operation, "%d - %d = %d", val2, val1, result);
                    break;
                case '*': 
                    result = val2 * val1; 
                    sprintf(operation, "%d * %d = %d", val2, val1, result);
                    break;
                case '/': 
                    if (val1 == 0) {
                        printf("Error: Division by zero\n");
                        return INT_MIN;
                    }
                    result = val2 / val1; 
                    sprintf(operation, "%d / %d = %d", val2, val1, result);
                    break;
                case '^': 
                    result = power(val2, val1); 
                    sprintf(operation, "%d ^ %d = %d", val2, val1, result);
                    break;
                default:
                    printf("Error: Invalid operator %c\n", current);
                    return INT_MIN;
            }
            
            pushInt(&stack, result);
            printf("%-10c %-15d %-15s\n", current, result, operation);
        }
    }
    
    if (isIntStackEmpty(stack)) {
        printf("Error: Invalid postfix expression - no result\n");
        return INT_MIN;
    }
    
    int finalResult = popInt(&stack);
    
    if (!isIntStackEmpty(stack)) {
        printf("Error: Invalid postfix expression - multiple results\n");
        return INT_MIN;
    }
    
    return finalResult;
}

// Function to validate infix expression
bool isValidInfix(char* infix) {
    int parentheses = 0;
    bool lastWasOperator = true; // Start as true to allow operand at beginning
    
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        
        if (isspace(c)) continue;
        
        if (c == '(') {
            parentheses++;
            lastWasOperator = true;
        }
        else if (c == ')') {
            parentheses--;
            if (parentheses < 0) return false;
            lastWasOperator = false;
        }
        else if (isOperand(c)) {
            if (!lastWasOperator && i > 0 && !isspace(infix[i-1])) {
                // Two consecutive operands without operator
                return false;
            }
            lastWasOperator = false;
        }
        else if (isOperator(c)) {
            if (lastWasOperator && c != '-' && c != '+') {
                // Two consecutive operators (except unary minus/plus)
                return false;
            }
            lastWasOperator = true;
        }
        else {
            // Invalid character
            return false;
        }
    }
    
    return parentheses == 0 && !lastWasOperator;
}

// Function to run test cases
void runTestCases() {
    printf("\n=== Test Cases ===\n");
    
    char testCases[][20] = {
        "A+B*C",
        "(A+B)*C",
        "A+B*C-D/E",
        "A^B^C",
        "((A+B)*C-D)/E",
        "234*+",  // This is actually postfix for testing evaluation
    };
    
    char postfix[100];
    
    for (int i = 0; i < 5; i++) {
        printf("\nTest Case %d: %s\n", i+1, testCases[i]);
        if (isValidInfix(testCases[i])) {
            infixToPostfix(testCases[i], postfix);
            printf("Result: %s\n", postfix);
        } else {
            printf("Invalid infix expression\n");
        }
    }
    
    // Test evaluation with numeric postfix
    printf("\nEvaluation Test Cases:\n");
    char evalTests[][20] = {"23+", "23*4+", "234*+", "52/3-", "23^"};
    
    for (int i = 0; i < 5; i++) {
        printf("\nEvaluating: %s\n", evalTests[i]);
        int result = evaluatePostfix(evalTests[i]);
        if (result != INT_MIN) {
            printf("Final Result: %d\n", result);
        }
    }
}

int main() {
    printf("=== QUESTION 11: Infix to Postfix Conversion and Evaluation ===\n");
    
    char infix[100], postfix[100];
    int choice;
    
    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Convert Infix to Postfix (with steps)\n");
        printf("2. Evaluate Postfix Expression (with steps)\n");
        printf("3. Convert and Evaluate in one go\n");
        printf("4. Run Test Cases\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter infix expression (no spaces): ");
                scanf("%s", infix);
                
                if (!isValidInfix(infix)) {
                    printf("Error: Invalid infix expression!\n");
                    break;
                }
                
                printf("\nOriginal infix: %s\n", infix);
                infixToPostfix(infix, postfix);
                printf("\nFinal postfix expression: %s\n", postfix);
                break;
                
            case 2:
                printf("Enter postfix expression (single digits only, no spaces): ");
                scanf("%s", postfix);
                
                printf("\nPostfix expression: %s\n", postfix);
                int result = evaluatePostfix(postfix);
                if (result != INT_MIN) {
                    printf("\nFinal evaluation result: %d\n", result);
                }
                break;
                
            case 3:
                printf("Enter infix expression (single digits only, no spaces): ");
                scanf("%s", infix);
                
                if (!isValidInfix(infix)) {
                    printf("Error: Invalid infix expression!\n");
                    break;
                }
                
                printf("\n=== CONVERSION PHASE ===\n");
                printf("Infix: %s\n", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix: %s\n", postfix);
                
                printf("\n=== EVALUATION PHASE ===\n");
                int evalResult = evaluatePostfix(postfix);
                if (evalResult != INT_MIN) {
                    printf("\nFinal Result: %s = %d\n", infix, evalResult);
                }
                break;
                
            case 4:
                runTestCases();
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