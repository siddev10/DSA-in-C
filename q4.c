// 4.	Write a program to illustrate operations on BST holding numeric keys. The menu must include insert, find, mirror image.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>



typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* createBSTNode(int data) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTNode* insertBST(BSTNode* root, int data) {
    if (root == NULL) {
        return createBSTNode(data);
    }
    
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    } else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }
    
    return root;
}

BSTNode* findBST(BSTNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return findBST(root->left, data);
    }
    
    return findBST(root->right, data);
}

void mirrorBST(BSTNode* root) {
    if (root == NULL) return;
    
    BSTNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirrorBST(root->left);
    mirrorBST(root->right);
}

void inorderBST(BSTNode* root) {
    if (root != NULL) {
        inorderBST(root->left);
        printf("%d ", root->data);
        inorderBST(root->right);
    }
}


int main() {

    BSTNode* root = NULL;
    int choice, data;
    
    while (1) {
        printf("\n1. Insert\n2. Find\n3. Mirror\n4. Display (Inorder)\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insertBST(root, data);
                printf("Inserted %d\n", data);
                break;
                
            case 2:
                printf("Enter data to find: ");
                scanf("%d", &data);
                if (findBST(root, data)) {
                    printf("%d found in BST\n", data);
                } else {
                    printf("%d not found in BST\n", data);
                }
                break;
                
            case 3:
                mirrorBST(root);
                printf("BST mirrored\n");
                break;
                
            case 4:
                printf("Inorder traversal: ");
                inorderBST(root);
                printf("\n");
                break;
                
            case 5:
                exit(0);
                
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}
