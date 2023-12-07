#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct {
    int start;
    int end;
    int* data;
} Array;

void merge(Array* array) {
    int length = array->end - array->start + 1;
    int* result = malloc(length * sizeof(int));
    int mid = array->start + length / 2;
    int *left = array->data + array->start, *right = array->data + mid, *i = result;

    while(left != array->data + mid && right != array->data + array->end + 1) {
        if(*left <= *right) {
            *i = *left;
            ++left;
        } else {
            *i = *right;
            ++right;
        }
        ++i;
    }

    while(left != array->data + mid) {
        *i = *left;
        ++i; ++left;
    }

    while(right != array->data + array->end + 1) {
        *i = *right;
        ++i; ++right;
    }

    for(int j = 0; j < length; ++j) {
        array->data[array->start + j] = result[j];
    }

    free(result);
}

void* mergesort(void* args) {
    Array* array = args;
    int length = array->end - array->start + 1;
    if(length < 2)
        return NULL;

    int m = length / 2;
    Array array1 = {array->start, array->start + m - 1, array->data};
    Array array2 = {array->start + m, array->end, array->data};

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, mergesort, &array1);
    pthread_create(&thread2, NULL, mergesort, &array2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    merge(array);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error in arguments\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening the file: %s\n", argv[1]);
        return -1;
    }

    int n;
    fscanf(file, "%d", &n);
    int* values = malloc(n*sizeof(int));
    for(int i = 0; i < n; ++i) {
        fscanf(file, "%d", &values[i]);
    }
    fclose(file);

    Array array = {0, n - 1, values};

    struct timeval start, end;
    gettimeofday(&start, NULL);
    mergesort(&array);
    gettimeofday(&end, NULL);

    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    file = fopen(argv[2], "w");
    if (file == NULL) {
        printf("Error opening the file: %s\n", argv[2]);
        return -1;
    }

    printf("Sorted array: ");
     fprintf(file, "Sorted array: ");
    for(int i = 0; i < n; ++i) {
        fprintf(file, "%d ", values[i]);
        printf("%d ", values[i]);
    }
    fprintf(file, "\nTime : %f s\n", time_taken);
    printf("\nTime : %f s\n", time_taken);
    fclose(file);

    free(values);

    return 0;
}

