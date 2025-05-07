#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void parallel_reduction_max_sum(int* data, int size, int* max_val_ptr, int* sum_val_ptr) {
    int max_val = data[0];
    long long sum_val = 0;

    // Parallel reduction for max and sum
    #pragma omp parallel for reduction(max:max_val) reduction(+:sum_val)
    for (int i = 0; i < size; i++) {
        if (data[i] > max_val)
            max_val = data[i];
        sum_val += data[i];
    }

    *max_val_ptr = max_val;
    *sum_val_ptr = (int)sum_val;  // you might want to keep this long long to avoid overflow for big data
}

int main() {
    int data_size = 1000000;
    int* data = (int*)malloc(data_size * sizeof(int));

    for (int i = 0; i < data_size; i++) {
        data[i] = rand() % 100; // Random values between 0 and 99
    }

    int max_val, sum_val;

    double start_time = omp_get_wtime();
    parallel_reduction_max_sum(data, data_size, &max_val, &sum_val);
    double end_time = omp_get_wtime();

    printf("Maximum value: %d\n", max_val);
    printf("Sum value: %d\n", sum_val);
    printf("Execution time: %.4f seconds\n", end_time - start_time);

    free(data);
    return 0;
}
