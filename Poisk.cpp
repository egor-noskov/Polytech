#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int linearSearch(const vector<int>& arr, int target, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int interpolationSearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right && target >= arr[left] && target <= arr[right]) {
        if (arr[right] == arr[left]) {
            if (arr[left] == target) return left;
            else return -1;
        }

        int pos = left + ((double)(right - left) / (arr[right] - arr[left])) * (target - arr[left]);

        if (arr[pos] == target) {
            return pos;
        }

        if (arr[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }

    return -1;
}


int main() {
    vector<int> arr = {2, 5, 7, 9, 12, 15, 18, 21, 25, 28};
    int target;
    int size=10;
    for(int i=0;i<size;++i){
        cout<<arr[i]<<" ";
    }
    cout<<endl<<"Введите число для поиска"<<endl;
    cin>>target;
    cout<<endl;

    int linearResult = linearSearch(arr, target, size);
    if (linearResult != -1) {
        cout << "Линейный поиск: Элемент найден по индексу " << linearResult << endl;
    } else {
        cout << "Линейный поиск: Элемент не найден" << endl;
    }

    int binaryResult = binarySearch(arr, target);
    if (binaryResult != -1) {
        cout << "Бинарный поиск: Элемент найден по индексу " << binaryResult << endl;
    } else {
        cout << "Бинарный поиск: Элемент не найден" << endl;
    }

    int interpolationResult = interpolationSearch(arr, target);
    if (interpolationResult != -1) {
        cout << "Интерполяционный поиск: Элемент найден по индексу " << interpolationResult << endl;
    } else {
        cout << "Интерполяционный поиск: Элемент не найден" << endl;
    }
    return 0;
}