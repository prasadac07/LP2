#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int> &arr) {
    int n = arr.size();

    for(int i = 0; i < n - 1; i++) {
        int minIdx = i;

        // Find index of the minimum element in the unsorted part
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        // Swap the found minimum with the first element of the unsorted part
        swap(arr[i], arr[minIdx]);
    }
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};

    cout << "Original array: ";
    for(int x : arr) cout << x << " ";
    cout << endl;

    selectionSort(arr);

    cout << "Sorted array: ";
    for(int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
