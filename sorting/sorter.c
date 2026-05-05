#include "sorter.h"
#include <stdio.h>

void int_bubble_sort(int *arr, const size_t len) {
    if(len == 0) return;

    for(size_t i = 0; i < len-1; i++) {
        for(size_t j = 0; j < len-1; j++) {
            if(*(arr + j) > *(arr + (j+1))) {
                int temp = *(arr + j);
                *(arr + j) = *(arr + (j+1));
                *(arr + (j+1)) = temp;
            }
        }
    }
}

void selection_sort(int *arr, const size_t len) {
    if(len == 0) return;

    for(size_t i = 0; i < len; i++) {
        
        size_t index = i;

        for(size_t j = i; j < len; j++) {
            if(*(arr + j) < *(arr + index))
                index = j;
        }

        int temp = *(arr + i);
        *(arr + i) = *(arr + index);
        *(arr + index) = temp;
    }
}
