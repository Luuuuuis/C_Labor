//
// Created by LUIBROS on 26.06.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100000

long long GetUSecClock() {
    clock_t cputime = clock();
    return (long long) cputime * 1000000 / CLOCKS_PER_SEC;
}

int *read() {
    FILE *file;
    int *numbers = (int *) malloc(MAX_NUMBERS * sizeof(int));
    int count = 0;

    file = fopen("C:\\Users\\LUIBROS\\Uni\\2. Semester\\Labor\\07_sort_comp\\numbers100000.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    while (count < MAX_NUMBERS && fscanf(file, "%d", &numbers[count]) == 1) {
        count++;
    }

    fclose(file);
    printf("Read %d numbers.\n", count);
    return numbers;
}


void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap arr[i] and arr[minIndex]
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void insertionSort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// MergeSort function
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char *argv[]) {
    int *numbers = read();

    printf("Welchen Sortier Algorithmus wollen Sie verwenden?\n"
           "1. Bubble Sort\n"
           "2. Selection Sort\n"
           "3. Insert Sort\n"
           "4. Merge Sort\n"
           "5. Quick Sort\n");
    int choice = 0;
    scanf("%d", &choice);

    long long start = GetUSecClock();

    switch (choice) {
        case 1:
            bubbleSort(numbers, MAX_NUMBERS);
            break;
        case 2:
            selectionSort(numbers, MAX_NUMBERS);
            break;
        case 3:
            insertionSort(numbers, MAX_NUMBERS);
            break;
        case 4:
            mergeSort(numbers, 0, MAX_NUMBERS - 1);
            break;
        case 5:
            printf("Quick Sort\n");
            quickSort(numbers, 0, MAX_NUMBERS - 1);
            break;
        default:
            printf("Ungültige Eingabe.\n");
            break;
    }

    long long end = GetUSecClock();

    long long time_taken = end - start;

    if (numbers != NULL) {
        printf("Returned Array:\n");
        for (int i = 0; i < 5; i++) {
            printf("%d\n", numbers[i]);
        }

        printf("...\n");

        for (int i = MAX_NUMBERS - 10; i < MAX_NUMBERS; i++) {
            printf("%d\n", numbers[i]);
        }
        printf("\n");

        printf("Time taken in mircosekunden: %lld\n", time_taken);

        free(numbers); // Remember to free the dynamically allocated memory
    }
}