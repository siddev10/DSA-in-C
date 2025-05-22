/*8.	Implement following problems based on arrays
           a) i/p  {2,2,3,4}
              o/p 1
	        b) find the address of the array
            c) Find saddle point in matrix     
            d) Magic Square(check)
            e) Represent given matrix in its sparse form */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


// 8a: Check if array has elements with product equal to 1
int checkProduct(int arr[], int n) {
    int product = 1;
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }
    return (product == 1) ? 1 : 0;
}

// 8b: Find address of array
void findArrayAddress(int arr[], int n) {
    printf("Array base address: %p\n", (void*)arr);
    for (int i = 0; i < n; i++) {
        printf("arr[%d] address: %p, value: %d\n", i, (void*)&arr[i], arr[i]);
    }
}

// 8c: Find saddle point in matrix
void findSaddlePoint(int mat[][4], int rows, int cols) {
    printf("Searching for saddle points...\n");
    bool found = false;
    
    for (int i = 0; i < rows; i++) {
        int min_row = mat[i][0];
        int col_ind = 0;
        
        for (int j = 1; j < cols; j++) {
            if (min_row > mat[i][j]) {
                min_row = mat[i][j];
                col_ind = j;
            }
        }
        
        int k;
        for (k = 0; k < rows; k++) {
            if (mat[k][col_ind] > min_row)
                break;
        }
        
        if (k == rows) {
            printf("Saddle point found at (%d, %d): %d\n", i, col_ind, min_row);
            found = true;
        }
    }
    
    if (!found) {
        printf("No saddle point found\n");
    }
}

// 8d: Check Magic Square
bool isMagicSquare(int mat[][3], int n) {
    int sum = mat[0][0] + mat[0][1] + mat[0][2];
    
    // Check rows
    for (int i = 0; i < n; i++) {
        int rowSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += mat[i][j];
        }
        if (rowSum != sum) return false;
    }
    
    // Check columns
    for (int j = 0; j < n; j++) {
        int colSum = 0;
        for (int i = 0; i < n; i++) {
            colSum += mat[i][j];
        }
        if (colSum != sum) return false;
    }
    
    // Check diagonals
    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < n; i++) {
        diag1 += mat[i][i];
        diag2 += mat[i][n - 1 - i];
    }
    
    return (diag1 == sum && diag2 == sum);
}

// 8e: Sparse Matrix Representation
typedef struct {
    int row;
    int col;
    int value;
} SparseElement;

void createSparseMatrix(int mat[][4], int rows, int cols) {
    int nonZeroCount = 0;
    
    // Count non-zero elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] != 0) {
                nonZeroCount++;
            }
        }
    }
    
    SparseElement* sparse = (SparseElement*)malloc((nonZeroCount + 1) * sizeof(SparseElement));
    
    // Store matrix info
    sparse[0].row = rows;
    sparse[0].col = cols;
    sparse[0].value = nonZeroCount;
    
    int k = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] != 0) {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = mat[i][j];
                k++;
            }
        }
    }
    
    printf("Sparse Matrix Representation:\n");
    printf("Row\tCol\tValue\n");
    for (int i = 0; i <= nonZeroCount; i++) {
        printf("%d\t%d\t%d\n", sparse[i].row, sparse[i].col, sparse[i].value);
    }
    
    free(sparse);
}

int main() {
    printf("=== QUESTION 8: Array Problems ===\n");
    
    int choice;
    
    while (1) {
        printf("\n1. Check Product = 1\n2. Array Addresses\n3. Saddle Point\n4. Magic Square\n5. Sparse Matrix\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int n;
                printf("Enter array size: ");
                scanf("%d", &n);
                int* arr = (int*)malloc(n * sizeof(int));
                printf("Enter array elements: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                if (checkProduct(arr, n)) {
                    printf("Product of array elements is 1\n");
                } else {
                    printf("Product of array elements is not 1\n");
                }
                free(arr);
                break;
            }
            
            case 2: {
                int n;
                printf("Enter array size: ");
                scanf("%d", &n);
                int* arr = (int*)malloc(n * sizeof(int));
                printf("Enter array elements: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }
                findArrayAddress(arr, n);
                free(arr);
                break;
            }
            
            case 3: {
                int rows, cols;
                printf("Enter matrix dimensions (max 4x4): ");
                scanf("%d %d", &rows, &cols);
                int mat[4][4];
                printf("Enter matrix elements:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        scanf("%d", &mat[i][j]);
                    }
                }
                findSaddlePoint(mat, rows, cols);
                break;
            }
            
            case 4: {
                int mat[3][3];
                printf("Enter 3x3 matrix elements:\n");
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        scanf("%d", &mat[i][j]);
                    }
                }
                if (isMagicSquare(mat, 3)) {
                    printf("It is a Magic Square\n");
                } else {
                    printf("It is not a Magic Square\n");
                }
                break;
            }
            
            case 5: {
                int rows, cols;
                printf("Enter matrix dimensions (max 4x4): ");
                scanf("%d %d", &rows, &cols);
                int mat[4][4];
                printf("Enter matrix elements:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        scanf("%d", &mat[i][j]);
                    }
                }
                createSparseMatrix(mat, rows, cols);
                break;
            }
            
            case 6:
                exit(0);
                
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}

