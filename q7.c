// 7.	WAP to implement insertion sort, merge sort, bubble sort on 1 D array of student structure (contains student_ name, roll_no, total marks) with keys as students_roll_no and count the number of swap performed.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


typedef struct Student {
    char name[50];
    int roll_no;
    int total_marks;
} Student;

void insertionSortStudents(Student arr[], int n, int* swaps) {
    *swaps = 0;
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j].roll_no > key.roll_no) {
            arr[j + 1] = arr[j];
            j = j - 1;
            (*swaps)++;
        }
        arr[j + 1] = key;
    }
}

void bubbleSortStudents(Student arr[], int n, int* swaps) {
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].roll_no > arr[j + 1].roll_no) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*swaps)++;
            }
        }
    }
}

void mergeStudents(Student arr[], int l, int m, int r, int* swaps) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    Student* L = (Student*)malloc(n1 * sizeof(Student));
    Student* R = (Student*)malloc(n2 * sizeof(Student));
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i].roll_no <= R[j].roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            (*swaps)++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSortStudents(Student arr[], int l, int r, int* swaps) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortStudents(arr, l, m, swaps);
        mergeSortStudents(arr, m + 1, r, swaps);
        mergeStudents(arr, l, m, r, swaps);
    }
}

void displayStudents(Student arr[], int n) {
    printf("\nRoll No\tName\t\tMarks\n");
    printf("--------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%d\n", arr[i].roll_no, arr[i].name, arr[i].total_marks);
    }
}


int main() {
    printf("=== QUESTION 7: Sorting Student Structure with Swap Count ===\n");
    
    int n, choice, swaps;
    printf("Enter number of students: ");
    scanf("%d", &n);
    
    Student* students = (Student*)malloc(n * sizeof(Student));
    
    printf("Enter student details:\n");
    for (int i = 0; i < n; i++) {
        printf("Student %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &students[i].roll_no);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Total Marks: ");
        scanf("%d", &students[i].total_marks);
    }
    
    printf("\nOriginal data:");
    displayStudents(students, n);
    
    printf("\n1. Insertion Sort\n2. Bubble Sort\n3. Merge Sort\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            insertionSortStudents(students, n, &swaps);
            printf("\nAfter Insertion Sort:");
            displayStudents(students, n);
            printf("Number of swaps: %d\n", swaps);
            break;
            
        case 2:
            bubbleSortStudents(students, n, &swaps);
            printf("\nAfter Bubble Sort:");
            displayStudents(students, n);
            printf("Number of swaps: %d\n", swaps);
            break;
            
        case 3:
            mergeSortStudents(students, 0, n - 1, &swaps);
            printf("\nAfter Merge Sort:");
            displayStudents(students, n);
            printf("Number of swaps: %d\n", swaps);
            break;
            
        default:
            printf("Invalid choice\n");
    }
    
    free(students);
    return 0;
}
