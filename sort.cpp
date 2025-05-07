#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    double start = omp_get_wtime();

    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
    }

    double end = omp_get_wtime();

    cout << "\nSorted array:\n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n\nTime taken: " << end - start << " seconds\n";

    return 0;
}
