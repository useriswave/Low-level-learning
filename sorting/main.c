#include <stdio.h>
#include "sorter.h"

int int_greatest(const int *arr, const size_t len);
void display_items(const int *arr, size_t len);

int main()
{
    int arr[] = {32, -34, 53, 94, -200, -999, 0, -1};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    display_items(arr, len);
    printf("\nAFTER:\n");
    selection_sort(arr, len);
    //int_bubble_sort(arr, len);          // bubble sort
    display_items(arr, len);

    printf("\nGreatest element: %d\n", int_greatest(arr, len));

    return 0;
}

int int_greatest(const int *arr, const size_t len) {
    int greatest = *arr;
    for(size_t i = 0; i < len; i++) {
        if(*(arr + i) > greatest) {
            greatest = *(arr + i);
        }
    }

    return greatest;
}

void display_items(const int *arr, size_t len) {

    for(size_t i = 0; i < len; i++) {
        printf("%d ", *(arr + i));
    }
}
