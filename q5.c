// 5.	Write a program to create a Binary search tree and perform following non recursive operations on it.
//      a.	Pre-order       b. Post order       c. display total nodes    d. display leaf nodes.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// BST Node structure
typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Stack Node structure for non-recursive operations
typedef struct StackNode {
    BSTNode* data;
    struct StackNode* next;
} StackNode;

// Stack operations
void push(StackNode** top, BSTNode* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

BSTNode* pop(StackNode** top) {
    if (*top == NULL) return NULL;
    StackNode* temp = *top;
    BSTNode* data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

bool isEmpty(StackNode* top) {
    return top == NULL;
}

// BST insertion function
BSTNode* insertBST(BSTNode* root, int data) {
    if (root == NULL) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    } else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }
    // If data equals root->data, we don't insert (no duplicates)
    
    return root;
}

// Non-recursive preorder traversal
void preorderNonRecursive(BSTNode* root) {
    if (root == NULL) return;
    
    StackNode* stack = NULL;
    push(&stack, root);
    
    while (!isEmpty(stack)) {
        BSTNode* current = pop(&stack);
        printf("%d ", current->data);
        
        // Push right first, then left (so left is processed first)
        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
}

// Non-recursive postorder traversal using two stacks
void postorderNonRecursive(BSTNode* root) {
    if (root == NULL) return;
    
    StackNode* stack1 = NULL;
    StackNode* stack2 = NULL;
    
    push(&stack1, root);
    
    while (!isEmpty(stack1)) {
        BSTNode* current = pop(&stack1);
        push(&stack2, current);
        
        if (current->left) push(&stack1, current->left);
        if (current->right) push(&stack1, current->right);
    }
    
    while (!isEmpty(stack2)) {
        BSTNode* current = pop(&stack2);
        printf("%d ", current->data);
    }
}

// Count total nodes using non-recursive approach
int totalNodes(BSTNode* root) {
    if (root == NULL) return 0;
    
    StackNode* stack = NULL;
    push(&stack, root);
    int count = 0;
    
    while (!isEmpty(stack)) {
        BSTNode* current = pop(&stack);
        count++;
        
        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
    
    return count;
}

// Count leaf nodes using non-recursive approach
int leafNodes(BSTNode* root) {
    if (root == NULL) return 0;
    
    StackNode* stack = NULL;
    push(&stack, root);
    int count = 0;
    
    while (!isEmpty(stack)) {
        BSTNode* current = pop(&stack);
        
        if (current->left == NULL && current->right == NULL) {
            count++;
        }
        
        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
    
    return count;
}

// Utility function to display the tree structure (for testing)
void inorderRecursive(BSTNode* root) {
    if (root != NULL) {
        inorderRecursive(root->left);
        printf("%d ", root->data);
        inorderRecursive(root->right);
    }
}

// Free the BST memory
void freeBST(BSTNode* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

// MAIN FUNCTION FOR QUESTION 5
int main() {
    
    BSTNode* root = NULL;
    int choice, data;
    
    // Insert some sample data
    printf("Enter elements for BST (enter -1 to stop): ");
    while (1) {
        scanf("%d", &data);
        if (data == -1) break;
        root = insertBST(root, data);
    }
    
    // Display the BST in sorted order for reference
    printf("\nBST created successfully!");
    printf("\nInorder traversal (sorted): ");
    inorderRecursive(root);
    printf("\n");
    
    while (1) {
        printf("\n=== BST Operations Menu ===\n");
        printf("1. Preorder Traversal (Non-recursive)\n");
        printf("2. Postorder Traversal (Non-recursive)\n");
        printf("3. Count Total Nodes\n");
        printf("4. Count Leaf Nodes\n");
        printf("5. Display Inorder (for reference)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Preorder traversal: ");
                preorderNonRecursive(root);
                printf("\n");
                break;
                
            case 2:
                printf("Postorder traversal: ");
                postorderNonRecursive(root);
                printf("\n");
                break;
                
            case 3:
                printf("Total nodes: %d\n", totalNodes(root));
                break;
                
            case 4:
                printf("Leaf nodes: %d\n", leafNodes(root));
                break;
                
            case 5:
                printf("Inorder traversal: ");
                inorderRecursive(root);
                printf("\n");
                break;
                
            case 6:
                printf("Freeing memory and exiting...\n");
                freeBST(root);
                exit(0);
                
            default:
                printf("Invalid choice! Please enter a number between 1-6.\n");
        }
    }
    
    return 0;
}