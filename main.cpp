#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>   
#include <ctime>      
using namespace std;

template<typename T>
void partition(const vector<T>& arr, T pivot, vector<T>& less, vector<T>& equal, vector<T>& greater) {
    less.clear();
    equal.clear();
    greater.clear();
    for (const T& x : arr) {
        if (x < pivot) less.push_back(x);
        else if (x == pivot) equal.push_back(x);
        else greater.push_back(x);
    }
}

template<typename T>
T selectKth(vector<T> arr, int k) {
    if (arr.size() == 1) return arr[0];
    T pivot = arr[rand() % arr.size()];
    vector<T> less, equal, greater;
    partition(arr, pivot, less, equal, greater);

    if (k < (int)less.size()) {
        return selectKth(less, k);
    } else if (k < (int)(less.size() + equal.size())) {
        return pivot;
    } else {
        return selectKth(greater, k - less.size() - equal.size());
    }
}

int main() {
    srand(time(nullptr));
    const int N = 1000000;  

    vector<int> data(N);
    for (int i = 0; i < N; ++i) {
        data[i] = rand();
    }
    vector<int> data_sorted = data;
    clock_t start_sort = clock();
    sort(data_sorted.begin(), data_sorted.end());
    int median_sort = data_sorted[N / 2];
    clock_t end_sort = clock();
    double time_sort = double(end_sort - start_sort) / CLOCKS_PER_SEC;
    clock_t start_select = clock();
    int median_select = selectKth(data, N / 2);
    clock_t end_select = clock();
    double time_select = double(end_select - start_select) / CLOCKS_PER_SEC;
    cout << "Median by sorting: " << median_sort << "\n";
    cout << "Median by select:  " << median_select << "\n";
    cout << "Time taken by sorting method: " << time_sort << " seconds\n";
    cout << "Time taken by quickselect method: " << time_select << " seconds\n";

    return 0;
}
