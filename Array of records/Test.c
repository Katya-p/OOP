#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "Array.h" 

void main(){
    assert(ra_create(3, 0) == NULL);
    RecordArray *arr = ra_create(5, sizeof(int));
    int array[5] = { 10000, 2, 3, 4, 5 };
    for (size_t i = 0; i < 5; i++){
        ra_set(arr, i, array + i);
        assert(*(int*)ra_get(arr, i) == array[i]);
    }
    ra_delete(arr);
    _CrtDumpMemoryLeaks();
}