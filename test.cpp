#include <iostream>
#include <cstring>

void radix_sort(int* arr, size_t size) {
    size_t l = 0, r = size-1;

    while (l < r) {
        if (arr[l] >= 0 && arr[r] < 0) {
            std::swap(arr[l], arr[r]);
            ++l; --r;
            continue;
        }
        if (arr[l] < 0) ++l;
        else if (arr[r] >= 0) --r;
    }
    std::cout << "l: " << l << " r: " << r << '\n';

}


int main() {
    
    int arr[] = {1, 78, -78, 89, -1, -89};

    radix_sort(arr, 6);

    for (size_t i = 0; i < 6; ++i) {
        std::cout << arr[i] << ' ';
    }
    
}