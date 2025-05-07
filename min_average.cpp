#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void parallel_reduction_min_avg(int* data, int data_size, int* min_val_ptr, double* avg_val_ptr) {
    int min_val = data[0];
    long long sum_val = 0;

    #pragma omp parallel for reduction(min:min_val) reduction(+:sum_val)
    for (int i = 0; i < data_size; i++) {
        if (data[i] < min_val)
            min_val = data[i];
        sum_val += data[i];
    }

    *min_val_ptr = min_val;
    *avg_val_ptr = (double)sum_val / data_size;
}

int main() {
    int data_size = 1000000;
    int* data = (int*)malloc(data_size * sizeof(int));

    for (int i = 0; i < data_size; i++) {
        data[i] = rand() % 100; // Random values from 0 to 99
    }

    int min_val;
    double avg_val;

    double start_time = omp_get_wtime();
    parallel_reduction_min_avg(data, data_size, &min_val, &avg_val);
    double end_time = omp_get_wtime();

    printf("Minimum value: %d\n", min_val);
    printf("Average value: %.4lf\n", avg_val);
    printf("Execution time: %.4f seconds\n", end_time - start_time);

    free(data);
    return 0;
}
