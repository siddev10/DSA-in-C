/*16.	Write a program to create a Binary search tree and perform following non recursive operations on it.
a.	In order       b. Post order       c. display total nodes    d. display leaf nodes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// BST Node structure
typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Stack Node structure for storing BST nodes
typedef struct StackNode {
    BSTNode* data;
    struct StackNode* next;
} StackNode;

// Stack operations
void push(StackNode** top, BSTNode* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
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
        if (newNode == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
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

// Non-recursive inorder traversal
void inorderNonRecursive(BSTNode* root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return;
    }
    
    StackNode* stack = NULL;
    BSTNode* current = root;
    
    printf("Inorder traversal steps:\n");
    int step = 1;
    
    while (current != NULL || !isEmpty(stack)) {
        // Go to the leftmost node of current
        while (current != NULL) {
            printf("Step %d: Push %d to stack, go left\n", step++, current->data);
            push(&stack, current);
            current = current->left;
        }
        
        // Current must be NULL at this point
        current = pop(&stack);
        if (current != NULL) {
            printf("Step %d: Pop and visit %d\n", step++, current->data);
            printf("%d ", current->data);
            
            // We have visited the node and its left subtree, now visit right subtree
            current = current->right;
        }
    }
}

// Recursive inorder traversal for comparison
void inorderRecursive(BSTNode* root) {
    if (root != NULL) {
        inorderRecursive(root->left);
        printf("%d ", root->data);
        inorderRecursive(root->right);
    }
}

// Utility function to display tree structure
void displayTree(BSTNode* root, int space) {
    const int COUNT = 10;
    if (root == NULL) return;
    
    space += COUNT;
    displayTree(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    
    displayTree(root->left, space);
}

// Function to find minimum value in BST
BSTNode* findMin(BSTNode* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to find maximum value in BST
BSTNode* findMax(BSTNode* root) {
    if (root == NULL) return NULL;
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Function to search for a value in BST
BSTNode* search(BSTNode* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    
    if (key < root->data) {
        return search(root->left, key);
    }
    
    return search(root->right, key);
}

// Function to count total nodes
int countNodes(BSTNode* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to find height of tree
int height(BSTNode* root) {
    if (root == NULL) return -1;
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Free BST memory
void freeBST(BSTNode* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main() {
    printf("=== BST Inorder Non-Recursive Traversal ===\n");
    
    BSTNode* root = NULL;
    int data, choice, searchKey;
    
    // Insert sample data or get user input
    printf("Enter elements for BST (enter -1 to stop): ");
    while (1) {
        scanf("%d", &data);
        if (data == -1) break;
        root = insertBST(root, data);
    }
    
    if (root == NULL) {
        printf("No elements entered. Creating sample BST...\n");
        int sampleData[] = {50, 30, 70, 20, 40, 60, 80};
        int n = sizeof(sampleData) / sizeof(sampleData[0]);
        
        for (int i = 0; i < n; i++) {
            root = insertBST(root, sampleData[i]);
        }
        printf("Sample BST created with elements: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", sampleData[i]);
        }
        printf("\n");
    }
    
    while (1) {
        printf("\n=== BST Operations Menu ===\n");
        printf("1. Inorder Traversal (Non-Recursive with steps)\n");
        printf("2. Inorder Traversal (Non-Recursive simple)\n");
        printf("3. Inorder Traversal (Recursive for comparison)\n");
        printf("4. Display Tree Structure\n");
        printf("5. Search for a value\n");
        printf("6. Find Minimum and Maximum\n");
        printf("7. Tree Statistics (Count, Height)\n");
        printf("8. Insert new element\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\n=== Non-Recursive Inorder Traversal (with steps) ===\n");
                inorderNonRecursive(root);
                printf("\n");
                break;
                
            case 2:
                printf("\n=== Non-Recursive Inorder Traversal (simple) ===\n");
                printf("Inorder: ");
                // Simple version without step-by-step display
                {
                    StackNode* stack = NULL;
                    BSTNode* current = root;
                    
                    while (current != NULL || !isEmpty(stack)) {
                        while (current != NULL) {
                            push(&stack, current);
                            current = current->left;
                        }
                        current = pop(&stack);
                        if (current != NULL) {
                            printf("%d ", current->data);
                            current = current->right;
                        }
                    }
                }
                printf("\n");
                break;
                
            case 3:
                printf("\n=== Recursive Inorder Traversal ===\n");
                printf("Inorder: ");
                inorderRecursive(root);
                printf("\n");
                break;
                
            case 4:
                printf("\n=== Tree Structure ===\n");
                displayTree(root, 0);
                break;
                
            case 5:
                printf("Enter value to search: ");
                scanf("%d", &searchKey);
                BSTNode* found = search(root, searchKey);
                if (found != NULL) {
                    printf("Value %d found in the BST!\n", searchKey);
                } else {
                    printf("Value %d not found in the BST.\n", searchKey);
                }
                break;
                
            case 6:
                {
                    BSTNode* minNode = findMin(root);
                    BSTNode* maxNode = findMax(root);
                    if (minNode) printf("Minimum value: %d\n", minNode->data);
                    if (maxNode) printf("Maximum value: %d\n", maxNode->data);
                }
                break;
                
            case 7:
                printf("Total nodes: %d\n", countNodes(root));
                printf("Tree height: %d\n", height(root));
                break;
                
            case 8:
                printf("Enter new element to insert: ");
                scanf("%d", &data);
                root = insertBST(root, data);
                printf("Element %d inserted successfully!\n", data);
                break;
                
            case 9:
                printf("Freeing memory and exiting...\n");
                freeBST(root);
                exit(0);
                
            default:
                printf("Invalid choice! Please enter 1-9.\n");
        }
    }
    
    return 0;
}